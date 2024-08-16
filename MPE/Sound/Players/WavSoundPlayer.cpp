#include "WavSoundPlayer.h"

#include "MPE/Log/GlobalLog.h"

namespace MPE
{
WavSoundPlayer::WavSoundPlayer(const std::string &filename)
{
    if (!LoadSoundFile(filename))
    {
        auto err = fmt::format("Failed to load WAV file: {0}", filename);
        MPE_CORE_ERROR(err);
        MPE_CORE_ASSERT(false, err);
        return;
    }
}

bool WavSoundPlayer::LoadSoundFile(const std::string &filename)
{
    std::vector<char> bufferData;
    ALenum format;
    ALsizei freq;
    if (!LoadWavFile(filename, bufferData, format, freq)) return false;

    alBufferData(m_bufferId, format, bufferData.data(), static_cast<ALsizei>(bufferData.size()), freq);
    alSourcei(m_sourceId, AL_BUFFER, m_bufferId);

    return true;
}

bool WavSoundPlayer::LoadWavFile(const std::string &filename, std::vector<char> &buffer, ALenum &format, ALsizei &freq)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file)
    {
        auto err = fmt::format("Error opening file: {0}", filename);
        MPE_CORE_ERROR(err);
        MPE_CORE_ASSERT(false, err);
        return false;
    }

    char riff[4];
    file.read(riff, 4);
    if (strncmp(riff, "RIFF", 4) != 0)
    {
        auto err = fmt::format("Not a valid WAV file (missing RIFF header): {0}", filename);
        MPE_CORE_ERROR(err);
        MPE_CORE_ASSERT(false, err);
        return false;
    }

    file.ignore(4);

    char wave[4];
    file.read(wave, 4);
    if (strncmp(wave, "WAVE", 4) != 0)
    {
        auto err = fmt::format("Not a valid WAV file (missing WAVE header): {0}", filename);
        MPE_CORE_ERROR(err);
        MPE_CORE_ASSERT(false, err);
        return false;
    }

    char fmt[4];
    file.read(fmt, 4);
    if (strncmp(fmt, "fmt ", 4) != 0)
    {
        auto err = fmt::format("Not a valid WAV file (missing fmt header): {0}", filename);
        MPE_CORE_ERROR(err);
        MPE_CORE_ASSERT(false, err);
        return false;
    }

    file.ignore(4);

    short audioFormat;
    file.read(reinterpret_cast<char *>(&audioFormat), sizeof(short));
    if (audioFormat != 1)
    {
        auto err = fmt::format("Unsupported WAV file format (must be PCM): {0}", filename);
        MPE_CORE_ERROR(err);
        MPE_CORE_ASSERT(false, err);
        return false;
    }

    short numChannels;
    file.read(reinterpret_cast<char *>(&numChannels), sizeof(short));

    file.read(reinterpret_cast<char *>(&freq), sizeof(ALsizei));

    file.ignore(6);

    short bitsPerSample;
    file.read(reinterpret_cast<char *>(&bitsPerSample), sizeof(short));

    file.ignore(4);

    int dataSize;
    file.read(reinterpret_cast<char *>(&dataSize), sizeof(int));

    buffer.resize(dataSize);
    file.read(buffer.data(), dataSize);

    int frameSize = (bitsPerSample / 8) * numChannels;
    if (dataSize % frameSize != 0)
    {
        auto err = fmt::format("Data size {0} is not a multiple of frame size {1}", dataSize, frameSize);
        MPE_CORE_ERROR(err);
        MPE_CORE_ASSERT(false, err);
        return false;
    }

    if (numChannels == 1)
    {
        format = (bitsPerSample == 8) ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16;
    }
    else if (numChannels == 2)
    {
        format = (bitsPerSample == 8) ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16;
    }
    else
    {
        auto err = fmt::format("Unsupported channel count: {0}", numChannels);
        MPE_CORE_ERROR(err);
        MPE_CORE_ASSERT(false, err);
        return false;
    }

    return true;
}
}