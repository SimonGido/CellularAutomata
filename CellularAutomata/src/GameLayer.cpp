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

static std::pair<int32_t, int32_t> WorldPositionToGridCoords(const glm::vec2& pos, uint32_t width, uint32_t height, const glm::vec2& cellSize, const glm::vec2& center)
{
	glm::vec2 leftBottom = center - glm::vec2(width, height) / 2.0f;
	glm::vec2 coords = pos - leftBottom;

	return {
		(int32_t)(std::floor(coords.x / cellSize.x)),
		(int32_t)(std::floor(coords.y / cellSize.y))
	};
}

GameLayer::GameLayer()
	:
	m_CameraController(16.0f / 9.0f),
	m_MousePosition(0.0f),
	m_Chunks{
		Chunk(glm::vec2(-0.5f)),
		Chunk(glm::vec2(-0.5f, 0.5f)),
		Chunk(glm::vec2(0.5f)),
		Chunk(glm::vec2(0.5f, -0.5f))
	}
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
	XYZ::Renderer::Clear();
	XYZ::Renderer::SetClearColor({ 0.1f,0.1f,0.1f,1.0f });
	

	XYZ::Renderer2D::BeginScene(m_CameraController.GetCamera().GetViewProjectionMatrix(), m_CameraController.GetCamera().GetPosition());
	XYZ::Renderer2D::SubmitCircle(glm::vec3(m_MousePosition, 0.0f), 0.1f, 10);

	for (size_t i = 0; i < 4; ++i)
		m_Chunks[i].Render();

	XYZ::Renderer2D::Flush();
	XYZ::Renderer2D::FlushLines();
	
	m_MousePosition = GetMouseViewportPosition(m_CameraController);
	XYZ::Renderer2D::EndScene();	
	
	if (XYZ::Input::IsMouseButtonPressed(XYZ::MouseCode::MOUSE_BUTTON_LEFT))
	{
		glm::vec2 cellSize = { 1.0f / (float)Chunk::sc_ChunkSize.X, 1.0f / (float)Chunk::sc_ChunkSize.Y };
		for (size_t i = 0; i < 4; ++i)
		{
			auto [xCoord, yCoord] = WorldPositionToGridCoords(m_MousePosition, 1, 1, cellSize, m_Chunks[i].GetPosition());
			if (xCoord >= 0 && yCoord >= 0)
				m_Chunks[i].SetCircle(xCoord, yCoord, 10, { 255, 0, 0, 255 });
		}
	}
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
