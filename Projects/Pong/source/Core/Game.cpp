#include "Game.h"

#include <random>

namespace PONG
{
Game::Game(Player *lplayer, Player *rplayer, Ball *ball) : leftPlayer(lplayer), rightPlayer(rplayer), BALL(ball)
{
    BallStart();
}

Game::Game(Player *lplayer, Player *rplayer, Ball *ball, glm::vec4 bounds) : leftPlayer(lplayer), rightPlayer(rplayer), BALL(ball), Bounds(bounds)
{
    BallStart();
}

Game::~Game() {}

void Game::SetBounds(glm::vec4 bounds)
{
    Bounds = bounds;
}

void Game::OnUpdate(MPE::Time deltatime)
{
    MoveBall(deltatime);
    CheckBallBounds();

    PlayerMovement(deltatime);
    CheckPlayerBounds();

    PlayerCollider();

    MPE_INFO("Ball Position: ({0}, {1})", BALL->GetPosition().x, BALL->GetPosition().y);
    MPE_INFO("Left Player Position: ({0}, {1})", leftPlayer->GetPosition().x, leftPlayer->GetPosition().y);
    MPE_INFO("Right Player Position: ({0}, {1})", rightPlayer->GetPosition().x, rightPlayer->GetPosition().y);
}
// BALL

void Game::BallStart()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 100);
    int ran = dist(rng);

    if (ran < 50 && ran >= 0)
    {
        MPE_INFO("RANDOM NUMBER = {0}", ran);
        BallDirectionX = DIRECTION::LEFT;
    }
    else if (ran >= 50 && ran <= 100)
    {
        MPE_INFO("RANDOM NUMBER = {0}", ran);
        BallDirectionX = DIRECTION::RIGHT;
    }
    else
    {
        MPE_ERROR("RANDOM NUMBER = {0}", ran);
        MPE_ASSERT(0, "");
    }

    std::string temp = "";
    if (BallDirectionX == DIRECTION::LEFT)
    {
        temp = "LEFT";
    }
    else
    {
        temp = "RIGHT";
    }
    MPE_INFO("DIRECTION: {0}", temp);
}

void Game::MoveBall(MPE::Time deltatime)
{
    if (BallDirectionX == DIRECTION::LEFT)
    {
        float temp = BALL->GetPosition().x;
        BALL->SetX(temp -= BallSpeed * deltatime);
    }
    if (BallDirectionX == DIRECTION::RIGHT)
    {
        float temp = BALL->GetPosition().x;
        BALL->SetX(temp += BallSpeed * deltatime);
    }
    if (BallDirectionY == DIRECTION::UP)
    {
        float temp = BALL->GetPosition().y;
        BALL->SetY(temp -= BallSpeed * deltatime);
    }
    if (BallDirectionY == DIRECTION::DOWN)
    {
        float temp = BALL->GetPosition().y;
        BALL->SetY(temp += BallSpeed * deltatime);
    }
}

void Game::CheckBallBounds()
{
    if (BALL->GetPosition().x <= (Bounds.x + (Bounds.x * 0.05)))
    {
        ResetBall();
    }
    if (BALL->GetPosition().x >= (-Bounds.x + (-Bounds.x * 0.05)))
    {
        ResetBall();
    }
    // if (BALL->GetPosition().y <= (Bounds.y * 0.55))
    // {
    //     SwitchBallY();
    //     SwitchBallX();
    // }
    // if (BALL->GetPosition().y >= (-Bounds.y * 0.55))
    // {
    //     SwitchBallY();
    //     SwitchBallX();
    // }
}

void Game::SwitchBallX()
{
    switch (BallDirectionX)
    {
        case DIRECTION::LEFT:
            BallDirectionX = DIRECTION::RIGHT;
            break;
        case DIRECTION::RIGHT:
            BallDirectionX = DIRECTION::LEFT;
            break;
    }
}

void Game::SwitchBallY()
{
    switch (BallDirectionY)
    {
        case DIRECTION::UP:
            BallDirectionY = DIRECTION::DOWN;
            break;
        case DIRECTION::DOWN:
            BallDirectionY = DIRECTION::UP;
            break;
    }
}

void Game::ResetBall()
{
    SwitchBallX();
    BALL->SetPosition(glm::vec2(0.0f, 0.0f));
}

void Game::BallRicochet(MPE::Time deltatime) {}

void Game::EnableBallY()
{
    switch (enableY)
    {
        case false:

        case true:
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> dist(0, 100);
            int ran = dist(rng);

            if (ran < 50 && ran >= 0)
            {
                MPE_INFO("RANDOM NUMBER = {0}", ran);
                BallDirectionY = DIRECTION::DOWN;
            }
            else if (ran >= 50 && ran <= 100)
            {
                MPE_INFO("RANDOM NUMBER = {0}", ran);
                BallDirectionY = DIRECTION::UP;
            }
            else
            {
                MPE_ERROR("RANDOM NUMBER = {0}", ran);
                MPE_ASSERT(0, "");
            }

            std::string temp = "";
            if (BallDirectionX == DIRECTION::LEFT)
            {
                temp = "LEFT";
            }
            else
            {
                temp = "RIGHT";
            }
            MPE_INFO("DIRECTION: {0}", temp);
            YReset = false;
    }
}

// PLAYERS

void Game::PlayerMovement(MPE::Time deltatime)
{
    // LEFT PLAYER
    if (MPE::Input::IsKeyPressed(leftPlayer->GetPlayerUp()))
    {
        float temp = leftPlayer->GetPosition().y;
        leftPlayer->SetY(temp += PlayerSpeed * deltatime);
    }
    if (MPE::Input::IsKeyPressed(leftPlayer->GetPlayerDown()))
    {
        float temp = leftPlayer->GetPosition().y;
        leftPlayer->SetY(temp -= PlayerSpeed * deltatime);
    }
    // RIGHT PLAYER
    if (MPE::Input::IsKeyPressed(rightPlayer->GetPlayerUp()))
    {
        float temp = rightPlayer->GetPosition().y;
        rightPlayer->SetY(temp += PlayerSpeed * deltatime);
    }
    if (MPE::Input::IsKeyPressed(rightPlayer->GetPlayerDown()))
    {
        float temp = rightPlayer->GetPosition().y;
        rightPlayer->SetY(temp -= PlayerSpeed * deltatime);
    }
}

void Game::CheckPlayerBounds()
{
    // LEFT PLAYER
    if (leftPlayer->GetPosition().y >= (Bounds.y / 2.3))
    {
        leftPlayer->SetY(Bounds.y / 2.3);
    }
    if (leftPlayer->GetPosition().y <= (-Bounds.y / 2.3))
    {
        leftPlayer->SetY(-Bounds.y / 2.3);
    }
    // RIGHT PLAYER
    if (rightPlayer->GetPosition().y >= (Bounds.y / 2.3))
    {
        rightPlayer->SetY(Bounds.y / 2.3);
    }
    if (rightPlayer->GetPosition().y <= (-Bounds.y / 2.3))
    {
        rightPlayer->SetY(-Bounds.y / 2.3);
    }
}

void Game::PlayerCollider()
{
    auto collisionLeft = PlayerCollider(leftPlayer, BALL);
    auto collisionRight = PlayerCollider(rightPlayer, BALL);

    if (collisionLeft != whichCollider::NOCOLLISION)
    {
        SwitchBallX();
        if (!enableY)
        {
            SwitchBallY();
            enableY = true;
        }
    }

    if (collisionRight != whichCollider::NOCOLLISION)
    {
        SwitchBallX();
        if (!enableY)
        {
            SwitchBallY();
            enableY = true;
        }
    }
}

whichCollider Game::PlayerCollider(Player *player, Ball *ball)
{
    float playerLeft = player->GetPosition().x - player->GetSize().x / 2;
    float playerRight = player->GetPosition().x + player->GetSize().x / 2;
    float playerTop = player->GetPosition().y + player->GetSize().y / 2;
    float playerBottom = player->GetPosition().y - player->GetSize().y / 2;

    float ballLeft = ball->GetPosition().x - ball->GetSize().x / 2;
    float ballRight = ball->GetPosition().x + ball->GetSize().x / 2;
    float ballTop = ball->GetPosition().y + ball->GetSize().y / 2;
    float ballBottom = ball->GetPosition().y - ball->GetSize().y / 2;

    bool collisionX = playerLeft <= ballRight && ballLeft <= playerRight;
    bool collisionY = playerBottom <= ballTop && ballBottom <= playerTop;

    if (collisionX && collisionY)
    {
        return whichCollider::XBall;
    }

    return whichCollider::NOCOLLISION;
}

}