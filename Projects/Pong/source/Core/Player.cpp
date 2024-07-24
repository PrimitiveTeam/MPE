#include "Player.h"

#include "MPE/Input/Input.h"

namespace PONG
{
Player::Player(glm::vec2 position, glm::vec2 size, const KeyMap controls, glm::vec4 color)
    : Score(0), Position(position), Size(size), Up(controls.UP), Down(controls.DOWN), Color(color), Velocity{0.0f, 5.0f}
{
}

Player::~Player() {}

void Player::SetScore(int value)
{
    Score = value;
}

void Player::IterateScore()
{
    Score++;
}

void Player::SetPosition(glm::vec2 position)
{
    Position = position;
}

void Player::SetX(float x)
{
    Position.x = x;
}

void Player::SetY(float y)
{
    Position.y = y;
}

void Player::SetColor(glm::vec4 rgba)
{
    Color.r = rgba.r;
    Color.g = rgba.g;
    Color.b = rgba.b;
    Color.a = rgba.a;
}

// void Player::OnUpdate(MPE::_TIME deltatime)
// {
//     Movement(deltatime);
//     CheckBounds();
// }

// void Player::Movement(MPE::_TIME deltatime)
// {
//     if (MPE::Input::IsKeyPressed(Up))
//     {
//         Position.y += 5.0f * deltatime;
//     }
//     if (MPE::Input::IsKeyPressed(Down))
//     {
//         Position.y -= 5.0f * deltatime;
//     }
// }

// void Player::CheckBounds()
// {
//     if (Position.y >= (Bounds.y / 2.3))
//     {
//         Position.y = (Bounds.y / 2.3);
//     }
//     if (Position.y <= (-Bounds.y / 2.3))
//     {
//         Position.y = (-Bounds.y / 2.3);
//     }
// }

// void Player::OnEvent(Event &e)
// {
// }

}