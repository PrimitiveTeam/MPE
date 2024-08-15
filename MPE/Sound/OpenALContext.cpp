#include "OpenALContext.h"

#include "SoundPlayer.h"
#include "MPE/Log/GlobalLog.h"

namespace MPE
{
// Initialize static members
std::mutex OpenALContext::s_InstanceMutex;
OpenALContext* OpenALContext::s_Instance = nullptr;

OpenALContext::OpenALContext() : m_Device(nullptr), m_Context(nullptr)
{
    m_Device = alcOpenDevice(nullptr);
    if (!m_Device)
    {
        MPE_CORE_ERROR("Failed to open an OpenAL device.");
        return;
    }

    m_Context = alcCreateContext(m_Device, nullptr);
    if (!alcMakeContextCurrent(m_Context))
    {
        MPE_CORE_ERROR("Failed to create an OpenAL context.");
        alcCloseDevice(m_Device);
        m_Device = nullptr;
        m_Context = nullptr;
        return;
    }

    MPE_CORE_INFO("OpenAL context created.");
}

OpenALContext::~OpenALContext()
{
    {
        std::lock_guard<std::mutex> lock(m_PlayerMutex);
        for (SoundPlayer* player : m_Players)
        {
            // Assumes ownership; otherwise, call a destroy function.
            delete player;
        }
        m_Players.clear();
    }
    MPE_WARN("OpenAL: Errors: {0} | Device: {1}", alGetError(), alcGetError(m_Device));
    alcMakeContextCurrent(nullptr);

    if (m_Context)
    {
        // delete m_Context;
        alcDestroyContext(m_Context);
        m_Context = nullptr;
    }

    if (m_Device)
    {
        // delete m_Device;
        alcCloseDevice(m_Device);
        m_Device = nullptr;
    }

    MPE_CORE_INFO("OpenAL context destroyed.");
}

// Singleton accessor
OpenALContext& OpenALContext::GetInstance()
{
    // Double-checked locking for thread-safe singleton initialization
    if (s_Instance == nullptr)
    {
        std::lock_guard<std::mutex> lock(s_InstanceMutex);
        if (s_Instance == nullptr)
        {
            s_Instance = new OpenALContext();
        }
    }
    return *s_Instance;
}

void OpenALContext::AddPlayer(SoundPlayer* player)
{
    std::lock_guard<std::mutex> lock(m_PlayerMutex);
    m_Players.push_back(player);
}

void OpenALContext::RemovePlayer(SoundPlayer* player)
{
    if (!player) return;

    // TODO: Investigate => when this is used it causes a crash but it might be necessary for thread safety
    // std::lock_guard<std::mutex> lock(m_PlayerMutex);
    auto it = std::remove(m_Players.begin(), m_Players.end(), player);
    if (it != m_Players.end())
    {
        m_Players.erase(it, m_Players.end());
    }
}
}