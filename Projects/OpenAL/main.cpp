#include <AL/al.h>
#include <AL/alc.h>
#include <iostream>
#include <vector>
#include <fstream>

// Used https://tomeko.net/online_tools/wave_gen.php?lang=en to generate a .wav file

bool loadWavFile(const std::string &filename, std::vector<char> &buffer, ALenum &format, ALsizei &freq)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    // Read WAV header
    char riff[4];
    file.read(riff, 4);
    if (strncmp(riff, "RIFF", 4) != 0)
    {
        std::cerr << "Not a valid WAV file (missing RIFF header)." << std::endl;
        return false;
    }

    // Skip file size
    file.ignore(4);

    char wave[4];
    file.read(wave, 4);
    if (strncmp(wave, "WAVE", 4) != 0)
    {
        std::cerr << "Not a valid WAV file (missing WAVE header)." << std::endl;
        return false;
    }

    char fmt[4];
    file.read(fmt, 4);
    if (strncmp(fmt, "fmt ", 4) != 0)
    {
        std::cerr << "Not a valid WAV file (missing fmt header)." << std::endl;
        return false;
    }

    // Skip fmt chunk size
    file.ignore(4);

    short audioFormat;
    file.read(reinterpret_cast<char *>(&audioFormat), sizeof(short));
    if (audioFormat != 1)
    {
        std::cerr << "Unsupported WAV file format (must be PCM)." << std::endl;
        return false;
    }

    short numChannels;
    file.read(reinterpret_cast<char *>(&numChannels), sizeof(short));

    file.read(reinterpret_cast<char *>(&freq), sizeof(ALsizei));

    // Skip byte rate and block align
    file.ignore(6);

    short bitsPerSample;
    file.read(reinterpret_cast<char *>(&bitsPerSample), sizeof(short));

    // Skip data chunk header
    file.ignore(4);

    int dataSize;
    file.read(reinterpret_cast<char *>(&dataSize), sizeof(int));

    buffer.resize(dataSize);
    file.read(buffer.data(), dataSize);

    // Determine OpenAL format
    if (numChannels == 1)
    {
        if (bitsPerSample == 8)
            format = AL_FORMAT_MONO8;
        else if (bitsPerSample == 16)
            format = AL_FORMAT_MONO16;
    }
    else if (numChannels == 2)
    {
        if (bitsPerSample == 8)
            format = AL_FORMAT_STEREO8;
        else if (bitsPerSample == 16)
            format = AL_FORMAT_STEREO16;
    }
    else
    {
        std::cerr << "Unsupported channel count: " << numChannels << std::endl;
        return false;
    }

    // Ensure the data size is a multiple of the frame size
    int frameSize = (bitsPerSample / 8) * numChannels;
    if (dataSize % frameSize != 0)
    {
        std::cerr << "Data size " << dataSize << " is not a multiple of frame size " << frameSize << std::endl;
        return false;
    }

    return true;
}

int main()
{
    // Initialize OpenAL
    ALCdevice *device = alcOpenDevice(nullptr);
    if (!device)
    {
        std::cerr << "Failed to open an OpenAL device." << std::endl;
        return -1;
    }

    ALCcontext *context = alcCreateContext(device, nullptr);
    if (!alcMakeContextCurrent(context))
    {
        std::cerr << "Failed to set OpenAL context." << std::endl;
        alcCloseDevice(device);
        return -1;
    }

    // Load WAV file
    ALuint bufferID;
    alGenBuffers(1, &bufferID);

    std::vector<char> bufferData;
    ALenum format;
    ALsizei freq;
    if (!loadWavFile("Data//Sounds//sound.wav", bufferData, format, freq))
    {
        std::cerr << "Failed to load WAV file." << std::endl;
        alDeleteBuffers(1, &bufferID);
        alcDestroyContext(context);
        alcCloseDevice(device);
        return -1;
    }

    alBufferData(bufferID, format, bufferData.data(), static_cast<ALsizei>(bufferData.size()), freq);

    // Generate source and play sound
    ALuint sourceID;
    alGenSources(1, &sourceID);
    alSourcei(sourceID, AL_BUFFER, bufferID);
    alSourcePlay(sourceID);

    // Wait until the sound has finished playing
    ALint state = AL_PLAYING;
    while (state == AL_PLAYING)
    {
        alGetSourcei(sourceID, AL_SOURCE_STATE, &state);
    };

    // Clean up OpenAL resources
    alDeleteSources(1, &sourceID);
    alDeleteBuffers(1, &bufferID);
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    alcCloseDevice(device);

    return 0;
}
