#pragma once

#include "MPE/Core/_CORE.h"

#include <thread>
#include <atomic>
#include <mutex>

#include "OpenALContext.h"

#include <AL/al.h>
#include <AL/alc.h>

// Simple Audio Generators in cases needed for testing:
// * https://onlinetonegenerator.com/
// * https://www.szynalski.com/tone-generator/

namespace MPE
{
class MPE_API SoundPlayer
{
  protected:
    SoundPlayer();

  public:
    virtual ~SoundPlayer();

    void Play();
    void Stop();
    std::string GetInfo();

  protected:
    virtual bool LoadSoundFile(const std::string &filename) = 0;

  protected:
    ALuint m_bufferId;
    ALuint m_sourceId;
    std::atomic<bool> m_isPlaying;
    std::thread m_soundThread;
    std::mutex m_mutex;

  private:
    void PlaySound();
};
}