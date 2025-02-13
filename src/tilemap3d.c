#include "tilemap3d.h"


bool IsCoordValid(u8 x, u8 y, u8 z)
{
    if (x >= 8 || y >= 4 || z >= 8)
    {
        return false;
    }
    return true;
}

bool IsChunkValid(Tilemap3D* map, u8 x, u8 y, u8 z)
{
    if (map->chunkCount == 0 || !map || !map->chunks)
    {
        return false;
    }
    if (x >= 8 || y >= 4 || z >= 8)
    {
        return false;
    }
    return true;
}

Chunk* ChunkGet(Tilemap3D* map, u8 x, u8 y, u8 z)
{
    if (!IsChunkValid(map, x, y, z))
    {
        return NULL;
    }
    for (u8 i = 0; i < map->chunkCount; i++)
    {
        Chunk* chunk = map->chunks[i];
        if (IsChunkHere(chunk, x, y, z))
        {
            return chunk;
        }
    }
    return NULL;
}