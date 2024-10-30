#pragma once
#include "RendererConfig.h"
#include "Common/Includes/RendererInterface.h"
#include "Viewer.h"
#include "enums.h"

struct GLFWwindow;
class CViewer;
class CShaderManager;
class CMeshObject;
/**
 * @brief Top-level class. All GL-Dependant Classes should be in this project
 */
class RENDEREROPENGL_DLL CRenderer final : public IRenderer
{
	/**
	 * Manage Keys under Windows VK Key Standard
	 */
	struct GLFW_KeyManager
	{
		enum KEY_STATE { KEY_NONE, KEY_DOWN, KEY_UP, KEY_PRESSING, KEY_STATE_NUM };
		static constexpr int VK_MAX = 0xff;

		std::pair<bool, KEY_STATE> keyStateArr[VK_MAX]{};
		double prevMousePosXY[2]{};
		double curMousePosXY[2]{};
	public:
		void Update_InputStates(GLFWwindow* pWin);
		bool Key_Pressing(int inKey);
		bool Key_Down(int inKey);
		bool Key_Up(int inKey);
	private:
		int ConvertVkToGlfwKey(int vkKey);
	};
	COM_BASE
public:
	CRenderer() = delete;
	CRenderer(IRenderer::OpenGL identifier, UINT uiWinX, UINT uiWinY, const char* szTitle, GLFWwindow ** ppOutGLWin);
	~CRenderer();
public: // Interface Overrides
	void Initialize(void*) override;
	/**
	 * @return If WindowShouldClose
	 */
	INT MainRender(FLOAT fDeltaTime) override;
	void Update_CameraInfo(XMFLOAT4X4& matCameraWorld, CAMERA_DESC& cameraDesc) override;
	void BeginRender() override;
	/**
	 * Called from External Renderer, Just Add to RenderQueue
	 */
	void Render_MeshObject_External(IMeshObject* pMeshObj, XMFLOAT4X4& matWorld) override;
	void MainRender() override;
	void EndRender() override;

	// getter
	//IRenderMachine* Get_RenderMachine() override;
	
	IMeshObject* Create_EmptyBasicMesh(void* pData) override;
	IMeshObject* Create_EmptyColoredMesh(void* pData) override;

private:
	GLFWwindow* m_pWindow = nullptr;
	CViewer* m_pViewer = nullptr;
private: //Managers
	CShaderManager* m_pShaderManager = nullptr;
private:
	/**
	 * @brief RenderQueue List Distributed by Shader Type
	 */
	std::list<CMeshObject*> m_RenderQueueArr[Renderer_OpenGL::GL_SHADER_PROGRAM_TYPE::NUM]{};
private:
	mat4x4 m_matCameraWorld;
	mat4x4 m_matView;
	mat4x4 m_matProj;
	mat4x4 m_matViewProj;

// Input Manager
public:
	GLFW_KeyManager m_KeyManager;
public:
	bool Key_Pressing(int inKey) { return m_KeyManager.Key_Pressing(inKey); }
	bool Key_Down(int inKey) { return m_KeyManager.Key_Down(inKey); }
	bool Key_Up(int inKey) { return m_KeyManager.Key_Up(inKey); }
};

