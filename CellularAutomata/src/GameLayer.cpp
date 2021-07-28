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
	auto& app = XYZ::Application::Get();
	XYZ::Renderer::WaitAndRender();
	XYZ::Renderer::BlockRenderThread();
}

void GameLayer::OnDetach()
{

}
void GameLayer::OnUpdate(XYZ::Timestep ts)
{
	m_MousePosition = GetMouseViewportPosition(m_CameraController);
	m_CameraController.OnUpdate(ts);
	m_World.Update(m_MousePosition);
	m_World.Render(m_CameraController.GetCamera());
	
	m_MousePosition = GetMouseViewportPosition(m_CameraController);
}
void GameLayer::OnEvent(XYZ::Event& event)
{
	m_CameraController.OnEvent(event);
}
void GameLayer::OnImGuiRender()
{
	displayStats();
}

void GameLayer::displayStats()
{
	if (ImGui::Begin("Stats"))
	{
		const auto& stats = XYZ::Renderer::GetStats();
		ImGui::Text("Draw Arrays: %d", stats.DrawArraysCount);
		ImGui::Text("Draw Indexed: %d", stats.DrawIndexedCount);
		ImGui::Text("Draw Instanced: %d", stats.DrawInstancedCount);
		ImGui::Text("Draw Fullscreen: %d", stats.DrawFullscreenCount);
		ImGui::Text("Draw Indirect: %d", stats.DrawIndirectCount);
		ImGui::Text("Commands Count: %d", stats.CommandsCount);
	}
	ImGui::End();
}
