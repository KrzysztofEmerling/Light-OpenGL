#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include"stb_image/stb_image.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

#include <cmath>
#include <memory>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

void GLClearError();
bool GLLogCall();

#ifdef PLATFORM_WINDOWS
#define DEBUG_BREAK DEBUG_BREAK
#endif

#ifdef PLATFORM_LINUX
#define DEBUG_BREAK  __asm__("int $3")
#endif

#define ASSERT(x) if(!(x)) DEBUG_BREAK;

#ifdef _DEBUG
#define glCall(x) GLClearError(); \
    x;\
    ASSERT(GLLogCall())

#define ASSERT_DebugOnly(x) if(!(x)) DEBUG_BREAK;
#else
#define glCall(x) x

#define ASSERT_DebugOnly(x)
#endif

