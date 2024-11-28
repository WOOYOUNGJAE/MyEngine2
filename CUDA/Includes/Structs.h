#pragma once
//#include ""
namespace GS
{
	/**
	 * Data for Gaussians
	 */
	struct GAUSSIANS_CUDA_DATA
	{
		GAUSSIANS_CUDA_DATA() = default;
		~GAUSSIANS_CUDA_DATA()
		{
			cudaFree(posXYZArr);
			cudaFree(rotXYZWArr);
			cudaFree(scaleXYZArr);
			cudaFree(opacityArr);
			cudaFree(shsArr);
			cudaFree(normalXYZArr);
			cudaFree(rect);
			cudaFree(bg_colorXYZ);
		}
		int iNumPoints;
		float* posXYZArr;
		float* rotXYZWArr;
		float* scaleXYZArr;
		float* opacityArr;
		float* shsArr;
		float* normalXYZArr;
		int* rect;
		float* bg_colorXYZ;
	};

	/**
	 * Data for Uniform Buffer
	 */
	struct UNIFORM_CUDA_DATA
	{
		UNIFORM_CUDA_DATA() = default;
		~UNIFORM_CUDA_DATA()
		{
			cudaFree(viewMat4X4);
			cudaFree(projMat4X4);
			cudaFree(camPosXYZ);
		}
		float* viewMat4X4;
		float* projMat4X4;
		float* camPosXYZ;
	};

	/**
	 * Data for OpenGL Buffer, 
	 */
	struct CUDA_GRAPHICS_RESOURCE_OpenGL
	{
		CUDA_GRAPHICS_RESOURCE_OpenGL() = default;
		~CUDA_GRAPHICS_RESOURCE_OpenGL()
		{
			cudaGraphicsUnregisterResource(imageBuffer);
		}
		cudaGraphicsResource_t imageBuffer;
	};
}
