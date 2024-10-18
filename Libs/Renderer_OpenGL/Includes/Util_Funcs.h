#pragma once
#include "Renderer_Common/Includes/Structs.h"

namespace Renderer_Common
{
	struct MESH_DESC_BASIC;
}


inline void Copy_MeshDesc_Basic(GL::VertexPositionNormalColorTexture* dstVertexArr, Renderer_Common::MESH_DESC_BASIC* pMeshDesc)
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
		memcpy_s(byCurDst + uiPositionOffset, sizeof(vec3), (BYTE*)pMeshDesc->fPositionArr + sizeof(vec3) * i, sizeof(vec3));
		memcpy_s(byCurDst + uiNormalOffset, sizeof(vec3), (BYTE*)pMeshDesc->fNormalArr + sizeof(vec3) * i, sizeof(vec3));
		memcpy_s(byCurDst + uiColorOffset, sizeof(vec4), (BYTE*)pMeshDesc->fColorArr + sizeof(vec4) * i, sizeof(vec4));
		memcpy_s(byCurDst + uiTexCoordOffset, sizeof(vec2), (BYTE*)pMeshDesc->fTexCoordArr + sizeof(vec2) * i, sizeof(vec2));
	}
}

inline void Convert_Matrix_DXtoGL(XMFLOAT4X4& mat)
{
	// Convert Look Direction
	mat._31 *= -1;
	mat._32 *= -1;
	mat._33 *= -1;
	mat._34 *= -1;

	// Convert Position Z
	mat._43 *= -1;
}