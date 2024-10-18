#include "Pong.h"

#include <imgui.h>
#include "MPE/Vendor/GLM/GLM.h"

namespace PONG
{
Pong::Pong()
    : Layer("Sandbox2D"),
      SYS_TEXT_RENDERER("Data/Shaders/Text/Text.glsl", "Data/Fonts/Hack_v3_003/Hack-Regular.ttf", 64),
      TEXT_COLOR{0.88f, 0.59f, 0.07f, 0.75f},
      TEXT_BOX_LOCATION_PLAYER_1{0.1f, 0.9f},
      TEXT_BOX_LOCATION_PLAYER_2{0.9f, 0.9f}
{
    m_ECS = MPE::NEWREF<MPE::ECS::ECS>();

    SYS_CAMERA_CONTROLLER = MPE::NEWREF<MPE::OrthographicCameraController>(*m_ECS, MPE::NEWREF<MPE::OrthographicCamera>(*m_ECS, -30.0f, 30.0f, -30.0f, 30.0f));

    // SYS_CAMERA_CONTROLLER.SetZoomLevel(16.0f);
    SYS_CAMERA_CONTROLLER->GetOrthographicCameraControllerComponent()->SetZoomLevel(16.0f);

    // BOUNDS = SYS_CAMERA_CONTROLLER.GetBounds();
    BOUNDS = SYS_CAMERA_CONTROLLER->GetOrthographicCameraControllerComponent()->GetBounds();

    PlaceText();

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

void Pong::OnUpdate(MPE::Time deltaTime)
{
    // SYS_CAMERA_CONTROLLER.OnUpdate(deltaTime);
    PongGame->OnUpdate(deltaTime);
    // LEFT_PLAYER->OnUpdate(deltaTime);
    // RIGHT_PLAYER->OnUpdate(deltaTime);
    // SYS_CAMERA_CONTROLLER.OnUpdate(deltaTime);

    TEXT_PLAYER_1 = std::to_string(LEFT_PLAYER->GetScore());
    TEXT_PLAYER_2 = std::to_string(RIGHT_PLAYER->GetScore());

    if (p2_previous_score != RIGHT_PLAYER->GetScore())
    {
        p2_previous_score = RIGHT_PLAYER->GetScore();
        PlaceText();
    }

    MPE::RenderPrimitive::SetClearColor(CLEAR_COLOR);
    MPE::RenderPrimitive::Clear();

    {
        // SYS_TEXT_RENDERER.RenderAllASCII(500.0f, 500.0f, 1.0f, glm::vec4(0.88f, 0.59f, 0.07f, 1.0f));
        SYS_TEXT_RENDERER.RenderText(TEXT_PLAYER_1, TEXT_BOX_LOCATION_PLAYER_1[0], TEXT_BOX_LOCATION_PLAYER_1[1], 1.0f,
                                     glm::vec4(TEXT_COLOR[0], TEXT_COLOR[1], TEXT_COLOR[2], TEXT_COLOR[3]));
        SYS_TEXT_RENDERER.RenderText(TEXT_PLAYER_2, TEXT_BOX_LOCATION_PLAYER_2[0], TEXT_BOX_LOCATION_PLAYER_2[1], 1.0f,
                                     glm::vec4(TEXT_COLOR[0], TEXT_COLOR[1], TEXT_COLOR[2], TEXT_COLOR[3]));
        SYS_TEXT_RENDERER.RenderText("F11 - HIDE GUI", 0.0f, 1.0f, 0.3f, glm::vec4(TEXT_COLOR[0], TEXT_COLOR[1], TEXT_COLOR[2], TEXT_COLOR[3]));
    }

    MPE::Renderer2D::BeginScene(SYS_CAMERA_CONTROLLER->GetOrthographicCamera()->GetCameraComponent()->GetProjectionViewMatrix());

    MPE::Renderer2D::DrawQuad(LEFT_PLAYER->GetPosition(), LEFT_PLAYER->GetSize(), LEFT_PLAYER->GetColor());
    MPE::Renderer2D::DrawQuad(RIGHT_PLAYER->GetPosition(), RIGHT_PLAYER->GetSize(), RIGHT_PLAYER->GetColor());

    MPE::Renderer2D::DrawQuad(glm::vec3(BALL->GetPosition(), 0.0f), BALL->GetSize(), BALL->GetTexture());

    MPE::Renderer2D::EndScene();

    // MPE_INFO("LEFT POS: {0}", LEFT_PLAYER->GetPosition().y);
    // MPE_INFO("BOUND: {0}", BOUNDS.y);
}

void Pong::OnImGuiRender()
{
    ImGui::Begin("PONG MENU");
    ImGui::ColorEdit4("CLEAR COLOR", glm::value_ptr(CLEAR_COLOR));

    ImGui::Separator();

    ImGui::Text("SCORE");
    ImGui::Text("LEFT: %d", LEFT_PLAYER->GetScore());
    ImGui::Text("RIGHT: %d", RIGHT_PLAYER->GetScore());

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

    ImGui::Separator();

    ImGui::Text("TEXT VARIABLES");

    static char buffer[256];
    strncpy(buffer, TEXT_PLAYER_1.c_str(), sizeof(buffer));
    buffer[sizeof(buffer) - 1] = 0;

    if (ImGui::InputText("TEXT_PLAYER_1", buffer, sizeof(buffer)))
    {
        TEXT_PLAYER_1 = std::string(buffer);
    }

    static char buffer2[256];
    strncpy(buffer2, TEXT_PLAYER_2.c_str(), sizeof(buffer2));
    buffer2[sizeof(buffer2) - 1] = 0;

    if (ImGui::InputText("TEXT_PLAYER_2", buffer2, sizeof(buffer2)))
    {
        TEXT_PLAYER_2 = std::string(buffer);
    }

    ImGui::ColorEdit4("TEXT COLOR", TEXT_COLOR);
    ImGui::SliderFloat("[X] [P1] TEXT BOX LOCATION", &TEXT_BOX_LOCATION_PLAYER_1[0], 0.0f, 1920.0f);
    ImGui::SliderFloat("[Y] [P1] TEXT BOX LOCATION", &TEXT_BOX_LOCATION_PLAYER_1[1], 0.0f, 1080.0f);
    ImGui::SliderFloat("[X] [P2] TEXT BOX LOCATION", &TEXT_BOX_LOCATION_PLAYER_2[0], 0.0f, 1920.0f);
    ImGui::SliderFloat("[Y] [P2] TEXT BOX LOCATION", &TEXT_BOX_LOCATION_PLAYER_2[1], 0.0f, 1080.0f);

    bool pixelAlign = SYS_TEXT_RENDERER.GetPixelAlign();
    ImGui::Checkbox("Pixel Align", &pixelAlign);
    SYS_TEXT_RENDERER.SetPixelAlign(pixelAlign);

    int fontSize = SYS_TEXT_RENDERER.GetFontSize();
    ImGui::SliderInt("Font Size", &fontSize, 1.0, 128.0);
    SYS_TEXT_RENDERER.SetFontSize(fontSize);

    ImGui::End();
}

void Pong::OnEvent(MPE::Event& event)
{
    MPE::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MPE::WindowResizeEvent>(MPE_BIND_EVENT_FUNCTION(Pong::OnWindowResize));

    SYS_CAMERA_CONTROLLER->OnEvent(event);
    SYS_TEXT_RENDERER.OnEvent(event);
    // OnWindowResize(event);
}

void Pong::PlaceText()
{
    // Orient text so that they are always at the corners of the screen
    float windowSize[2] = {(float) MPE::App::GetApp().GetWindow()->GetWidth(), (float) MPE::App::GetApp().GetWindow()->GetHeight()};
    // P1 is always at the top left corner - no need to account for character amount
    TEXT_BOX_LOCATION_PLAYER_1[0] = 0.1f;
    TEXT_BOX_LOCATION_PLAYER_1[1] = windowSize[1] - 50.0f;
    // P2 is always at the top right corner - need to account for character amount so that the text doesn't go off screen
    // Adjust for each character in the string
    TEXT_BOX_LOCATION_PLAYER_2[0] = windowSize[0] - (TEXT_PLAYER_2.size() * 40.0f);
    // TEXT_BOX_LOCATION_PLAYER_2[0] = windowSize[0] - 50.0f;
    TEXT_BOX_LOCATION_PLAYER_2[1] = windowSize[1] - 50.0f;

    // MPE_WARN("Window Width: {0}, Window Height: {1}", windowSize[0], windowSize[1]);
    // MPE_WARN("TEXT BOX LOCATIONS: P1: ({0}, {1}), P2: ({2}, {3})", TEXT_BOX_LOCATION_PLAYER_1[0], TEXT_BOX_LOCATION_PLAYER_1[1],
    // TEXT_BOX_LOCATION_PLAYER_2[0],
    //          TEXT_BOX_LOCATION_PLAYER_2[1]);
}

bool Pong::OnWindowResize(MPE::WindowResizeEvent& e)
{
    PlaceText();

    return true;
}
}