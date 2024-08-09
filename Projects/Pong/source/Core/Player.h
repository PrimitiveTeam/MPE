#pragma once

#include <glm/glm.hpp>
#include "MPE/Time/Time.h"
#include "MPE/Events/EventApp.h"
#include "MPE/Events/EventMouse.h"

namespace PONG
{
struct KeyMap
{
    uint32_t UP;
    uint32_t DOWN;

    KeyMap(uint32_t up, uint32_t down)
    {
        UP = up;
        DOWN = down;
    }
};

class Player
{
  private:
    int Score;
    glm::vec2 Position;
    glm::vec2 Size;
    glm::vec2 Velocity;

    uint32_t Up;
    uint32_t Down;

    glm::vec4 Color;

  public:
    Player(glm::vec2 position, glm::vec2 size, const KeyMap controls, glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f});
    ~Player();

    int GetScore() const { return Score; }
    void SetScore(int value);
    void IterateScore();

    glm::vec2 GetPosition() { return Position; }
    void SetPosition(glm::vec2 position);
    void SetX(float x);
    void SetY(float y);
    glm::vec2 GetSize() { return Size; }
    void SetSize(glm::vec2 size);

    glm::vec2 GetVelocity() { return Velocity; }
    void SetVelocity(glm::vec2 velocity) { Velocity = velocity; }

    glm::vec4 GetColor() { return Color; }
    void SetColor(glm::vec4 rgba);

    uint32_t GetPlayerUp() const { return Up; }
    uint32_t GetPlayerDown() const { return Down; }

    // void OnUpdate(MPE::_TIME deltatime);
    // void Movement(MPE::_TIME deltatime);
    // void CheckBounds();
    // void OnEvent(Event &e);
};
}