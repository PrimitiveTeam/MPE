#include "MPE/MPE.h"

#include "Core/_INCLUDE.h"
#include "MPE/Events/EventApp.h"

#ifdef MPE_OPENGL
#    include "MPE/MPE_GFX_OPEN_GL.h"
#elif MPE_OPENGLES
#    include "MPE/MPE_GFX_OPEN_GLES.h"
#endif

namespace PONG
{
class Pong : public MPE::Layer
{
  private:
    MPE::StaticOrthographicCamera SYS_CAMERA_CONTROLLER;
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

    // TEXT
#ifdef MPE_OPENGL
    MPE::OpenGLTextRenderer SYS_TEXT_RENDERER;
#elif MPE_OPENGLES
    MPE::OpenGLESTextRenderer SYS_TEXT_RENDERER;
#endif

    std::string TEXT_PLAYER_1 = "0";
    std::string TEXT_PLAYER_2 = "0";
    float TEXT_COLOR[4];
    float TEXT_BOX_LOCATION_PLAYER_1[2];
    float TEXT_BOX_LOCATION_PLAYER_2[2];
    uint16_t p2_previous_score = 0;
    // TEXT

  private:
    void PlaceText();

  public:
    Pong();

    virtual ~Pong() = default;

    virtual void OnAttach() override;

    virtual void OnDetach() override;

    virtual void OnUpdate(MPE::Time deltaTime) override;

    virtual void OnImGuiRender() override;

    virtual void OnEvent(MPE::Event &event) override;

    bool OnWindowResize(MPE::WindowResizeEvent &e);
};
}
