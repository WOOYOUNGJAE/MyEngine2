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
	MESH_DESC_BASIC* pMeshDataArr = *(pCastedData->pBasicMeshDataArrPtr);
	MESH_DESC_BASIC& refCurMeshData = pMeshDataArr[0];
	//refCurMeshData = pMeshDataArr[1];

	m_pVertexArr = new GL::VertexPositionNormalColorTexture[refCurMeshData.uiNumVertices];
	::Copy_MeshDesc_Basic(reinterpret_cast<GL::VertexPositionNormalColorTexture*>(m_pVertexArr), &refCurMeshData);

	// Gen VAO VBO EBO
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	// VAO
	glBindVertexArray(m_VAO);

	// VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)sizeof(GL::VertexPositionNormalColorTexture) * refCurMeshData.uiNumVertices, m_pVertexArr, GL_STATIC_DRAW); // 메모리 할당과 저장
	CHECK_GL_ERROR;


	// EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)sizeof(uint) * refCurMeshData.uiNumIndices, refCurMeshData.indexArr, GL_STATIC_DRAW);

	// Vertex Attrib
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, m_iVertexStride, (void*)0); // POSITION
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, m_iVertexStride, (void*)(0 + sizeof(vec3))); // NORMAL
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, m_iVertexStride, (void*)(0 + sizeof(vec3) + sizeof(vec3))); // COLOR
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, m_iVertexStride, (void*)(0 + sizeof(vec3) + sizeof(vec3) + sizeof(vec4))); // UV
	glEnableVertexAttribArray(3);



	glBindVertexArray(0);
	m_eShaderType = Renderer_OpenGL::GL_SHADER_PROGRAM_TYPE::SIMPLE;
	m_iNumIndices = refCurMeshData.uiNumIndices;
}

void CBasicMesh::End_CreateMesh(void* pData)
{
	DELETE_ARRAY(m_pVertexArr);

	// Unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
