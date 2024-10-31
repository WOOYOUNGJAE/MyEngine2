#pragma once

namespace GS
{
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
}
