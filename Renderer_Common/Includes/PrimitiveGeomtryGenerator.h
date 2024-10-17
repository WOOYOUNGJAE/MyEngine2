#pragma once
#include "Structs.h"

// DX Standard. Should be converted if OpenGL

inline void Fill_BasicMesh_Cube(Renderer_Common::MESH_DESC_BASIC& refMeshDesc)
{
	using namespace Renderer_Common;

	UINT uiNumVertices = 24;
	refMeshDesc.uiNumVertices = uiNumVertices;

	// Allocate
	refMeshDesc.fPositionArr = new FLOAT[3 * uiNumVertices]
	{
		// front
		-0.5f, -0.5f, -0.5f,
		-0.5f, +0.5f, -0.5f,
		+0.5f, +0.5f, -0.5f,
		+0.5f, -0.5f, -0.5f,
		// back
		-0.5f, -0.5f, +0.5f,
		-0.5f, +0.5f, +0.5f,
		+0.5f, +0.5f, +0.5f,
		+0.5f, -0.5f, +0.5f,
		// top
		-0.5f, +0.5f, -0.5f,
		-0.5f, +0.5f, +0.5f,
		+0.5f, +0.5f, +0.5f,
		+0.5f, +0.5f, -0.5f,
		// bottom
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, +0.5f,
		+0.5f, -0.5f, +0.5f,
		+0.5f, -0.5f, -0.5f,
		// left
		-0.5f, -0.5f, +0.5f,
		-0.5f, +0.5f, +0.5f,
		-0.5f, +0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		// right
		+0.5f, -0.5f, -0.5f,
		+0.5f, +0.5f, -0.5f,
		+0.5f, +0.5f, +0.5f,
		+0.5f, -0.5f, +0.5f

	};

	refMeshDesc.fNormalArr = new FLOAT[3 * uiNumVertices]
	{
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,

		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,

		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,

		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f
	};

	refMeshDesc.fColorArr = new FLOAT[4 * uiNumVertices]
	{
		Colors::Yellow.x, Colors::Yellow.y, Colors::Yellow.z, Colors::Yellow.w,
		Colors::White.x, Colors::White.y, Colors::White.z, Colors::White.w,
		Colors::Cyan.x, Colors::Cyan.y, Colors::Cyan.z, Colors::Cyan.w,
		Colors::Green.x, Colors::Green.y, Colors::Green.z, Colors::Green.w,

		Colors::Red.x, Colors::Red.y, Colors::Red.z, Colors::Red.w,
		Colors::Magenta.x, Colors::Magenta.y, Colors::Magenta.z, Colors::Magenta.w,
		Colors::Blue.x, Colors::Blue.y, Colors::Blue.z, Colors::Blue.w,
		Colors::Black.x, Colors::Black.y, Colors::Black.z, Colors::Black.w,

		Colors::White.x, Colors::White.y, Colors::White.z, Colors::White.w,
		Colors::Magenta.x, Colors::Magenta.y, Colors::Magenta.z, Colors::Magenta.w,
		Colors::Blue.x, Colors::Blue.y, Colors::Blue.z, Colors::Blue.w,
		Colors::Cyan.x, Colors::Cyan.y, Colors::Cyan.z, Colors::Cyan.w,

		Colors::Yellow.x, Colors::Yellow.y, Colors::Yellow.z, Colors::Yellow.w,
		Colors::Red.x, Colors::Red.y, Colors::Red.z, Colors::Red.w,
		Colors::Black.x, Colors::Black.y, Colors::Black.z, Colors::Black.w,
		Colors::Green.x, Colors::Green.y, Colors::Green.z, Colors::Green.w,

		Colors::Red.x, Colors::Red.y, Colors::Red.z, Colors::Red.w,
		Colors::Magenta.x, Colors::Magenta.y, Colors::Magenta.z, Colors::Magenta.w,
		Colors::White.x, Colors::White.y, Colors::White.z, Colors::White.w,
		Colors::Yellow.x, Colors::Yellow.y, Colors::Yellow.z, Colors::Yellow.w,

		Colors::Green.x, Colors::Green.y, Colors::Green.z, Colors::Green.w,
		Colors::Cyan.x, Colors::Cyan.y, Colors::Cyan.z, Colors::Cyan.w,
		Colors::Blue.x, Colors::Blue.y, Colors::Blue.z, Colors::Blue.w,
		Colors::Black.x, Colors::Black.y, Colors::Black.z, Colors::Black.w,
	};

	refMeshDesc.fTexCoordArr = new FLOAT[2 * uiNumVertices]
	{
		0.0f, 1.0f,  // front
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,

		1.0f, 1.0f,  // back
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,

		0.0f, 1.0f,  // top
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,

		1.0f, 1.0f,  // bottom
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,

		0.0f, 1.0f,  // left
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,

		0.0f, 1.0f,  // right
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
	};


	UINT uiNumIndices = 36;
	refMeshDesc.uiNumIndices = uiNumIndices;
	refMeshDesc.indexArr = new UINT32[uiNumIndices]
	{
		// front
		0, 1, 2,
		0, 2, 3,

		// back
		7, 6, 5,
		7, 5, 4,

		// top
		8, 9, 10,
		8, 10, 11,

		// bottom
		13, 12, 15,
		13, 15, 14,

		// left
		16, 17, 18,
		16, 18, 19,

		// right
		20, 21, 22,
		20, 22, 23,
	};
}

inline void Fill_BasicMesh_Quad(Renderer_Common::MESH_DESC_BASIC& refMeshDesc)
{
	// TODO: GL Convention
	using namespace Renderer_Common;

	UINT uiNumVertices = 4;
	refMeshDesc.uiNumVertices = uiNumVertices;

	// Allocate
	refMeshDesc.fPositionArr = new FLOAT[3 * uiNumVertices]
	{
		0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	refMeshDesc.fNormalArr = new FLOAT[3 * uiNumVertices]
	{
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
	};

	refMeshDesc.fColorArr = new FLOAT[4 * uiNumVertices]
	{
		Colors::Yellow.x, Colors::Yellow.y, Colors::Yellow.z, Colors::Yellow.w,
		Colors::White.x, Colors::White.y, Colors::White.z, Colors::White.w,
		Colors::Cyan.x, Colors::Cyan.y, Colors::Cyan.z, Colors::Cyan.w,
		Colors::Green.x, Colors::Green.y, Colors::Green.z, Colors::Green.w,
	};

	refMeshDesc.fTexCoordArr = new FLOAT[2 * uiNumVertices]
	{
		1.f, 1.f,
		1.f, 0.f,
		0.f, 0.f,
		0.f, 1.f,
	};


	UINT uiNumIndices = 6;
	refMeshDesc.uiNumIndices = uiNumIndices;
	refMeshDesc.indexArr = new UINT32[uiNumIndices]
	{
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};
}

#pragma region Static Mesh Info
struct STATIC_CUBE_BASIC_VERTEX
{
	UINT32 uiNumVertices = 24;
	UINT32 uiNumIndices = 36;
	DirectX::VertexPositionNormalColorTexture basicVertexArr[24]
	{
		// front
		VertexPositionNormalColorTexture(XMFLOAT3(-1, -1, -1), XMFLOAT3(0.0f, 0.0f, -1.0f), (XMFLOAT4)Colors::Yellow, XMFLOAT2(0.0f, 1.0f)),
		VertexPositionNormalColorTexture(XMFLOAT3(-1, +1, -1), XMFLOAT3(0.0f, 0.0f, -1.0f), Colors::White, XMFLOAT2(0.0f, 0.0f)),
		VertexPositionNormalColorTexture(XMFLOAT3(+1, +1, -1), XMFLOAT3(0.0f, 0.0f, -1.0f), Colors::Cyan, XMFLOAT2(1.0f, 0.0f)),
		VertexPositionNormalColorTexture(XMFLOAT3(+1, -1, -1), XMFLOAT3(0.0f, 0.0f, -1.0f), Colors::Green, XMFLOAT2(1.0f, 1.0f)),

		// back
		VertexPositionNormalColorTexture(XMFLOAT3(-1, -1, +1), XMFLOAT3(0.0f, 0.0f, 1.0f),Colors::Red,XMFLOAT2(1.0f, 1.0f)),
		VertexPositionNormalColorTexture(XMFLOAT3(-1, +1, +1), XMFLOAT3(0.0f, 0.0f, 1.0f),Colors::Magenta, XMFLOAT2(1.0f, 0.0f)),
		VertexPositionNormalColorTexture(XMFLOAT3(+1, +1, +1), XMFLOAT3(0.0f, 0.0f, 1.0f),Colors::Blue, XMFLOAT2(0.0f, 0.0f)),
		VertexPositionNormalColorTexture(XMFLOAT3(+1, -1, +1), XMFLOAT3(0.0f, 0.0f, 1.0f),Colors::Black, XMFLOAT2(0.0f, 1.0f)),

		// top
		VertexPositionNormalColorTexture(XMFLOAT3(-1, +1, -1), XMFLOAT3(0.0f, 1.0f, 0.0f),Colors::White,XMFLOAT2(0.0f, 1.0f)),
		VertexPositionNormalColorTexture(XMFLOAT3(-1, +1, +1), XMFLOAT3(0.0f, 1.0f, 0.0f),Colors::Magenta, XMFLOAT2(0.0f, 0.0f)),
		VertexPositionNormalColorTexture(XMFLOAT3(+1, +1, +1), XMFLOAT3(0.0f, 1.0f, 0.0f),Colors::Blue, XMFLOAT2(1.0f, 0.0f)),
		VertexPositionNormalColorTexture(XMFLOAT3(+1, +1, -1), XMFLOAT3(0.0f, 1.0f, 0.0f),Colors::Cyan, XMFLOAT2(1.0f, 1.0f)),

		// bottom
		VertexPositionNormalColorTexture(XMFLOAT3(-1, -1, -1), XMFLOAT3(0.0f, -1.0f, 0.0f),Colors::Yellow,XMFLOAT2(1.0f, 1.0f)),
		VertexPositionNormalColorTexture(XMFLOAT3(-1, -1, +1), XMFLOAT3(0.0f, -1.0f, 0.0f),Colors::Red, XMFLOAT2(1.0f, 0.0f)),
		VertexPositionNormalColorTexture(XMFLOAT3(+1, -1, +1), XMFLOAT3(0.0f, -1.0f, 0.0f),Colors::Black, XMFLOAT2(0.0f, 0.0f)),
		VertexPositionNormalColorTexture(XMFLOAT3(+1, -1, -1), XMFLOAT3(0.0f, -1.0f, 0.0f),Colors::Green, XMFLOAT2(0.0f, 1.0f)),

		// left
		VertexPositionNormalColorTexture(XMFLOAT3(-1, -1, +1), XMFLOAT3(-1.0f, 0.0f, 0.0f),Colors::Red,XMFLOAT2(0.0f, 1.0f)),  // 
		VertexPositionNormalColorTexture(XMFLOAT3(-1, +1, +1), XMFLOAT3(-1.0f, 0.0f, 0.0f),Colors::Magenta, XMFLOAT2(0.0f, 0.0f)),
		VertexPositionNormalColorTexture(XMFLOAT3(-1, +1, -1), XMFLOAT3(-1.0f, 0.0f, 0.0f),Colors::White, XMFLOAT2(1.0f, 0.0f)),
		VertexPositionNormalColorTexture(XMFLOAT3(-1, -1, -1), XMFLOAT3(-1.0f, 0.0f, 0.0f),Colors::Yellow, XMFLOAT2(1.0f, 1.0f)),

		// right
		VertexPositionNormalColorTexture(XMFLOAT3(1, -1, -1), XMFLOAT3(1.0f, 0.0f, 0.0f), Colors::Green,XMFLOAT2(0.0f, 1.0f)),
		VertexPositionNormalColorTexture(XMFLOAT3(1, +1, -1), XMFLOAT3(1.0f, 0.0f, 0.0f), Colors::Cyan, XMFLOAT2(0.0f, 0.0f)),
		VertexPositionNormalColorTexture(XMFLOAT3(1, +1, +1), XMFLOAT3(1.0f, 0.0f, 0.0f), Colors::Blue, XMFLOAT2(1.0f, 0.0f)),
		VertexPositionNormalColorTexture(XMFLOAT3(1, -1, +1), XMFLOAT3(1.0f, 0.0f, 0.0f), Colors::Black, XMFLOAT2(1.0f, 1.0f)),

	};
	UINT32 indexArr[36]
	{
		// front
		0, 1, 2,
		0, 2, 3,

		// back
		7, 6, 5,
		7, 5, 4,

		// top
		8, 9, 10,
		8, 10, 11,

		// bottom
		13, 12, 15,
		13, 15, 14,

		// left
		16, 17, 18,
		16, 18, 19,

		// right
		20, 21, 22,
		20, 22, 23,
	};
};
#pragma endregion
