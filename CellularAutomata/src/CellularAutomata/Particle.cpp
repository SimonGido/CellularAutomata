#include "Particle.h"

#include "Chunk.h"

static uint32_t GetIndex(uint32_t width, uint32_t x, uint32_t y)
{
	return (y * width) + x;
}


void SandMaterial::Update(std::vector<Particle>& readBuffer, std::vector<Particle>& writeBuffer, uint32_t x, uint32_t y)
{
	size_t index = GetIndex(Chunk::sc_ChunkSize.x, x, y);
	writeBuffer[index].Active = readBuffer[index].Active;
	if (!readBuffer[index].Active)
		return;
	
	if (y > 0)
	{
		uint32_t bottomIndex = GetIndex(Chunk::sc_ChunkSize.x, x, y - 1);
		if (!readBuffer[bottomIndex].Active)
		{
			writeBuffer[bottomIndex].MaterialType = readBuffer[index].MaterialType;
			writeBuffer[bottomIndex].Active = true;
			writeBuffer[index].Active = false;
			return;
		}
		if (x > 0)
		{
			uint32_t bottomLeftIndex = GetIndex(Chunk::sc_ChunkSize.x, x - 1, y - 1);
			if (!readBuffer[bottomLeftIndex].Active)
			{
				writeBuffer[bottomLeftIndex].MaterialType = readBuffer[index].MaterialType;
				writeBuffer[bottomLeftIndex].Active = true;
				writeBuffer[index].Active = false;
				return;
			}
		}
		if (x < Chunk::sc_ChunkSize.x - 1)
		{
			uint32_t bottomRightIndex = GetIndex(Chunk::sc_ChunkSize.x, x + 1, y - 1);
			if (!readBuffer[bottomRightIndex].Active)
			{
				writeBuffer[bottomRightIndex].MaterialType = readBuffer[index].MaterialType;
				writeBuffer[bottomRightIndex].Active = true;
				writeBuffer[index].Active = false;
				return;
			}
		}
	}
}
