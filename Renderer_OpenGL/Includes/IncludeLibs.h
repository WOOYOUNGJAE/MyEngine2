#ifndef RENDEREROPENGLINCLUDELIBS_H
#define RENDEREROPENGLINCLUDELIBS_H

#pragma comment(lib, "../Libs/GLFW/glfw3.lib")

#ifdef _WIN64 // x64
#ifdef _DEBUG
#pragma comment(lib, "../Libs/Common/bin/Common_x64_Debug.lib")
#else
#pragma comment(lib, "../Libs/Common/bin/Common_x64_Release.lib")
#endif
#else // (x86)
#ifdef _DEBUG
#pragma comment(lib, "../Libs/Common/bin/Common_x86_Debug.lib")
#else
#pragma comment(lib, "../Libs/Common/bin/Common_x86_Release.lib")
#endif
#endif


#include "Common/Includes/pch.h"



#include "../../Libs/glad/glad.h"
#include "../../Libs/GLFW/glfw3.h"
#include "../../Libs/glm/glm.hpp"
#include "../../Libs/glm/gtc/matrix_transform.hpp"
#include "../../Libs/glm/gtc/type_ptr.hpp"



#endif