#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Sound/SoundPlayer.h"

#include <fstream>

namespace MPE
{
class MPE_API WavSoundPlayer : public SoundPlayer
{
  public:
    WavSoundPlayer(const std::string &filename);
    virtual ~WavSoundPlayer() {}

  protected:
    virtual bool LoadSoundFile(const std::string &filename) override;

  private:
    bool LoadWavFile(const std::string &filename, std::vector<char> &buffer, ALenum &format, ALsizei &freq);
};
}