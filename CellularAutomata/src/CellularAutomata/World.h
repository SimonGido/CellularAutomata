#pragma once

#include <XYZ.h>

#include "Chunk.h"
#include "Particle.h"

class World
{
public:
	World();

	void Update(const glm::vec2& mousePosition);
	void Render(const XYZ::OrthographicCamera& camera);
private:
	SandMaterial m_SandMaterial;
	std::vector<Particle> m_ReadParticles;
	std::vector<Particle> m_WriteParticles;

	std::vector<Chunk> m_LoadedChunks;
	std::array<Material*, NumMaterialTypes> m_Materials;
};