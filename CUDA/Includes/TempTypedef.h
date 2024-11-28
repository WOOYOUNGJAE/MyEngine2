#pragma once
#include "OptixException.h"

template <typename PIXEL_FORMAT>
interface IOutputBuffer
{
	IOutputBuffer() = delete;
	IOutputBuffer(UINT uiWidth, UINT uiHeight) : m_uiWidth(uiWidth), m_uiHeight(uiHeight), m_device_pixels(nullptr)
	{
		m_host_pixels.resize(uiWidth * uiHeight);
	}
	~IOutputBuffer() = default;

	PIXEL_FORMAT* Map() { return m_device_pixels; }

	UINT m_uiWidth = 0u;
	UINT m_uiHeight = 0u;

	std::vector<PIXEL_FORMAT>  m_host_pixels;
	PIXEL_FORMAT* m_device_pixels;
};


enum RayType
{
    RAY_TYPE_RADIANCE = 0,
    RAY_TYPE_COUNT
};

struct Params
{
    uchar4* image;
    unsigned int           image_width;
    unsigned int           image_height;
    float3                 cam_pos;
    float3                 cam_u, cam_v, cam_w;
    OptixTraversableHandle handle;
};


struct RayGenData
{
    // No data needed
};


struct MissData
{
    float3 bg_color;
};


struct HitGroupData
{
    // No data needed
};
