#pragma once

#include "MPE.h"

#include <string>

#include <glm/glm.hpp>

namespace PONG
{
class Ball
{
  private:
    glm::vec2 Position;
    glm::vec2 Size;
    glm::vec2 Velocity;
    MPE::REF<MPE::Texture2D> Texture;
    float Radius;

    // DIRECTION Direction = DIRECTION::None;
  public:
    Ball(glm::vec2 position, glm::vec2 size, const std::string &texture, float radius = 0.25f);
    ~Ball();

    glm::vec2 GetPosition() const { return Position; }
    // float GetX() { return Position.x; }
    // float GetY() { return Position.y; }
    void SetPosition(glm::vec2 position);
    void SetX(float x);
    void SetY(float y);

    glm::vec2 GetSize() const { return Size; }
    void SetSize(glm::vec2 size);

    glm::vec2 GetVelocity() const { return Velocity; }
    void SetVelocity(glm::vec2 velocity) { Velocity = velocity; }

    MPE::REF<MPE::Texture2D> GetTexture() const { return Texture; }
    // void SetTexture(const std::string& texture);

    float GetRadius() const { return Radius; }
    void SetRadius(float radius);

    // DIRECTION GetDirection() const { return Direction; }
    // void SetDirection(DIRECTION dir);

    // void OnUpdate(MPE::_TIME deltaTime);

    // void Move(MPE::_TIME deltaTime);
    // void CheckBounds(MPE::_TIME deltaTime);

    // void switchX();
    // void switchY();
    // void reset();

    // void Ricochet(MPE::_TIME deltaTime);
};
}