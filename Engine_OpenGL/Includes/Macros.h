#pragma once

// OpenGL Macro
#define DELETE_GL_BUFFER_OBJECT(GLUINT_BO) \
	if ((GLUINT_BO))			\
	{\
		glDeleteBuffers(1, &(GLUINT_BO));\
		(GLUINT_BO) = 0;\
	}

#define DELETE_GL_VERTEX_ARRAY(GLUINT_VAO) \
	if ((GLUINT_VAO))			\
	{\
		glDeleteVertexArrays(1, &(GLUINT_VAO));\
		(GLUINT_VAO) = 0;\
	}


/** Macro to check OpenGL error and throw \p std::runtime_error if found */
# undef CHECK_GL_ERROR
# define CHECK_GL_ERROR  {								\
  GLenum err = glGetError();							\
  if (err) {											\
	std::string errorStr = "Unknown";					\
	switch (err) {										\
	case GL_INVALID_ENUM:								\
		errorStr = "GL_INVALID_ENUM";					\
		break;											\
	case GL_INVALID_VALUE:								\
		errorStr = "GL_INVALID_VALUE";					\
		break;											\
	case GL_INVALID_OPERATION:							\
		errorStr = "GL_INVALID_OPERATION";				\
		break;											\
	case GL_OUT_OF_MEMORY:								\
		errorStr = "GL_OUT_OF_MEMORY";					\
		break;											\
	case GL_INVALID_FRAMEBUFFER_OPERATION:				\
		errorStr = "GL_INVALID_FRAMEBUFFER_OPERATION";	\
		break;											\
	default:											\
		break;											\
	}													\
  ERROR_CONSOLE << "OpenGL error 0x0" << std::hex << err  << std::dec  << " (" << int(err) << ") " << errorStr << " at " << __FILE__ << ":" << __LINE__ << std::endl; \
  }														\
}
