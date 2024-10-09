#pragma once
#include "Engine_Common/Includes/Structs.h"

namespace Engine_Common
{
	struct MESH_DESC_BASIC;
}


inline void Move_MeshDesc_Basic(GL::VertexPositionNormalColorTexture* dstVertexArr, Engine_Common::MESH_DESC_BASIC* pMeshDesc)
{
	UINT uiNumVertices = pMeshDesc->uiNumVertices;
	size_t ullVertexSize = sizeof(GL::VertexPositionNormalColorTexture);
	BYTE* byDstStart = (BYTE*)dstVertexArr;
	UINT uiPositionOffset = 0;
	UINT uiNormalOffset = sizeof(vec3);
	UINT uiColorOffset = uiNormalOffset + sizeof(vec3);
	UINT uiTexCoordOffset = uiColorOffset + sizeof(vec4);
	for (UINT i = 0; i < uiNumVertices; ++i)
	{
		BYTE* byCurDst = byDstStart + ullVertexSize * i;
		memcpy_s(byCurDst + uiPositionOffset, sizeof(vec3), pMeshDesc->fPositionArr + sizeof(FLOAT) * 3 * i, sizeof(vec3));
		memcpy_s(byCurDst + uiNormalOffset, sizeof(vec3), pMeshDesc->fNormalArr + sizeof(FLOAT) * 3 * i, sizeof(vec3));
		memcpy_s(byCurDst + uiColorOffset, sizeof(vec4), pMeshDesc->fColorArr + sizeof(FLOAT) * 4 * i, sizeof(vec2));
		memcpy_s(byCurDst + uiTexCoordOffset, sizeof(vec2), pMeshDesc->fTexCoordArr + sizeof(FLOAT) * 2 * i, sizeof(vec2));
	}
}