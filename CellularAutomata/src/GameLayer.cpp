#include "GameLayer.h"

static glm::vec2 GetMouseViewportPosition(const XYZ::OrthographicCameraController& controller)
{
	auto [x, y] = XYZ::Input::GetMousePosition();
	auto width = XYZ::Application::Get().GetWindow().GetWidth();
	auto height = XYZ::Application::Get().GetWindow().GetHeight();

	auto bounds = controller.GetBounds();
	auto pos = controller.GetCamera().GetPosition();
	x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
	y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
	return { pos.x + x, pos.y + y };
}

GameLayer::GameLayer()
	:
	m_CameraController(16.0f / 9.0f),
	m_MousePosition(0.0f)
{
	auto& app = XYZ::Application::Get();
	app.GetImGuiLayer()->EnableDockspace(false);
	app.GetImGuiLayer()->BlockEvents(false);
}

GameLayer::~GameLayer()
{
	
}

void GameLayer::OnAttach()
{
	m_Texture = XYZ::Texture2D::Create(100, 100, 4, {});
	m_Shader = XYZ::Shader::Create("Assets/Shaders/TestShader.glsl");

	uint8_t* pixels = new uint8_t[100 * 100 * 4];
	memset(pixels, 0, 100 * 100 * sizeof(uint32_t));
	for (size_t i = 0; i < 100 * 100 * 4; i += 4)
	{
		pixels[i]	  = 0xff;
		pixels[i + 3] = 0xff;
	}
	m_Texture->SetData(pixels, 100 * 100 * sizeof(uint32_t));

	XYZ::Renderer::WaitAndRender();
	XYZ::Renderer::BlockRenderThread();
}

void GameLayer::OnDetach()
{

}
void GameLayer::OnUpdate(XYZ::Timestep ts)
{
	m_CameraController.OnUpdate(ts);
	XYZ::Renderer::Clear();
	XYZ::Renderer::SetClearColor({ 0.0f,0.0f,0.0f,1.0f });
	
	m_Shader->Bind();
	m_Texture->Bind();
	XYZ::Renderer::SubmitFullscreenQuad();

	XYZ::Renderer2D::BeginScene(m_CameraController.GetCamera().GetViewProjectionMatrix(), m_CameraController.GetCamera().GetPosition());
	XYZ::Renderer2D::SubmitQuad(glm::vec3(0.0f), glm::vec2(1.0f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
	XYZ::Renderer2D::SubmitCircle(glm::vec3(m_MousePosition, 0.0f), 0.1f, 10);

	XYZ::Renderer2D::Flush();
	XYZ::Renderer2D::FlushLines();
	
	m_Timestep = ts;
	m_RendererStats = XYZ::Renderer2D::GetStats();
	XYZ::Renderer2D::EndScene();	
}
void GameLayer::OnEvent(XYZ::Event& event)
{
	m_CameraController.OnEvent(event);
}
void GameLayer::OnImGuiRender()
{
	if (ImGui::Begin("Debug"))
	{
		ImGui::Text("Performance: ");
		ImGui::SameLine();
		ImGui::Text("%f s", m_Timestep);
	
		ImGui::Text("Quad Drawcalls: ");
		ImGui::SameLine();
		ImGui::Text("%u", m_RendererStats.DrawCalls);
	
		ImGui::Text("Line Drawcalls: ");
		ImGui::SameLine();
		ImGui::Text("%u", m_RendererStats.LineDrawCalls);
	
		m_MousePosition = GetMouseViewportPosition(m_CameraController);
	}
	ImGui::End();
}