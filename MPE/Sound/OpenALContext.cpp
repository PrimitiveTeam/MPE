#include "OpenALContext.h"

#include "SoundPlayer.h"
#include "MPE/Log/GlobalLog.h"

namespace MPE
{
std::mutex OpenALContext::s_instanceMutex;
OpenALContext* OpenALContext::s_instance = nullptr;

OpenALContext::OpenALContext() : m_device(nullptr), m_context(nullptr)
{
    m_device = alcOpenDevice(nullptr);
    if (!m_device)
    {
        MPE_CORE_ERROR("Failed to open an OpenAL device.");
        return;
    }

    m_context = alcCreateContext(m_device, nullptr);
    if (!alcMakeContextCurrent(m_context))
    {
        MPE_CORE_ERROR("Failed to create an OpenAL context.");
        alcCloseDevice(m_device);
        m_device = nullptr;
        m_context = nullptr;
        return;
    }

    MPE_CORE_INFO("OpenAL context created.");
}

OpenALContext::~OpenALContext()
{
    {
        std::lock_guard<std::mutex> lock(m_playerMutex);
        for (SoundPlayer* player : m_players)
        {
            // Assumes ownership; otherwise, call a destroy function.
            delete player;
        }
        m_players.clear();
    }
    MPE_WARN("OpenAL: Errors: {0} | Device: {1}", alGetError(), alcGetError(m_device));
    alcMakeContextCurrent(nullptr);

    if (m_context)
    {
        // delete m_context;
        alcDestroyContext(m_context);
        m_context = nullptr;
    }

    if (m_device)
    {
        // delete m_device;
        alcCloseDevice(m_device);
        m_device = nullptr;
    }

    MPE_CORE_INFO("OpenAL context destroyed.");
}

// Singleton accessor
OpenALContext& OpenALContext::GetInstance()
{
    // Double-checked locking for thread-safe singleton initialization
    if (s_instance == nullptr)
    {
        std::lock_guard<std::mutex> lock(s_instanceMutex);
        if (s_instance == nullptr)
        {
            s_instance = new OpenALContext();
        }
    }
    return *s_instance;
}

void OpenALContext::AddPlayer(SoundPlayer* player)
{
    std::lock_guard<std::mutex> lock(m_playerMutex);
    m_players.push_back(player);
}

void OpenALContext::RemovePlayer(SoundPlayer* player)
{
    if (!player) return;

    // TODO: Investigate => when this is used it causes a crash but it might be necessary for thread safety
    // std::lock_guard<std::mutex> lock(m_playerMutex);
    auto it = std::remove(m_players.begin(), m_players.end(), player);
    if (it != m_players.end())
    {
        m_players.erase(it, m_players.end());
    }
}
}