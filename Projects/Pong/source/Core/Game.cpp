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
        SwitchBallX();  // Reverse ball direction if collision with left player
    }
    if (collisionRight != whichCollider::NOCOLLISION)
    {
        SwitchBallX();  // Reverse ball direction if collision with right player
    }

    // if (BALL->GetPosition().x + BALL->GetSize().x >= leftPlayer->GetPosition().x &&
    // leftPlayer->GetPosition().x + leftPlayer->GetSize().x >= BALL->GetPosition().x)
    // {
    //     SwitchBallX();
    // }
    // if (BALL->GetPosition().x + BALL->GetSize().x >= rightPlayer->GetPosition().x &&
    // rightPlayer->GetPosition().x + rightPlayer->GetSize().x >= BALL->GetPosition().x)
    // {
    //     SwitchBallX();
    // }
}

whichCollider Game::PlayerCollider(Player *player, Ball *ball)
{
    bool collisionX =
        player->GetPosition().x + player->GetSize().x >= ball->GetPosition().x && ball->GetPosition().x + ball->GetSize().x >= player->GetPosition().x;
    bool collisionY =
        player->GetPosition().y + player->GetSize().y >= ball->GetPosition().y && ball->GetPosition().y + ball->GetSize().y >= player->GetPosition().y;

    if (collisionX && collisionY)  // Check for full collision
    {
        return whichCollider::XBall;  // Assume horizontal collision for simplicity
    }

    return whichCollider::NOCOLLISION;
}

}