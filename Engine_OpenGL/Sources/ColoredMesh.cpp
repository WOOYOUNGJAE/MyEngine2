#include "pch.h"
#include "ColoredMesh.h"

void CColoredMesh::Begin_CreateMesh(void* pData)
{
	struct MESH_DESC
	{
		GL::VertexPositionNormalColor* vertexArr;
		UINT uiNumVertices;
	};

	MESH_DESC* pCastedData = reinterpret_cast<MESH_DESC*>(pData);

	glGenBuffers(1, &m_VBO);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)sizeof(GL::VertexPositionNormalColor) * pCastedData->uiNumVertices, pCastedData->vertexArr, GL_STATIC_DRAW); // 메모리 할당과 저장

	// TODO: Make VAO
}

void CColoredMesh::End_CreateMesh(void* pData)
{
}
