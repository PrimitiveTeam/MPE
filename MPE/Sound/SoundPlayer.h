#pragma once

#include "MPE/Core/_CORE.h"

#include <iostream>
#include <vector>
#include <thread>
#include <atomic>

#include <AL/al.h>
#include <AL/alc.h>

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

  protected:
    virtual bool LoadSoundFile(const std::string &filename) = 0;

  protected:
    ALuint m_BufferID;
    ALuint m_SourceID;
    ALCdevice *m_Device;
    ALCcontext *m_Context;
    std::atomic<bool> m_IsPlaying;
    std::thread m_SoundThread;

  private:
    void PlaySound();
};
}