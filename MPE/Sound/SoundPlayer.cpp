#include "SoundPlayer.h"

#include "OpenALContext.h"
#include "MPE/Log/GlobalLog.h"
#include "MPE/App/App.h"

namespace MPE
{
SoundPlayer::SoundPlayer() : m_bufferId(0), m_sourceId(0), m_isPlaying(false)
{
    alGenBuffers(1, &m_bufferId);
    alGenSources(1, &m_sourceId);

    // Register this player with the OpenALContext
    App::GetApp().GetOpenALContext().AddPlayer(this);
}

SoundPlayer::~SoundPlayer()
{
    this->Stop();

    if (m_soundThread.joinable())
    {
        m_soundThread.join();
    }

    alSourceStop(m_sourceId);
    alDeleteSources(1, &m_sourceId);
    alDeleteBuffers(1, &m_bufferId);

    // Unregister this player from the OpenALContext
    App::GetApp().GetOpenALContext().RemovePlayer(this);
}

void SoundPlayer::Play()
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_isPlaying) return;

    // Ensure any previous thread has been joined before creating a new one, otherwise crash
    if (m_soundThread.joinable())
    {
        m_soundThread.join();
    }

    m_isPlaying = true;
    m_soundThread = std::thread(&SoundPlayer::PlaySound, this);
}

void SoundPlayer::Stop()
{
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (!m_isPlaying) return;
        m_isPlaying = false;
    }

    if (m_isPlaying)
    {
        m_isPlaying = false;
        if (m_soundThread.joinable())
        {
            m_soundThread.join();
        }
    }
}

std::string SoundPlayer::GetInfo()
{
    std::string info;
    info += "SoundPlayer Info:\n";
    info += "\tBuffer ID: " + std::to_string(m_bufferId) + "\n";
    info += "\tSource ID: " + std::to_string(m_sourceId) + "\n";
    info += "\tDevice: " + std::to_string(reinterpret_cast<uintptr_t>(App::GetApp().GetOpenALContext().GetDevice())) + "\n";
    info += "\tContext: " + std::to_string(reinterpret_cast<uintptr_t>(App::GetApp().GetOpenALContext().GetContext())) + "\n";
    info += "\tIs Playing: " + std::to_string(m_isPlaying);
    return info;
}

void SoundPlayer::PlaySound()
{
    alSourcePlay(m_sourceId);

    ALint state = AL_PLAYING;
    while (state == AL_PLAYING && m_isPlaying)
    {
        alGetSourcei(m_sourceId, AL_SOURCE_STATE, &state);

        if (!m_isPlaying)
        {
            break;
        }

        // Prevent CPU from being overworked
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    alSourceStop(m_sourceId);

    {
        // Lock the mutex
        std::lock_guard<std::mutex> lock(m_mutex);
        m_isPlaying = false;
    }
}
}