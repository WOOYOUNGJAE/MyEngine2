#pragma once
#include "Common/Includes/Structs.h"

namespace Common
{
	struct MESH_DESC_BASIC;
}


inline void Copy_MeshDesc_Basic(GL::VertexPositionNormalColorTexture* dstVertexArr, Common::MESH_DESC_BASIC* pMeshDesc)
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
inline void Convert_Matrix_DXtoGL(XMFLOAT4X4& srcMat)
{
	// Convert Z Direction
	//srcMat._13 *= -1;
	//srcMat._23 *= -1;
	//srcMat._33 *= -1;

	srcMat._31 *= -1;
	srcMat._32 *= -1;
	srcMat._33 *= -1;

	srcMat._43 *= -1;
}
inline glm::mat4x4 Get_Converted_Matrix_DXtoGL(XMFLOAT4X4& srcMat)
{
	// Convert Z Direction
	srcMat._13 *= -1;
	srcMat._23 *= -1;
	srcMat._33 *= -1;
	srcMat._43 *= -1;

	glm::mat4x4 mat;
	mat = *reinterpret_cast<glm::mat4x4*>(&srcMat);

	return mat;
}