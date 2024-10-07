#pragma once

inline DirectX::VertexPositionNormalColorTexture* Cube_Vertices()
{
	using namespace DirectX;

	VertexPositionNormalColorTexture* vertexArr = new VertexPositionNormalColorTexture[24]
	{
		// front
		VertexPositionNormalColorTexture(Vector3(-1, -1, -1), Vector3(0.0f, 0.0f, -1.0f), Colors::Yellow, Vector2(0.0f, 1.0f)),
		VertexPositionNormalColorTexture(Vector3(-1, +1, -1), Vector3(0.0f, 0.0f, -1.0f), Colors::White, Vector2(0.0f, 0.0f)),
		VertexPositionNormalColorTexture(Vector3(+1, +1, -1), Vector3(0.0f, 0.0f, -1.0f), Colors::Cyan, Vector2(1.0f, 0.0f)),
		VertexPositionNormalColorTexture(Vector3(+1, -1, -1), Vector3(0.0f, 0.0f, -1.0f), Colors::Green, Vector2(1.0f, 1.0f)),

		// back
		VertexPositionNormalColorTexture(Vector3(-1, -1, +1), Vector3(0.0f, 0.0f, 1.0f),Colors::Red,Vector2(1.0f, 1.0f)),
		VertexPositionNormalColorTexture(Vector3(-1, +1, +1), Vector3(0.0f, 0.0f, 1.0f),Colors::Magenta, Vector2(1.0f, 0.0f)),
		VertexPositionNormalColorTexture(Vector3(+1, +1, +1), Vector3(0.0f, 0.0f, 1.0f),Colors::Blue, Vector2(0.0f, 0.0f)),
		VertexPositionNormalColorTexture(Vector3(+1, -1, +1), Vector3(0.0f, 0.0f, 1.0f),Colors::Black, Vector2(0.0f, 1.0f)),

		// top
		VertexPositionNormalColorTexture(Vector3(-1, +1, -1), Vector3(0.0f, 1.0f, 0.0f),Colors::White,Vector2(0.0f, 1.0f)),
		VertexPositionNormalColorTexture(Vector3(-1, +1, +1), Vector3(0.0f, 1.0f, 0.0f),Colors::Magenta, Vector2(0.0f, 0.0f)),
		VertexPositionNormalColorTexture(Vector3(+1, +1, +1), Vector3(0.0f, 1.0f, 0.0f),Colors::Blue, Vector2(1.0f, 0.0f)),
		VertexPositionNormalColorTexture(Vector3(+1, +1, -1), Vector3(0.0f, 1.0f, 0.0f),Colors::Cyan, Vector2(1.0f, 1.0f)),

		// bottom
		VertexPositionNormalColorTexture(Vector3(-1, -1, -1), Vector3(0.0f, -1.0f, 0.0f),Colors::Yellow,Vector2(1.0f, 1.0f)),
		VertexPositionNormalColorTexture(Vector3(-1, -1, +1), Vector3(0.0f, -1.0f, 0.0f),Colors::Red, Vector2(1.0f, 0.0f)),
		VertexPositionNormalColorTexture(Vector3(+1, -1, +1), Vector3(0.0f, -1.0f, 0.0f),Colors::Black, Vector2(0.0f, 0.0f)),
		VertexPositionNormalColorTexture(Vector3(+1, -1, -1), Vector3(0.0f, -1.0f, 0.0f),Colors::Green, Vector2(0.0f, 1.0f)),

		// left
		VertexPositionNormalColorTexture(Vector3(-1, -1, +1), Vector3(-1.0f, 0.0f, 0.0f),Colors::Red,Vector2(0.0f, 1.0f)),  // 
		VertexPositionNormalColorTexture(Vector3(-1, +1, +1), Vector3(-1.0f, 0.0f, 0.0f),Colors::Magenta, Vector2(0.0f, 0.0f)),
		VertexPositionNormalColorTexture(Vector3(-1, +1, -1), Vector3(-1.0f, 0.0f, 0.0f),Colors::White, Vector2(1.0f, 0.0f)),
		VertexPositionNormalColorTexture(Vector3(-1, -1, -1), Vector3(-1.0f, 0.0f, 0.0f),Colors::Yellow, Vector2(1.0f, 1.0f)),

		// right
		VertexPositionNormalColorTexture(Vector3(1, -1, -1), Vector3(1.0f, 0.0f, 0.0f), Colors::Green,Vector2(0.0f, 1.0f)),
		VertexPositionNormalColorTexture(Vector3(1, +1, -1), Vector3(1.0f, 0.0f, 0.0f), Colors::Cyan, Vector2(0.0f, 0.0f)),
		VertexPositionNormalColorTexture(Vector3(1, +1, +1), Vector3(1.0f, 0.0f, 0.0f), Colors::Blue, Vector2(1.0f, 0.0f)),
		VertexPositionNormalColorTexture(Vector3(1, -1, +1), Vector3(1.0f, 0.0f, 0.0f), Colors::Black, Vector2(1.0f, 1.0f)),
	};
	return vertexArr;
}