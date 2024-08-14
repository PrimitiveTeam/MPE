#include "SoundPlayer.h"

#include "MPE/Log/GlobalLog.h"

namespace MPE
{
SoundPlayer::SoundPlayer() : m_Device(nullptr), m_Context(nullptr), m_BufferID(0), m_SourceID(0), m_IsPlaying(false)
{
    m_Device = alcOpenDevice(nullptr);
    if (!m_Device)
    {
        auto err = fmt::format("Failed to open an OpenAL device.");
        MPE_CORE_ERROR(err);
        MPE_CORE_ASSERT(false, err);
        return;
    }

    m_Context = alcCreateContext(m_Device, nullptr);
    if (!alcMakeContextCurrent(m_Context))
    {
        alcCloseDevice(m_Device);
        auto err = fmt::format("Failed to create an OpenAL context.");
        MPE_CORE_ERROR(err);
        MPE_CORE_ASSERT(false, err);
        return;
    }

    alGenBuffers(1, &m_BufferID);
    alGenSources(1, &m_SourceID);
}

SoundPlayer::~SoundPlayer()
{
    this->Stop();

    if (m_SoundThread.joinable())
    {
        m_SoundThread.join();
    }

    alDeleteSources(1, &m_SourceID);
    alDeleteBuffers(1, &m_BufferID);

    alcMakeContextCurrent(nullptr);
    if (m_Context) alcDestroyContext(m_Context);
    if (m_Device) alcCloseDevice(m_Device);
}

void SoundPlayer::Play()
{
    if (m_IsPlaying) return;

    // Ensure any previous thread has been joined before creating a new one, otherwise crash
    if (m_SoundThread.joinable())
    {
        m_SoundThread.join();
    }

    m_IsPlaying = true;
    m_SoundThread = std::thread(&SoundPlayer::PlaySound, this);
}

void SoundPlayer::Stop()
{
    if (m_IsPlaying)
    {
        m_IsPlaying = false;
        if (m_SoundThread.joinable())
        {
            m_SoundThread.join();
        }
    }
}

void SoundPlayer::PlaySound()
{
    alSourcePlay(m_SourceID);

    ALint state = AL_PLAYING;
    while (state == AL_PLAYING && m_IsPlaying)
    {
        alGetSourcei(m_SourceID, AL_SOURCE_STATE, &state);
    }

    alSourceStop(m_SourceID);
    m_IsPlaying = false;
}
}