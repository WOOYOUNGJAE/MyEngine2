#include "pch.h"
#include "BasicMesh.h"
#include "Renderer_Common/Includes/Structs.h"
#include "Util_Funcs.h"


CBasicMesh::CBasicMesh()
{
	m_iVertexStride = sizeof(GL::VertexPositionNormalColorTexture);
}

void CBasicMesh::Begin_CreateMesh(void* pData)
{
	using namespace Renderer_Common;

	CREATE_MESHES_DESC* pCastedData = reinterpret_cast<CREATE_MESHES_DESC*>(pData);
	MESH_DESC_BASIC** pMeshDataArr = pCastedData->pBasicMeshDataArrPtr;
	MESH_DESC_BASIC* pCurMeshData = pMeshDataArr[0];

	uint uiPosArrIndex = 0;
	uint uiNormalArrIndex = 0;
	uint uiColorArrIndex = 0;
	uint uiTexCoordArrIndex = 0;

	m_pVertexArr = new GL::VertexPositionNormalColorTexture[pCurMeshData->uiNumVertices];
	::Move_MeshDesc_Basic(reinterpret_cast<GL::VertexPositionNormalColorTexture*>(m_pVertexArr), pCurMeshData);

#if _DEBUG
	GL::VertexPositionNormalColorTexture* pCastedVertexArr = reinterpret_cast<GL::VertexPositionNormalColorTexture*>(m_pVertexArr);
#endif


	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)sizeof(GL::VertexPositionNormalColorTexture) * pCurMeshData->uiNumVertices, m_pVertexArr, GL_STATIC_DRAW); // 메모리 할당과 저장

	// VAO
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, m_iVertexStride, (void*)0); // POSITION
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, m_iVertexStride, (void*)(0 + sizeof(vec3))); // NORMAL
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, m_iVertexStride, (void*)(0 + sizeof(vec3) + sizeof(vec3))); // COLOR
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, m_iVertexStride, (void*)(0 + sizeof(vec3) + sizeof(vec3) + sizeof(vec4))); // UV
	glEnableVertexAttribArray(3);


	// EBO
	m_iNumIndices = pCurMeshData->uiNumIndices;
	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * pCurMeshData->uiNumIndices, pCurMeshData->indexArr, GL_STATIC_DRAW);

	// Release Desc Data
	CHECK_GL_ERROR;
}

void CBasicMesh::End_CreateMesh(void* pData)
{
	DELETE_ARRAY(m_pVertexArr);

	// Unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
