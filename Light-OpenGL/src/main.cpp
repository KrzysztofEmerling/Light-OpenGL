#include "Renderer/Macros.h"
#include "Renderer/GLRenderer.h"

#include "Core/Transform.h"

#include "Tests/Test.h"
#include "Tests/BgColor.h"
#include "Tests/Primitives.h"
#include "Tests/Texture2D.h"
#include "Tests/ParentTransform.h"
 #include "Tests/SimpleBaching.h"

#include "Tests/ShadersShowdown.h"

#include <iostream>
bool isFullScreen = false;  
int windowWidth = 960;
int windowHeight = 540;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void ToggleFullScreen(GLFWwindow*& window, int width, int height);

int main(int argc, char* argv[])
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(windowWidth, windowHeight, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);
  
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "glew initialization error" << std::endl;
        return -1;
    }
    std::cout << glGetString(GL_VERSION) << std::endl;

    glCall(glEnable(GL_BLEND));
    glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui::StyleColorsClassic();
    //ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();
    ImGui_ImplOpenGL3_Init((char*)glGetString(450));

    Tests::Test* currentTest = nullptr;
    Tests::Menu* testMenu = new Tests::Menu(currentTest);
    currentTest = testMenu;

    testMenu->RegisterTest<Tests::BgColor>("BgColor");
    testMenu->RegisterTest<Tests::Primitives>("Primitives");
    testMenu->RegisterTest<Tests::Texture2D>("Texture2D");
    testMenu->RegisterTest<Tests::ParentTransform>("ParentTransform");
    testMenu->RegisterTest<Tests::SimpleBaching>("SimpleBaching"); 
    testMenu->RegisterTest<Tests::ShadersShowdown>("ShadersShowdown");

    /* Parce terminal arguments */
    int testNumber = -1;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-t" && (i + 1) < argc) {
            testNumber = std::atoi(argv[++i]); 
        }
        else if (arg == "-f") {
            ToggleFullScreen(window, windowWidth, windowHeight); 
        }
        else if (arg == "-w" && (i + 1) < argc) {
            windowWidth = std::atoi(argv[++i]); 
        }
        else if (arg == "-h" && (i + 1) < argc) {
            windowHeight = std::atoi(argv[++i]); 
        }
        else {
            std::cout << "Nieznany argument: " << arg << std::endl;
            return 1; 
        }
    }
    if (!isFullScreen)
    {
        glfwSetWindowSize(window, windowWidth, windowHeight);
        framebuffer_size_callback(window, windowWidth, windowHeight);
    }
    testMenu->SetTest(testNumber);
    

    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_F11) == GLFW_PRESS)
        {
            ToggleFullScreen(window, windowWidth, windowHeight);
        }

        Graphics::GLRenderer::Clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (currentTest)
        {
            currentTest->OnUpdate((float)glfwGetTime());
            currentTest->OnRender();

            ImGui::Begin("Test");
            if (currentTest != testMenu && ImGui::Button("<-"))
            {
                delete currentTest;
                currentTest = testMenu;
            }
            currentTest->OnImGuiRender();
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    if (currentTest != testMenu)
    {
        delete testMenu;
    }
    delete currentTest;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) 
{
    glViewport(0, 0, width, height);
    Graphics::GLRenderer::UpdateWindowSize(width,height);
    float temp = Graphics::GLRenderer::GetAspectRatio();
}

void ToggleFullScreen(GLFWwindow*& window, int width, int height)
{
    static int windowedWidth = width, windowedHeight = height;
    static int windowedPosX = 100, windowedPosY = 100;

    if (!isFullScreen)
    {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        glfwGetWindowSize(window, &windowedWidth, &windowedHeight);
        glfwGetWindowPos(window, &windowedPosX, &windowedPosY);

        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
    }
    else
    {
        glfwSetWindowMonitor(window, nullptr, windowedPosX, windowedPosY, windowedWidth, windowedHeight, GLFW_DONT_CARE);
    }

    isFullScreen = !isFullScreen;  
}