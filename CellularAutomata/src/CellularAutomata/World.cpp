#include "World.h"

static std::pair<int32_t, int32_t> WorldPositionToGridCoords(const glm::vec2& pos, uint32_t width, uint32_t height, const glm::vec2& cellSize, const glm::vec2& center)
{
	glm::vec2 leftBottom = center - glm::vec2(width, height) / 2.0f;
	glm::vec2 coords = pos - leftBottom;

	return {
		(int32_t)(std::floor(coords.x / cellSize.x)),
		(int32_t)(std::floor(coords.y / cellSize.y))
	};
}
static uint32_t GetIndex(uint32_t width, uint32_t x, uint32_t y)
{
	return (y * width) + x;
}

World::World()
{
	m_LoadedChunks.emplace_back(glm::vec2(0.0f));
	//m_LoadedChunks.emplace_back(glm::vec2(-0.5f, 0.5f));
	//m_LoadedChunks.emplace_back(glm::vec2( 0.5f));
	//m_LoadedChunks.emplace_back(glm::vec2( 0.5f, -0.5f));

	m_Materials[SandMaterialType] = &m_SandMaterial;
	m_ReadParticles.resize(Chunk::sc_ChunkSize.x * Chunk::sc_ChunkSize.y);
	m_WriteParticles.resize(Chunk::sc_ChunkSize.x * Chunk::sc_ChunkSize.y);
}

void World::Update(const glm::vec2& mousePosition)
{
	if (XYZ::Input::IsMouseButtonPressed(XYZ::MouseCode::MOUSE_BUTTON_LEFT))
	{
		glm::vec2 cellSize = { 1.0f / (float)Chunk::sc_ChunkSize.x, 1.0f / (float)Chunk::sc_ChunkSize.y };
		for (size_t i = 0; i < m_LoadedChunks.size(); ++i)
		{
			auto [xCoord, yCoord] = WorldPositionToGridCoords(mousePosition, 1, 1, cellSize, m_LoadedChunks[i].GetPosition());
			if (xCoord >= 0 && yCoord >= 0 && xCoord < Chunk::sc_ChunkSize.x && yCoord < Chunk::sc_ChunkSize.y)
			{
				uint32_t index = GetIndex(Chunk::sc_ChunkSize.x, xCoord, yCoord);
				m_ReadParticles[index].Active = true;		
				//m_LoadedChunks[i].SetPixel(xCoord, yCoord, { 255, 255, 0, 255 });
			}
		}
	}


	for (uint32_t x = 0; x < Chunk::sc_ChunkSize.x; ++x)
	{
		for (uint32_t y = 0; y < Chunk::sc_ChunkSize.y; ++y)
		{
			auto& p = m_ReadParticles[GetIndex(Chunk::sc_ChunkSize.x, x, y)];
			m_Materials[p.MaterialType]->Update(m_ReadParticles, m_WriteParticles, x, y);
		}
	}
	for (uint32_t x = 0; x < Chunk::sc_ChunkSize.x; ++x)
	{
		for (uint32_t y = 0; y < Chunk::sc_ChunkSize.y; ++y)
		{
			auto& p = m_WriteParticles[GetIndex(Chunk::sc_ChunkSize.x, x, y)];
			if (p.Active)
				m_LoadedChunks[0].SetPixel(x, y, { 255, 255, 0, 255 });
		}
	}
	std::swap(m_ReadParticles, m_WriteParticles);
}

void World::Render(const XYZ::OrthographicCamera& camera)
{
	XYZ::Renderer::Clear();
	XYZ::Renderer::SetClearColor({ 0.1f,0.1f,0.1f,1.0f });
	XYZ::Renderer2D::BeginScene(camera.GetViewProjectionMatrix(), camera.GetPosition());
	
	for (auto& chunk : m_LoadedChunks)
		chunk.Render();

	XYZ::Renderer2D::Flush();
	XYZ::Renderer2D::FlushLines();

	XYZ::Renderer2D::EndScene();
}
