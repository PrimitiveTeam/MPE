#pragma once

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

class Game
{
  private:
    Player *leftPlayer;
    Player *rightPlayer;
    Ball *BALL;
    DIRECTION BallDirectionX = DIRECTION::NONE;
    DIRECTION BallDirectionY = DIRECTION::NONE;

    glm::vec4 Bounds = {0.0f, 0.0f, 0.0f, 0.0f};

    float PlayerSpeed = 10.0f;
    float BallSpeed = 25.0f;

    MPE::OggSoundPlayer *BallHitSound;
    MPE::OggSoundPlayer *ScoreSound;

  public:
    Game(Player *lplayer, Player *rplayer, Ball *ball);
    Game(Player *lplayer, Player *rplayer, Ball *ball, glm::vec4 bounds);
    ~Game();

    void SetBounds(glm::vec4 bounds);
    void OnUpdate(MPE::Time deltaTime);

    void BallStart();
    void MoveBall(MPE::Time deltaTime);
    void CheckBallBounds();
    void ResetBall();
    void PlayerMovement(MPE::Time deltaTime);
    void CheckPlayerBounds();
    void PlayerCollider();
    void HandlePlayerCollision(Player *player);
    bool PlayerCollider(Player *player, Ball *ball);
};
}