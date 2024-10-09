#pragma once

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