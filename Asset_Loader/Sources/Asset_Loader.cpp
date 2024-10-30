#include "pch.h"
#include "Asset_Loader.h"

#include <algorithm>

#include "Engine_Core/Includes/Asset_ply.h"
#include "Engine_Core/Includes/Engine_Core.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

IMPL_COM_FUNC(CAsset_Loader)

//CAsset_Loader::CAsset_Loader(CEngine_Core* pEngine_Core) : m_pEngine_Core(pEngine_Core)
//{
//
//}

HRESULT CAsset_Loader::Load_Ply(const wchar_t* wszPath)
{
	HRESULT hr = S_OK;

	CAsset_ply* pPlyInstance = new CAsset_ply();
	pPlyInstance->m_wszPath = std::wstring(wszPath);

	std::vector<XMFLOAT3>& refVecPos = pPlyInstance->m_vecPos;
	std::vector<XMFLOAT4>& refVecRot = pPlyInstance->m_vecRot;
	std::vector<XMFLOAT3>& refVecScale = pPlyInstance->m_vecScale;
	std::vector<FLOAT>& refVecOpacity  = pPlyInstance->m_vecOpacity;
	std::vector<SHs<3>>& refVecShs = pPlyInstance->m_vecShs;
	std::vector<XMFLOAT3>& refVecNormal = pPlyInstance->m_vecNormal;
	XMFLOAT3& refMin = pPlyInstance->m_vMin;
	XMFLOAT3& refMax = pPlyInstance->m_vMax;


	std::ifstream infile(wszPath, std::ios_base::binary);

	if (!infile.good())
	{
		std::cerr << "Unable to find model's PLY file, attempted:\n" << wszPath << std::endl;
	}

	// "Parse" header (it has to be a specific format anyway)
	std::string buff;
	std::getline(infile, buff);
	std::getline(infile, buff);

	std::string dummy;
	std::getline(infile, buff);
	std::stringstream ss(buff);
	int count;
	ss >> dummy >> dummy >> count;

	// Output number of Gaussians contained
	std::cout << "Loading " << count << " Gaussian splats" << std::endl;

	while (std::getline(infile, buff))
	{
		if (buff.compare("end_header") == 0)
			break;
	}

	// Read all Gaussians at once (AoS)
	struct RichPoint
	{
		Vector3 pos;
		float n[3];
		SHs<3> shs;
		float opacity;
		Vector3 scale;
		XMFLOAT4 rot;
	};
	std::vector<RichPoint> points(count);
	infile.read((char*)points.data(), count * sizeof(RichPoint));

	// Resize our SoA data
	refVecPos.resize(count);
	refVecNormal.resize(count);
	refVecShs.resize(count);
	refVecOpacity.resize(count);
	refVecScale.resize(count);
	refVecRot.resize(count);

	// Gaussians are done training, they won't move anymore. Arrange
	// them according to 3D Morton order. This means better cache
	// behavior for reading Gaussians that end up in the same tile 
	// (close in 3D --> close in 2D).
	refMax = Vector3(FLT_MAX, FLT_MAX, FLT_MAX);
	refMin = refMin * -1;

	for (int i = 0; i < count; i++)
	{
		refMax = XMMax(Vector3(refMax), points[i].pos);
		refMin = XMMin(Vector3(refMin), points[i].pos);
	}


	std::vector<std::pair<uint64_t, int>> mapp(count);
	for (int i = 0; i < count; i++)
	{
		Vector3 rel = (points[i].pos - refMin) / (refMax - refMin);
		Vector3 scaled = ((float((1 << 21) - 1)) * rel); // 2.14345.. -> 214345...

		int iXYZ[3]{ (int)scaled.x, (int)scaled.y, (int)scaled.z };

		uint64_t motornCode = 0;

		// Bit Interleaving
		for (int i = 0; i < 21; i++) {
			motornCode |= ((uint64_t(iXYZ[0] & (1 << i))) << (2 * i + 0));
			motornCode |= ((uint64_t(iXYZ[1] & (1 << i))) << (2 * i + 1));
			motornCode |= ((uint64_t(iXYZ[2] & (1 << i))) << (2 * i + 2));
		}

		mapp[i].first = motornCode;
		mapp[i].second = i;
	}
	auto sorter = [](const std::pair < uint64_t, int>& a, const std::pair < uint64_t, int>& b) {
		return a.first < b.first;
		};
	std::sort(mapp.begin(), mapp.end(), sorter);

	// Move data from AoS to SoA
	int SH_N = (3 + 1) * (3 + 1);
	for (int k = 0; k < count; k++)
	{
		int i = mapp[k].second;
		refVecPos[k] = points[i].pos;
		// Normalize quaternion
		float length2 = 0;


		length2 += points[i].rot.x * points[i].rot.x;			
		length2 += points[i].rot.y * points[i].rot.y;
		length2 += points[i].rot.z * points[i].rot.z;
		length2 += points[i].rot.w * points[i].rot.w;

		float length = sqrt(length2);
		refVecRot[k].x = points[i].rot.x / length;
		refVecRot[k].y = points[i].rot.y / length;
		refVecRot[k].z = points[i].rot.z / length;
		refVecRot[k].w = points[i].rot.w / length;



		// Exponentiate vecScale
		refVecScale[k].x = exp(points[i].scale.x);
		refVecScale[k].y = exp(points[i].scale.y);
		refVecScale[k].z = exp(points[i].scale.z);


		// Activate alpha
		auto sigmoid = [](float m1)
		{
			return 1.0f / (1.0f + std::exp(-m1));
		};

		refVecOpacity[k] = sigmoid(points[i].opacity);

		refVecShs[k].shs[0] = points[i].shs.shs[0];
		refVecShs[k].shs[1] = points[i].shs.shs[1];
		refVecShs[k].shs[2] = points[i].shs.shs[2];
		for (int j = 1; j < SH_N; j++)
		{
			refVecShs[k].shs[j * 3 + 0] = points[i].shs.shs[(j - 1) + 3];
			refVecShs[k].shs[j * 3 + 1] = points[i].shs.shs[(j - 1) + SH_N + 2];
			refVecShs[k].shs[j * 3 + 2] = points[i].shs.shs[(j - 1) + 2 * SH_N + 1];
		}

		Vector3 vTempNormal = Vector3(points[i].n[0], points[i].n[1], points[i].n[2]);
		vTempNormal.Normalize();
		refVecNormal[k] = vTempNormal;
		
	}






	//m_pEngine_Core->Add_Ply(wszPath, pPlyInstance);

	return hr;
}
