#include "Pong.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace PONG
{
Pong::Pong() : Layer("Sandbox2D"), SYS_CAMERA_CONTROLLER(1920.0f / 1080.0f, true)
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
    ImGui::Begin("PONG MENU");
    ImGui::ColorEdit4("CLEAR COLOR", glm::value_ptr(CLEAR_COLOR));

    ImGui::Separator();
    ImGui::Text("DEBUG INFO");
    ImGui::Separator();

    ImGui::Text("LEFT PLAYER");
    ImGui::Text("POSITION: (%.5f, %.5f)", LEFT_PLAYER->GetPosition().x, LEFT_PLAYER->GetPosition().y);
    ImGui::Text("SIZE: (%.5f, %.5f)", LEFT_PLAYER->GetSize().x, LEFT_PLAYER->GetSize().y);
    // ImGui::Text("COLOR: (%.5f, %.5f, %.5f, %.5f)", LEFT_PLAYER->GetColor().r, LEFT_PLAYER->GetColor().g, LEFT_PLAYER->GetColor().b,
    // LEFT_PLAYER->GetColor().a);

    ImGui::Separator();

    ImGui::Text("RIGHT PLAYER");
    ImGui::Text("POSITION: (%.5f, %.5f)", RIGHT_PLAYER->GetPosition().x, RIGHT_PLAYER->GetPosition().y);
    ImGui::Text("SIZE: (%.5f, %.5f)", RIGHT_PLAYER->GetSize().x, RIGHT_PLAYER->GetSize().y);
    // ImGui::Text("COLOR: (%.5f, %.5f, %.5f, %.5f)", RIGHT_PLAYER->GetColor().r, RIGHT_PLAYER->GetColor().g, RIGHT_PLAYER->GetColor().b,
    // RIGHT_PLAYER->GetColor().a);

    ImGui::Separator();

    ImGui::Text("BALL");
    ImGui::Text("POSITION: (%.5f, %.5f)", BALL->GetPosition().x, BALL->GetPosition().y);
    ImGui::Text("SIZE: (%.5f, %.5f)", BALL->GetSize().x, BALL->GetSize().y);
    ImGui::Text("RADIUS: %.5f", BALL->GetRadius());

    ImGui::End();
}

void Pong::OnEvent(MPE::Event &event)
{
    // SYS_CAMERA_CONTROLLER.OnEvent(event);
}
}