#include "Ball.h"

#include <stdlib.h>

namespace PONG
{
Ball::Ball(glm::vec2 position, glm::vec2 size, const std::string &texture, float radius) : Position(position), Size(size), Radius(radius)
{
    Texture = MPE::Texture2D::Create(texture);
}

Ball::~Ball() {}

void Ball::SetPosition(glm::vec2 position)
{
    Position = position;
}

void Ball::SetX(float x)
{
    Position.x = x;
}

void Ball::SetY(float y)
{
    Position.y = y;
}

void Ball::SetSize(glm::vec2 size)
{
    Size = size;
}

// void Ball::SetDirection(DIRECTION dir)
// {
//     Direction = dir;
// }

// void Ball::OnUpdate(MPE::_TIME deltatime)
// {
//     Move(deltatime);
//     CheckBounds(deltatime);
// }
}