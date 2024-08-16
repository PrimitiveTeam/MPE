#pragma once

#include "MPE/Core/_CORE.h"

#include <mutex>

#include <AL/al.h>
#include <AL/alc.h>

namespace MPE
{
class MPE_API SoundPlayer;

class MPE_API OpenALContext
{
  public:
    // OpenALContext();
    // Deleted copy constructor and assignment operator to prevent copies
    OpenALContext(const OpenALContext&) = delete;
    OpenALContext& operator=(const OpenALContext&) = delete;

    // Static method to access the singleton instance
    static OpenALContext& GetInstance();
    ~OpenALContext();

    ALCdevice* GetDevice() { return m_device; }
    ALCcontext* GetContext() { return m_context; }

    void AddPlayer(SoundPlayer* player);
    void RemovePlayer(SoundPlayer* player);

  private:
    OpenALContext();

    // Helper method for instance creation
    static OpenALContext& CreateInstance();

  private:
    ALCdevice* m_device;
    ALCcontext* m_context;

    std::vector<SoundPlayer*> m_players;
    std::mutex m_playerMutex;

    // Mutex for thread-safe singleton initialization
    static std::mutex s_instanceMutex;
    static OpenALContext* s_instance;
};
}