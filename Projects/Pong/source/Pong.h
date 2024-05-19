#include "MPE/MPE.h"

#include "Core/_INCLUDE.h"

namespace PONG
{
class Pong : public MPE::Layer
{
  private:
    MPE::OrthographicCameraController SYS_CAMERA_CONTROLLER;
    // glm::vec4 CLEAR_COLOR = {0.5f, 0.25f, 0.5f, 1.0f};
    glm::vec4 CLEAR_COLOR = {0.0f, 0.0f, 0.0f, 1.0f};

    glm::vec4 BOUNDS;

    // PLAYERS
    PONG::Player *LEFT_PLAYER;
    PONG::Player *RIGHT_PLAYER;

    // BALL
    // PONG::Ball *BALL;
    PONG::Ball *BALL;

    PONG::Game *PongGame;

  public:
    Pong();

    virtual ~Pong() = default;

    virtual void OnAttach() override;

    virtual void OnDetach() override;

    virtual void OnUpdate(MPE::Time deltatime) override;

    virtual void OnImGuiRender() override;

    virtual void OnEvent(MPE::Event &event) override;
};
}
