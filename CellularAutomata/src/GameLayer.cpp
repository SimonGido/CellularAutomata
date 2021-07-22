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
	m_MousePosition(0.0f),
	m_Pixels(nullptr),
	m_PixelsDirty(false)
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
	auto& app = XYZ::Application::Get();
	m_Texture = XYZ::Texture2D::Create(app.GetWindow().GetWidth(), app.GetWindow().GetHeight(), 4, {});
	m_Shader = XYZ::Shader::Create("Assets/Shaders/TestShader.glsl");

	m_Pixels = new uint8_t[m_Texture->GetWidth() * m_Texture->GetHeight() * 4];
	memset(m_Pixels, 0, m_Texture->GetWidth() * m_Texture->GetHeight() * sizeof(uint32_t));	
	m_Texture->SetData(m_Pixels, m_Texture->GetWidth() * m_Texture->GetHeight() * sizeof(uint32_t));


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
	XYZ::Renderer::SetClearColor({ 0.1f,0.1f,0.1f,1.0f });
	
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

	if (XYZ::Input::IsMouseButtonPressed(XYZ::MouseCode::MOUSE_BUTTON_LEFT))
	{
		auto& app = XYZ::Application::Get();
		auto [mx, my] = XYZ::Input::GetMousePosition();
		my = app.GetWindow().GetHeight() - my;
		putPixel(mx, my, 0xff, 0, 0, 0xff);
	}
	updateTexture();
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
		ImGui::Text("%f s", m_Timestep.GetSeconds());
	
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

void GameLayer::putPixel(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	static constexpr uint32_t channels = 4;
	if (x < m_Texture->GetWidth() && y < m_Texture->GetHeight())
	{
		uint32_t index = (y * m_Texture->GetWidth() * channels) + (x * channels);
		
		m_Pixels[index] = r;
		m_Pixels[index + 1] = g;
		m_Pixels[index + 2] = b;
		m_Pixels[index + 3] = a;
		m_PixelsDirty = true;
	}
}

void GameLayer::updateTexture()
{
	if (m_PixelsDirty)
	{
		m_Texture->SetData(m_Pixels, m_Texture->GetWidth() * m_Texture->GetHeight() * sizeof(uint32_t));
		m_PixelsDirty = false;
	}
}
