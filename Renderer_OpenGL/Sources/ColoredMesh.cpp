#include "pch.h"
#include "ColoredMesh.h"


CColoredMesh::CColoredMesh()
{
	m_iVertexStride = sizeof(GL::VertexPositionNormalColor);
}

void CColoredMesh::Begin_CreateMesh(void* pData)
{
	struct MESH_DESC
	{
		GL::VertexPositionNormalColor* vertexArr;
		uint uiNumVertices;
		uint* indexArr;
		uint uiNumIndices;
	};

	MESH_DESC* pCastedData = reinterpret_cast<MESH_DESC*>(pData);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)sizeof(GL::VertexPositionNormalColor) * pCastedData->uiNumVertices, pCastedData->vertexArr, GL_STATIC_DRAW); // 메모리 할당과 저장

	// VAO
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, m_iVertexStride, (void*)0); // POSITION
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, m_iVertexStride, (void*)(0 + sizeof(vec3))); // NORMAL
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, m_iVertexStride, (void*)(0 + sizeof(vec3) + sizeof(vec3))); // COLOR
	glEnableVertexAttribArray(2);


	// EBO
	glGenVertexArrays(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * pCastedData->uiNumIndices, pCastedData->indexArr, GL_STATIC_DRAW);

}

void CColoredMesh::End_CreateMesh(void* pData)
{
	glBindVertexArray(0); // Unbind VAO
} 
