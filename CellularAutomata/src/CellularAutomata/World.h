#pragma once

#include <XYZ.h>

#include "Chunk.h"


class World
{
public:
	World();


private:
	std::vector<Chunk> m_LoadedChunks;
};