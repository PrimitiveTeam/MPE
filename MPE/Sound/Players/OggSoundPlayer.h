#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Sound/SoundPlayer.h"

#include <fstream>

namespace MPE
{
class MPE_API OggSoundPlayer : public SoundPlayer
{
  public:
    OggSoundPlayer(const std::string &filename);
    virtual ~OggSoundPlayer() {}

  protected:
    virtual bool LoadSoundFile(const std::string &filename) override;

  private:
    bool LoadOggFile(const std::string &filename, std::vector<char> &buffer, ALenum &format, ALsizei &freq);
};
}