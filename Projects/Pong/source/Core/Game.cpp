#include "Game.h"
#include <random>
#include <limits>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "MPE/MPE.h"

namespace PONG
{
Game::Game(Player *lplayer, Player *rplayer, Ball *ball) : leftPlayer(lplayer), rightPlayer(rplayer), BALL(ball)
{
    BallStart();
}

Game::Game(Player *lplayer, Player *rplayer, Ball *ball, glm::vec4 bounds) : leftPlayer(lplayer), rightPlayer(rplayer), BALL(ball), Bounds(bounds)
{
    // log calc
    MPE_WARN("Window Width: {0}, Window Height: {1}", MPE::App::GetApp().GetWindow()->GetWidth(), MPE::App::GetApp().GetWindow()->GetHeight());
    MPE_WARN("Bounds: ({0}, {1}, {2}, {3})", Bounds.x, Bounds.y, Bounds.z, Bounds.w);
    MPE_WARN("BOUND Y (Window Height / 2): {0}", MPE::App::GetApp().GetWindow()->GetHeight() / 2.0f);
    bounds.y = MPE::App::GetApp().GetWindow()->GetHeight() / 2.0f;
    bounds.y = 16.0f;

    bounds.z = (-1) * bounds.x;
    bounds.w = (-1) * bounds.y;

    Bounds = bounds;

    MPE_WARN("Bounds: ({0}, {1}, {2}, {3})", Bounds.x, Bounds.y, Bounds.z, Bounds.w);

    BallStart();
}

Game::~Game() {}

void Game::SetBounds(glm::vec4 bounds)
{
    Bounds = bounds;
}

void Game::OnUpdate(MPE::Time deltatime)
{
    static const float FIXED_TIMESTEP = 1.0f / 60.0f;
    static float accumulator = 0.0f;

    accumulator += deltatime.GetSeconds();

    while (accumulator >= FIXED_TIMESTEP)
    {
        PlayerMovement(FIXED_TIMESTEP);
        CheckPlayerBounds();

        // Move ball
        glm::vec2 newPosition = BALL->GetPosition();
        glm::vec2 velocity = BALL->GetVelocity();
        newPosition += velocity * FIXED_TIMESTEP;
        BALL->SetPosition(newPosition);

        // Check ball bounds
        glm::vec2 ballPosition = BALL->GetPosition();
        // Change score if ball goes out of bounds
        if (ballPosition.x <= Bounds.x)
        {
            rightPlayer->IncrementScore();
            ResetBall();
        }
        if (ballPosition.x >= -Bounds.x)
        {
            leftPlayer->IncrementScore();
            ResetBall();
        }

        // Add a bit of a border at the top and bottom
        const float border = 0.5f;

        // MPE_INFO("BALL POSITION Y: {0} <= BOUNDS Y {1} || {2} >= -BOUNDS Y {3}", ballPosition.y, Bounds.y, ballPosition.y, Bounds.y);
        if (ballPosition.y >= (Bounds.y - border) || ballPosition.y <= -(Bounds.y - border))
        {
            glm::vec2 velocity = BALL->GetVelocity();
            velocity.y *= -1;
            BALL->SetVelocity(velocity);
            // MPE_WARN("Y DETECTED. VELOCITY: {0}, {1}", velocity.x, velocity.y);
        }

        // Handle paddle collisions
        Player *paddles[2] = {leftPlayer, rightPlayer};

        for (int i = 0; i < 2; ++i)
        {
            glm::vec2 paddlePosition = paddles[i]->GetPosition();
            glm::vec2 paddleSize = paddles[i]->GetSize();
            float halfPaddleWidth = paddleSize.x / 2.0f;
            float halfPaddleHeight = paddleSize.y / 1.5f;
            float ballRadius = BALL->GetRadius();

            // Get distance from center of ball to center of paddle
            glm::vec2 distance = {std::abs(ballPosition.x - paddlePosition.x), std::abs(ballPosition.y - paddlePosition.y)};

            // Check if collision is possible
            if (distance.x <= halfPaddleWidth + ballRadius && distance.y <= halfPaddleHeight + ballRadius)
            {
                bool collision = false;
                if (distance.x <= halfPaddleWidth)
                {
                    collision = true;
                    velocity.x *= -1;
                }

                if (collision)
                {
                    // Calculate the relative intersection point
                    float relativeIntersectY = paddlePosition.y - ballPosition.y;
                    float normalizedRelativeIntersectionY = (relativeIntersectY / halfPaddleHeight);
                    // Maximum bounce angle of 45 degrees
                    float bounceAngle = normalizedRelativeIntersectionY * (glm::pi<float>() / 4);

                    velocity.x = (i == 0) ? std::abs(velocity.x) : -std::abs(velocity.x);
                    velocity.y = BallSpeed * -sin(bounceAngle);

                    // Increase ball speed after collision
                    float speedIncrease = 1.1f;
                    velocity *= speedIncrease;

                    // Add some variation based on the paddle's velocity
                    float k = 0.5f;
                    velocity.y += k * paddles[i]->GetVelocity().y;

                    BALL->SetVelocity(velocity);

                    // Prevent the ball from getting stuck inside the paddle
                    if (i == 0)
                    {
                        BALL->SetPosition(glm::vec2(paddlePosition.x + halfPaddleWidth + ballRadius, ballPosition.y));
                    }
                    else
                    {
                        BALL->SetPosition(glm::vec2(paddlePosition.x - halfPaddleWidth - ballRadius, ballPosition.y));
                    }
                }
            }
        }

        accumulator -= FIXED_TIMESTEP;
    }
}

void Game::BallStart()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 100);
    int ran = dist(rng);

    BallDirectionX = (ran < 50) ? DIRECTION::LEFT : DIRECTION::RIGHT;
    BallDirectionY = (ran < 50) ? DIRECTION::UP : DIRECTION::DOWN;

    // Ensure ball is centered
    BALL->SetPosition(glm::vec2(0.0f, 0.0f));
    // Set a reasonable initial speed for the ball
    BallSpeed = 15.0f;

    BALL->SetVelocity(glm::vec2(BallSpeed * ((BallDirectionX == DIRECTION::LEFT) ? -1 : 1), 0));

    std::string tempX = (BallDirectionX == DIRECTION::LEFT) ? "LEFT" : "RIGHT";
    std::string tempY = (BallDirectionY == DIRECTION::UP) ? "UP" : "DOWN";
    MPE_INFO("DIRECTION: {0}, {1}", tempX, tempY);
}

void Game::ResetBall()
{
    BallStart();
}

void Game::PlayerMovement(MPE::Time deltatime)
{
    // LEFT PLAYER
    if (MPE::Input::IsKeyPressed(leftPlayer->GetPlayerUp()))
    {
        float temp = leftPlayer->GetPosition().y;
        leftPlayer->SetY(temp += PlayerSpeed * deltatime.GetSeconds());
    }
    if (MPE::Input::IsKeyPressed(leftPlayer->GetPlayerDown()))
    {
        float temp = leftPlayer->GetPosition().y;
        leftPlayer->SetY(temp -= PlayerSpeed * deltatime.GetSeconds());
    }
    // RIGHT PLAYER
    if (MPE::Input::IsKeyPressed(rightPlayer->GetPlayerUp()))
    {
        float temp = rightPlayer->GetPosition().y;
        rightPlayer->SetY(temp += PlayerSpeed * deltatime.GetSeconds());
    }
    if (MPE::Input::IsKeyPressed(rightPlayer->GetPlayerDown()))
    {
        float temp = rightPlayer->GetPosition().y;
        rightPlayer->SetY(temp -= PlayerSpeed * deltatime.GetSeconds());
    }
}

void Game::CheckPlayerBounds()
{
    auto boundOffset = 0.5f;

    // LEFT PLAYER
    if (leftPlayer->GetPosition().y >= (Bounds.y / boundOffset))
    {
        leftPlayer->SetY(Bounds.y / boundOffset);
    }
    if (leftPlayer->GetPosition().y <= (-Bounds.y / boundOffset))
    {
        leftPlayer->SetY(-Bounds.y / boundOffset);
    }
    // RIGHT PLAYER
    if (rightPlayer->GetPosition().y >= (Bounds.y / boundOffset))
    {
        rightPlayer->SetY(Bounds.y / boundOffset);
    }
    if (rightPlayer->GetPosition().y <= (-Bounds.y / boundOffset))
    {
        rightPlayer->SetY(-Bounds.y / boundOffset);
    }
}

}