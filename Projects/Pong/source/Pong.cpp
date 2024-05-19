#include "Pong.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace PONG
{
Pong::Pong() : Layer("Sandbox2D"), SYS_CAMERA_CONTROLLER(1280.0f / 720.0f, true)
// LEFT_PLAYER(nullptr), RIGHT_PLAYER(nullptr),
// BALL(glm::vec2(0.0f, 0.0f), glm::vec2(0.25f, 0.25f), "Data/Textures/Ball.png"),
// LEFT_PLAYER(glm::vec2(-22.0f, 0.0f), glm::vec2(0.5f, 5.0f), PONG::KeyMap(MPE_KEY_W, MPE_KEY_S)),
// RIGHT_PLAYER(glm::vec2(22.0f, 0.0f), glm::vec2(0.5f, 5.0f), PONG::KeyMap(MPE_KEY_UP, MPE_KEY_DOWN)),
//   PongGame( PONG::Player(glm::vec2(-22.0f, 0.0f), glm::vec2(0.5f, 5.0f), PONG::KeyMap(MPE_KEY_W, MPE_KEY_S)),
//       PONG::Player(glm::vec2(22.0f, 0.0f), glm::vec2(0.5f, 5.0f), PONG::KeyMap(MPE_KEY_UP, MPE_KEY_DOWN)),
//       PONG::Ball(glm::vec2(0.0f, 0.0f), glm::vec2(0.25f, 0.25f), "Data/Textures/Ball.png"))

{
    SYS_CAMERA_CONTROLLER.SetZoomLevel(16.0f);

    BOUNDS = SYS_CAMERA_CONTROLLER.GetBounds();

    // PongGame.SetBounds(BOUNDS);

    // LEFT_PLAYER = PongGame.GetLeftPlayer();
    // RIGHT_PLAYER = PongGame.GetRightPlayer();
    // BALL = PongGame.GetBall();

    LEFT_PLAYER = new PONG::Player(glm::vec2(-22.0f, 0.0f), glm::vec2(0.5f, 5.0f), PONG::KeyMap(MPE_KEY_W, MPE_KEY_S));
    RIGHT_PLAYER = new PONG::Player(glm::vec2(22.0f, 0.0f), glm::vec2(0.5f, 5.0f), PONG::KeyMap(MPE_KEY_UP, MPE_KEY_DOWN));

    BALL = new PONG::Ball(glm::vec2(0.0f, 0.0f), glm::vec2(0.25f, 0.25f), "Data/Textures/Ball.png");
    PongGame = new PONG::Game(LEFT_PLAYER, RIGHT_PLAYER, BALL, BOUNDS);
    // PongGame(LEFT_PLAYER, RIGHT_PLAYER, BALL);
}

void Pong::OnAttach() {}

void Pong::OnDetach() {}

void Pong::OnUpdate(MPE::Time deltatime)
{
    PongGame->OnUpdate(deltatime);
    // LEFT_PLAYER->OnUpdate(deltatime);
    // RIGHT_PLAYER->OnUpdate(deltatime);
    // SYS_CAMERA_CONTROLLER.OnUpdate(deltatime);

    MPE::RenderPrimitive::SetClearColor(CLEAR_COLOR);
    MPE::RenderPrimitive::Clear();

    MPE::Renderer2D::BeginScene(SYS_CAMERA_CONTROLLER.GetCamera());

    MPE::Renderer2D::DrawQuad(LEFT_PLAYER->GetPosition(), LEFT_PLAYER->GetSize(), LEFT_PLAYER->GetColor());
    MPE::Renderer2D::DrawQuad(RIGHT_PLAYER->GetPosition(), RIGHT_PLAYER->GetSize(), RIGHT_PLAYER->GetColor());

    MPE::Renderer2D::DrawQuad(BALL->GetPosition(), BALL->GetSize(), BALL->GetTexture());

    MPE::Renderer2D::EndScene();

    // MPE_INFO("LEFT POS: {0}", LEFT_PLAYER->GetPosition().y);
    // MPE_INFO("BOUND: {0}", BOUNDS.y);
}

void Pong::OnImGuiRender()
{
    ImGui::Begin("TETRIS MENU");
    ImGui::ColorEdit4("CLEAR COLOR", glm::value_ptr(CLEAR_COLOR));
    ImGui::End();
}

void Pong::OnEvent(MPE::Event &event)
{
    // SYS_CAMERA_CONTROLLER.OnEvent(event);
}
}