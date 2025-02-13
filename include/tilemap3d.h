#ifndef TILEMAP_3D_H
#define TILEMAP_3D_H

#include "game_math.h"
#include <stdbool.h>

typedef struct
{
    u8 id : 4;
    u8 runLength : 4;
} TileRLE;

typedef struct 
{
    u8 x : 3;
    u8 y : 2;
    u8 z : 3;
} ChunkCoord;

typedef struct
{
    ChunkCoord coord;
    TileRLE* tiles;
} Chunk;

typedef struct
{
    Chunk** chunks;
    u8 chunkCount;
} Tilemap3D;

inline bool IsChunkHere(Chunk* chunk, u8 x, u8 y, u8 z)
{
    return chunk->coord.x == x && chunk->coord.y == y && chunk->coord.z == z;
}

bool IsCoordValid(u8 x, u8 y, u8 z);

bool IsChunkValid(Tilemap3D* map, u8 x, u8 y, u8 z);

Chunk* ChunkGet(Tilemap3D* map, u8 x, u8 y, u8 z);

#endif // TILEMAP_3D_H