#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 128

typedef union
{
    struct
    {
        float x, y, z;
    };
    float v[3];
} Vec3;

typedef struct
{
    uint16_t indices[4];
} Tri;

typedef struct
{
    uint16_t vtxCount;
    Vec3* vtx;
    uint16_t nrmCount;
    Vec3* nrms;
    uint16_t triCount;
    Tri* tris;
} MeshData;


void parse_obj(const char* fileName, MeshData* mesh)
{
    FILE* file = fopen(fileName, "r");
    if(!file)
    {
        fprintf(stderr, "Failed to open file: %s\n", fileName);
        exit(1);
    }
    char line[MAX_LINE_LEN];
    while(fgets(line, sizeof(line), file))
    {
        if(strncmp(line, "v ", 2) == 0)
        {
            mesh->vtxCount++;
        }
        else if (strncmp(line, "vn ", 3) == 0)
        {
            mesh->nrmCount++;
        }
        else if (strncmp(line, "f ", 2) == 0)
        {
            mesh->triCount++;
        }
    }

    mesh->vtx = calloc(mesh->vtxCount, sizeof(Vec3));//malloc(mesh->vtxCount * sizeof(Vec3));
    if (mesh->vtx == NULL)
    {
        fprintf(stderr, "Memory allocation failed for vertices!\n");
        exit(1);
    }
    mesh->nrms = calloc(mesh->nrmCount, sizeof(Vec3));
    if (mesh->nrms == NULL)
    {
        fprintf(stderr, "Memory allocation failed for normals!\n");
        exit(1);
    }
    mesh->tris = calloc(mesh->triCount, sizeof(Tri));
    if (mesh->tris == NULL)
    {
        fprintf(stderr, "Memory allocation failed for tris!\n");
        exit(1);
    }
    printf("%d, %d, %d\n", mesh->vtxCount, mesh->nrmCount, mesh->triCount);
    uint32_t vtxIdx = 0;
    uint32_t nrmIdx = 0;
    uint32_t triIdx = 0;

    fseek(file, 0, SEEK_SET);
    while (fgets(line, sizeof(line), file))
    {
        if (strncmp(line, "v ", 2) == 0)
        {

            sscanf(line + 2, "%f %f %f", &mesh->vtx[vtxIdx].x, &mesh->vtx[vtxIdx].y &mesh->vtx[vtxIdx].z);
            vtxIdx++;
        }
        else if (strncmp(line, "vn ", 3) == 0)
        {

            sscanf(line + 3, "%f %f %f", &mesh->nrms[nrmIdx].x, &mesh->nrms[nrmIdx].y, &mesh->nrms[nrmIdx].z);
            nrmIdx++;
        }
        else if (strncmp(line, "f ", 2) == 0)
        {

            sscanf(line + 2,
                "%d//%d %d//%*d %d//%*d",
                &mesh->tris[triIdx].indices[0],
                &mesh->tris[triIdx].indices[3],
                &mesh->tris[triIdx].indices[1],
                &mesh->tris[triIdx].indices[2]
            );
            triIdx++;
        }
        
    }
    fclose(file);
}

void write_coll(const char* fileName, MeshData* mesh)
{
    FILE* file = fopen(fileName, "wb");
    fwrite(&mesh->vtxCount, sizeof(uint32_t), 1, file);
    fwrite(mesh->vtx, sizeof(Vec3), mesh->vtxCount, file);
    fwrite(&mesh->nrmCount, sizeof(uint32_t), 1, file);
    fwrite(mesh->nrms, sizeof(Vec3), mesh->nrmCount, file);
    fwrite(&mesh->triCount, sizeof(uint32_t), 1, file);
    fwrite(mesh->tris, sizeof(Tri), mesh->triCount, file);
    fclose(file);
}

void mesh_free(MeshData* mesh)
{
    free(mesh->vtx);
    free(mesh->nrms);
    free(mesh->tris);
}

int main(int argc, char* argv[])
{
    MeshData mesh = { 0 };
    parse_obj(argv[1], &mesh);

    write_coll(argv[2], &mesh);

    mesh_free(&mesh);
    return 0;
}