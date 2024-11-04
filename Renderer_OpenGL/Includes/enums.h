#pragma once

namespace Renderer_OpenGL
{
	enum GL_SHADER_PROGRAM_TYPE
	{
		SIMPLE,
		/**
		 * 	A simple copy renderer class. Much like the original, but this one
		 *	reads from a buffer instead of a texture and blits the result to
		 *	a render target. 
		 */
		IMAGE_COPY,
		VS_FS_AND_MORE_NO_USE_YET,
		NUM
	};
}