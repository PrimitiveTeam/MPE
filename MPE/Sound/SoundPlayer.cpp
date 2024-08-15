#include "SoundPlayer.h"

#include "OpenALContext.h"
#include "MPE/Log/GlobalLog.h"
#include "MPE/App/App.h"

namespace MPE
{
SoundPlayer::SoundPlayer() : m_BufferID(0), m_SourceID(0), m_IsPlaying(false)
{
    alGenBuffers(1, &m_BufferID);
    alGenSources(1, &m_SourceID);

    // Register this player with the OpenALContext
    App::GetApp().GetOpenALContext().AddPlayer(this);
}

SoundPlayer::~SoundPlayer()
{
    this->Stop();

    if (m_SoundThread.joinable())
    {
        m_SoundThread.join();
    }

    alSourceStop(m_SourceID);
    alDeleteSources(1, &m_SourceID);
    alDeleteBuffers(1, &m_BufferID);

    // Unregister this player from the OpenALContext
    App::GetApp().GetOpenALContext().RemovePlayer(this);
}

void SoundPlayer::Play()
{
    std::lock_guard<std::mutex> lock(m_Mutex);

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
    {
        std::lock_guard<std::mutex> lock(m_Mutex);
        if (!m_IsPlaying) return;
        m_IsPlaying = false;
    }

    if (m_IsPlaying)
    {
        m_IsPlaying = false;
        if (m_SoundThread.joinable())
        {
            m_SoundThread.join();
        }
    }
}

std::string SoundPlayer::GetInfo()
{
    std::string info;
    info += "SoundPlayer Info:\n";
    info += "\tBuffer ID: " + std::to_string(m_BufferID) + "\n";
    info += "\tSource ID: " + std::to_string(m_SourceID) + "\n";
    info += "\tDevice: " + std::to_string(reinterpret_cast<uintptr_t>(App::GetApp().GetOpenALContext().GetDevice())) + "\n";
    info += "\tContext: " + std::to_string(reinterpret_cast<uintptr_t>(App::GetApp().GetOpenALContext().GetContext())) + "\n";
    info += "\tIs Playing: " + std::to_string(m_IsPlaying);
    return info;
}

void SoundPlayer::PlaySound()
{
    alSourcePlay(m_SourceID);

    ALint state = AL_PLAYING;
    while (state == AL_PLAYING && m_IsPlaying)
    {
        alGetSourcei(m_SourceID, AL_SOURCE_STATE, &state);

        if (!m_IsPlaying)
        {
            break;
        }

        // Prevent CPU from being overworked
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    alSourceStop(m_SourceID);

    {
        // Lock the mutex
        std::lock_guard<std::mutex> lock(m_Mutex);
        m_IsPlaying = false;
    }
}
}