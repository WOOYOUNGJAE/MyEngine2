#include "pch.h"
#include "Renderer.h"

#include <execution>

#include "BasicMesh.h"
#include "ShaderManager.h"
#include "BufferManager.h"
#include "enums.h"
#include "Util_Funcs.h"
#include "ShaderObject.h"

IMPL_COM_FUNC(CRenderer)

CViewer* g_pViewer;
void On_Resize_Window(GLFWwindow* pWindow, INT winX, INT winY);

void On_Resize_Window(GLFWwindow* pWindow, INT winX, INT winY)
{
    glViewport(0, 0, winX, winY);
}

CRenderer::CRenderer(IRenderer::OpenGL identifier, UINT uiWinX, UINT uiWinY, const char* szTitle, GLFWwindow ** ppOutGLWin)
{
    m_eGraphics = Graphics_API::OpenGL;
    // Init GL
    if (!glfwInit())
    {
        ERROR_BOX("Init GLFW Failed");
        return;
    }

	// Create a GLFW window with OpenGL context
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // Request OpenGL 3.3
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);  // Request OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE); // Double Buffering

    // Create Window, Context
    m_pWindow = glfwCreateWindow((int)uiWinX, (int)uiWinY, szTitle, nullptr, nullptr);
    glfwMakeContextCurrent(m_pWindow); // Bind Context

    // Init GLAD
    if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == false)
    {
        ERROR_BOX("Init GLAD Failed");
        return;
    }

    // Create Viewer
    m_uiWinX = uiWinX;
    m_uiWinY = uiWinY;

    // Register Callback win Resizing Func
    glfwSetFramebufferSizeCallback(m_pWindow, On_Resize_Window);

    // Create Manager
    m_pShaderManager = new CShaderManager();
    m_pBufferManager = new CBufferManager();

    *ppOutGLWin = m_pWindow;
}

CRenderer::~CRenderer()
{
    RELEASE_INSTANCE(m_pBufferManager);
    RELEASE_INSTANCE(m_pShaderManager);
}

void CRenderer::Initialize(void* pArg)
{
    if (*(bool*)pArg == true)
    {
        m_pBufferManager->Generate_Buffer_CudaImage(m_uiWinX, m_uiWinY);
    }

    // Default Shaders
    m_pShaderManager->Load_Shader(Renderer_OpenGL::GL_SHADER_PROGRAM_TYPE::SIMPLE, "Simple");
    m_pShaderManager->Load_Shader(Renderer_OpenGL::GL_SHADER_PROGRAM_TYPE::IMAGE_COPY, "Image_Copy");
}

int32 CRenderer::MainRender(FLOAT fDeltaTime)
{

    //if (glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    if (m_KeyManager.Key_Down(VK_ESCAPE))
    {
        glfwSetWindowShouldClose(m_pWindow, TRUE);
        glfwTerminate();
        return FALSE;
    }
    for (UINT eShaderType = 0; eShaderType < Renderer_OpenGL::GL_SHADER_PROGRAM_TYPE::NUM; ++eShaderType)
    {
        CShaderObject* pShaderObject = m_pShaderManager->m_mapShaderObjects[eShaderType];
        GLuint curShaderProgram = pShaderObject->Shader();
        glUseProgram(curShaderProgram); // Bind Shader Program

        // Culling
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CW);
        glCullFace(GL_BACK);

        // Depth Testing
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);


        if (eShaderType == Renderer_OpenGL::GL_SHADER_PROGRAM_TYPE::SIMPLE)
        {
            GLuint uniformViewProj = glGetUniformLocation(curShaderProgram, "g_ViewProj");
            glUniformMatrix4fv(uniformViewProj, 1, GL_FALSE/*row to col*/, glm::value_ptr(m_matViewProj));
        }

        for (auto& iterMeshObj : m_RenderQueueArr[eShaderType])
        {
            glBindVertexArray(iterMeshObj->VAO()); // Bind VAO
            glDrawElements(GL_TRIANGLES, (GLsizei)iterMeshObj->NumIndices(), GL_UNSIGNED_INT, nullptr);
            glBindVertexArray(0); // Unbind VAO

            
            GLuint uniformModel = glGetUniformLocation(curShaderProgram, "g_Model");
            glm::mat4x4 curModelMatrix{};
            curModelMatrix = ::Get_Converted_Matrix_DXtoGL(iterMeshObj->WorldMat());
            memcpy_s(&curModelMatrix, sizeof(mat4x4), &curModelMatrix, sizeof(XMFLOAT4X4));

            glUniformMatrix4fv(uniformModel, 1, GL_FALSE/*row to col*/, glm::value_ptr(curModelMatrix));
            CHECK_GL_ERROR


        }
        m_RenderQueueArr[eShaderType].clear();
    }


    return !glfwWindowShouldClose(m_pWindow);
}

void CRenderer::Update_CameraInfo(XMFLOAT4X4& matCameraWorld, CAMERA_DESC& cameraDesc)
{
    //::Convert_Matrix_DXtoGL(matCameraWorld);

    //m_matCameraWorld = *reinterpret_cast<mat4x4*>(&matCameraWorld);
    m_matCameraWorld = ::Get_Converted_Matrix_DXtoGL(matCameraWorld);

    glm::vec3 camPos = m_matCameraWorld[3];
    glm::vec3 camFront = glm::normalize(m_matCameraWorld[2]);
    glm::vec3 camUp = glm::normalize(m_matCameraWorld[1]);

    //m_matCameraWorld[2].z *= -1; // Look Z Direction Should not be Converted
    m_matView = glm::inverse(m_matCameraWorld);
    m_matView = glm::lookAt(camPos, camPos + camFront, camUp);

    m_matProj = glm::perspective(cameraDesc.fFovY, cameraDesc.fAspectRatio, cameraDesc.fNear, cameraDesc.fFar);
    m_matViewProj = m_matProj * m_matView;
}

void CRenderer::BeginRender()
{
    glfwPollEvents();

    // Reset Depth
    glClearDepth(1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Update Key Inputs
    m_KeyManager.Update_InputStates(m_pWindow);


    glViewport(0, 0, (UINT)m_uiWinX, (UINT)m_uiWinY);

    glClearColor(37.f / 255.f, 37.f / 255.f, 38.f / 255.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void CRenderer::Render_MeshObject_External(IMeshObject* pMeshObj, XMFLOAT4X4& matWorld)
{
    CMeshObject* pCastedMeshObj = static_cast<CMeshObject*>(pMeshObj);
    //::Convert_Matrix_DXtoGL(matWorld);
    pCastedMeshObj->Set_WorldMat(matWorld);
    m_RenderQueueArr[pCastedMeshObj->ShaderType()].push_back(pCastedMeshObj);
}

void CRenderer::MainRender()
{
}

void CRenderer::EndRender()
{
    glfwSwapBuffers(m_pWindow);
}

void* CRenderer::Get_ImageBuffer()
{
    return (void*)m_pBufferManager->Get_ImageBuffer();
}

IMeshObject* CRenderer::Create_EmptyBasicMesh(void* pData)
{
    return new CBasicMesh;
}

void CRenderer::GLFW_KeyManager::Update_InputStates(GLFWwindow* pWin)
{
    // Keyboard
    for (INT keyChecking = 0 /*After Mouse, From Keyboard*/ ; keyChecking < VK_MAX; ++keyChecking)
    {
        int glfwKey = ConvertVkToGlfwKey(keyChecking);
        int glfwState = 0;
        // If Mouse
        if (glfwKey < GLFW_MOUSE_BUTTON_LAST)
        {
            glfwState = glfwGetMouseButton(pWin, glfwKey);
        }
        else
        {
			glfwState = glfwGetKey(pWin, glfwKey);	        
        }

        if (glfwState == GLFW_PRESS || glfwState == GLFW_REPEAT) // If Pressed
        {
            if (keyStateArr[keyChecking].first) // and Also Pressed Before
            {
                keyStateArr[keyChecking].second = KEY_PRESSING; // Pressing
            }
            else
            {
                keyStateArr[keyChecking].first = true;
                keyStateArr[keyChecking].second = KEY_DOWN; // Pressed this tick
            }
        }
        else if (glfwState == GLFW_RELEASE) // Not Pressed
        {
            if (keyStateArr[keyChecking].first) // but Pressed Before
            {
                keyStateArr[keyChecking].first = false;
                keyStateArr[keyChecking].second = KEY_UP;
            }
            else
            {
                keyStateArr[keyChecking].second = KEY_NONE;
            }
        }
    }

    // prev = cur
    memcpy_s(prevMousePosXY, sizeof(double) * 2, curMousePosXY, sizeof(double) * 2);
    glfwGetCursorPos(pWin, &curMousePosXY[0], &curMousePosXY[1]);
}

bool CRenderer::GLFW_KeyManager::Key_Pressing(int inKey)
{
    return keyStateArr[inKey].second == KEY_PRESSING;
}

bool CRenderer::GLFW_KeyManager::Key_Down(int inKey)
{
    return keyStateArr[inKey].second == KEY_DOWN;
}

bool CRenderer::GLFW_KeyManager::Key_Up(int inKey)
{
    return keyStateArr[inKey].second == KEY_UP;
}

int CRenderer::GLFW_KeyManager::ConvertVkToGlfwKey(int vkKey)
{
    switch (vkKey)
    {
    case 0x01: return GLFW_MOUSE_BUTTON_LEFT;
    case 0x02: return GLFW_MOUSE_BUTTON_RIGHT;
    case 0x04: return GLFW_MOUSE_BUTTON_MIDDLE;
    case 0x08: return GLFW_KEY_BACKSPACE;
    case 0x09: return GLFW_KEY_TAB;
    case 0x0D: return GLFW_KEY_ENTER;
    case 0x10: return GLFW_KEY_LEFT_SHIFT;
    case 0x11: return GLFW_KEY_LEFT_CONTROL;
    case 0x12: return GLFW_KEY_LEFT_ALT;
    case 0x1B: return GLFW_KEY_ESCAPE;
    case 0x20: return GLFW_KEY_SPACE;
    case 0x21: return GLFW_KEY_PAGE_UP;
    case 0x22: return GLFW_KEY_PAGE_DOWN;
    case 0x23: return GLFW_KEY_END;
    case 0x24: return GLFW_KEY_HOME;
    case 0x25: return GLFW_KEY_LEFT;
    case 0x26: return GLFW_KEY_UP;
    case 0x27: return GLFW_KEY_RIGHT;
    case 0x28: return GLFW_KEY_DOWN;
    case 0x2C: return GLFW_KEY_PRINT_SCREEN;
    case 0x2D: return GLFW_KEY_INSERT;
    case 0x2E: return GLFW_KEY_DELETE;
    case 0x5B: return GLFW_KEY_LEFT_SUPER;  // Left Windows key
    case 0x5C: return GLFW_KEY_RIGHT_SUPER; // Right Windows key
    case 0x60: return GLFW_KEY_KP_0;
    case 0x61: return GLFW_KEY_KP_1;
    case 0x62: return GLFW_KEY_KP_2;
    case 0x63: return GLFW_KEY_KP_3;
    case 0x64: return GLFW_KEY_KP_4;
    case 0x65: return GLFW_KEY_KP_5;
    case 0x66: return GLFW_KEY_KP_6;
    case 0x67: return GLFW_KEY_KP_7;
    case 0x68: return GLFW_KEY_KP_8;
    case 0x69: return GLFW_KEY_KP_9;
    case 0x6A: return GLFW_KEY_KP_MULTIPLY;
    case 0x6B: return GLFW_KEY_KP_ADD;
    case 0x6D: return GLFW_KEY_KP_SUBTRACT;
    case 0x6E: return GLFW_KEY_KP_DECIMAL;
    case 0x6F: return GLFW_KEY_KP_DIVIDE;
    case 0x70: return GLFW_KEY_F1;
    case 0x71: return GLFW_KEY_F2;
    case 0x72: return GLFW_KEY_F3;
    case 0x73: return GLFW_KEY_F4;
    case 0x74: return GLFW_KEY_F5;
    case 0x75: return GLFW_KEY_F6;
    case 0x76: return GLFW_KEY_F7;
    case 0x77: return GLFW_KEY_F8;
    case 0x78: return GLFW_KEY_F9;
    case 0x79: return GLFW_KEY_F10;
    case 0x7A: return GLFW_KEY_F11;
    case 0x7B: return GLFW_KEY_F12;
    case 0x90: return GLFW_KEY_NUM_LOCK;
    case 0x91: return GLFW_KEY_SCROLL_LOCK;

        /*
        * VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
        * 0x3A - 0x40 : unassigned
        * VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
        */
    default: return vkKey; // ASCII
    }
}
