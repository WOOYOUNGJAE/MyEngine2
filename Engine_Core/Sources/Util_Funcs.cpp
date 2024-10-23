#include "pch.h"
#include "Util_Funcs.h"

int ConvertVkToGlfwKey(int vkKey)
{
    // VK와 GLFW 매크로 간 직접 매핑
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