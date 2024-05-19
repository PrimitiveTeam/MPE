#pragma once

// #include "MPE/MPE.h"
#include "Player.h"
#include "Ball.h"

namespace PONG
{
enum DIRECTION
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NONE
};

enum whichCollider
{
    NOCOLLISION = 0,
    XBall = 1,
    YBall = 2,
};

// typedef std::tuple<bool, Direction, glm::vec2> Collision;

class Game
{
  private:
    Player *leftPlayer;
    Player *rightPlayer;

    Ball *BALL;
    DIRECTION BallDirectionX = DIRECTION::NONE;
    DIRECTION BallDirectionY = DIRECTION::NONE;
    bool enableY = false;
    bool YReset = true;

    glm::vec4 Bounds = {0.0f, 0.0f, 0.0f, 0.0f};

    float PlayerSpeed = 5.0f;
    float BallSpeed = 25.0f;

  public:
    Game(Player *lplayer, Player *rplayer, Ball *ball);
    Game(Player *lplayer, Player *rplayer, Ball *ball, glm::vec4 bounds);
    ~Game();

    // Player *GetLeftPlayer() { return lp; }
    // Player *GetRightPlayer() { return rp; }
    // Ball *GetBall() { return bl; }

    void SetBounds(glm::vec4 bounds);

    void OnUpdate(MPE::Time deltatime);

    // BALL
    void BallStart();

    void MoveBall(MPE::Time deltatime);
    void CheckBallBounds();
    void SwitchBallX();
    void SwitchBallY();
    void ResetBall();
    void BallRicochet(MPE::Time deltatime);
    void EnableBallY();

    // PLAYERS
    void PlayerMovement(MPE::Time deltatime);
    void CheckPlayerBounds();
    void PlayerCollider();
    whichCollider PlayerCollider(Player *player, Ball *ball);
};
// COLLISION
// DIRECTION VectorDirection(glm::vec2 target)
// {
//     glm::vec2 compass[] = {
//         glm::vec2(0.0f, 1.0f),  // up
//         glm::vec2(1.0f, 0.0f),  // right
//         glm::vec2(0.0f, -1.0f), // down
//         glm::vec2(-1.0f, 0.0f)  // left
//     };
//     float max = 0.0f;
//     unsigned int best_match = -1;
//     for (unsigned int i = 0; i < 4; i++)
//     {
//         float dot_product = glm::dot(glm::normalize(target), compass[i]);
//         if (dot_product > max)
//         {
//             max = dot_product;
//             best_match = i;
//         }
//     }
//     return (DIRECTION)best_match;
// }

// Collision CheckCollision(Ball *one, Player *two)
// {
//     // get center point circle first
//     glm::vec2 center(one->GetPosition() + one->GetRadius());
//     // calculate AABB info (center, half-extents)
//     glm::vec2 aabb_half_extents(two->GetSize().x / 2.0f, two->GetSize().y / 2.0f);
//     glm::vec2 aabb_center(two->GetPosition().x + aabb_half_extents.x, two->GetPosition().y + aabb_half_extents.y);
//     // get difference vector between both centers
//     glm::vec2 difference = center - aabb_center;
//     glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
//     // now that we know the the clamped values, add this to AABB_center and we get the value of box closest to circle
//     glm::vec2 closest = aabb_center + clamped;
//     // now retrieve vector between center circle and closest point AABB and check if length < radius
//     difference = closest - center;

//     if (glm::length(difference) < one.Radius) // not <= since in that case a collision also occurs when object one exactly touches object two, which they are
//     at the end of each collision resolution stage.
//         return std::make_tuple(true, VectorDirection(difference), difference);
//     else
//         return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
// }
}