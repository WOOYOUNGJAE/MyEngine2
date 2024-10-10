#pragma once
#include "MeshObject.h"

/**
 * @brief Basic Mesh with Vertex(Position, Normal, Color, Texcoord), Index(uint16)
 */
class CBasicMesh : public CMeshObject
{
public:
	CBasicMesh();
	~CBasicMesh() override = default;
public:
	void Begin_CreateMesh(void* pData) override;
	void End_CreateMesh(void* pData) override;

private:
	//GL::VertexPositionNormalColorTexture m_
	/*POSITIONS m_vecPositions;
	NORMALS m_vecNormals;
	COLORS m_vecColors;
	TEXCOORDS m_vecTexcoords;*/

};
