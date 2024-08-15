#include "OggSoundPlayer.h"

#include "MPE/Log/GlobalLog.h"
#include "stb_vorbis.c"

namespace MPE
{
OggSoundPlayer::OggSoundPlayer(const std::string &filename)
{
    if (!LoadSoundFile(filename))
    {
        auto err = fmt::format("Failed to load WAV file: {0}", filename);
        MPE_CORE_ERROR(err);
        MPE_CORE_ASSERT(false, err);
        return;
    }
}

bool OggSoundPlayer::LoadSoundFile(const std::string &filename)
{
    std::vector<char> bufferData;
    ALenum format;
    ALsizei freq;
    if (!LoadOggFile(filename, bufferData, format, freq)) return false;

    alBufferData(m_BufferID, format, bufferData.data(), static_cast<ALsizei>(bufferData.size()), freq);
    alSourcei(m_SourceID, AL_BUFFER, m_BufferID);

    return true;
}

bool OggSoundPlayer::LoadOggFile(const std::string &filename, std::vector<char> &buffer, ALenum &format, ALsizei &freq)
{
    int channels, sampleRate;
    short *output;
    int len = stb_vorbis_decode_filename(filename.c_str(), &channels, &sampleRate, &output);

    if (len < 0)
    {
        auto err = fmt::format("Failed to decode OGG file: {0}", filename);
        MPE_CORE_ERROR(err);
        MPE_CORE_ASSERT(false, err);
        return false;
    }

    freq = static_cast<ALsizei>(sampleRate);

    if (channels == 1)
    {
        format = AL_FORMAT_MONO16;
    }
    else if (channels == 2)
    {
        format = AL_FORMAT_STEREO16;
    }
    else
    {
        auto err = fmt::format("Unsupported channel count: {0} in OGG file: {1}", channels, filename);
        MPE_CORE_ERROR(err);
        MPE_CORE_ASSERT(false, err);
        free(output);
        return false;
    }

    buffer.assign(reinterpret_cast<char *>(output), reinterpret_cast<char *>(output) + len * channels * sizeof(short));
    free(output);

    return true;
}
}