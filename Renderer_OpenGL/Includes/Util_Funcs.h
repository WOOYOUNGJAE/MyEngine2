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

/**
 * @brief Change z direction, memory row to col
 */
inline void Convert_Matrix_DXtoGL(XMFLOAT4X4& mat)
{
	// Convert Look Direction
	mat._31 *= -1;
	mat._32 *= -1;
	mat._33 *= -1;
	mat._34 *= -1;

	// Convert Position Z
	mat._43 *= -1;

	// Reorder the matrix to match OpenGL's column-major order

	XMFLOAT4X4 temp = mat; // Temporary copy to reorder
	mat._11 = temp._11; mat._21 = temp._12; mat._31 = temp._13; mat._41 = temp._14; // 1st column
	mat._12 = temp._21; mat._22 = temp._22; mat._32 = temp._23; mat._42 = temp._24; // 2nd column
	mat._13 = temp._31; mat._23 = temp._32; mat._33 = temp._33; mat._43 = temp._34; // 3rd column
	mat._14 = temp._41; mat._24 = temp._42; mat._34 = temp._43; mat._44 = temp._44; // 4th column

}