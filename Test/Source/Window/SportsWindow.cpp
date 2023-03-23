/* ************************************************************************
 *
 * Copyright (C) 2022 Vincent Luo All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ************************************************************************/

/* Creates on 2023/3/15. */
#include "SportsWindow.h"

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

static bool INITIALIZED_GLFW = GLFW_FALSE;

/* SportsWindow窗口句柄结构体 */
struct SportsWindowContext {
    GLFWwindow *handle;
    GLFWmonitor *monitor;
    const GLFWvidmode *vidmode;
    ImGuiIO *io;
};

/* 获取 (GLFWwindow *) */
#define GLFWHANDLE(hwindow) ( ((SportsWindowContext *) (hwindow))->handle )
/* 获取 (GLFWmonitor *) */
#define GLFWMONITOR(hwindow) ( ((SportsWindowContext *) (hwindow))->monitor )
/* 获取 (const GLFWvidmode *) */
#define GLFWVIDMODE(hwindow) ( ((SportsWindowContext *) (hwindow))->vidmode )

SportsWindow::SportsWindow(int width, int height, std::string title) :
        _width(width), _height(height), _title(std::move(title))
{
    auto *sportsWindowContext = new SportsWindowContext();

    /* 初始化GLFW */
    if (!INITIALIZED_GLFW) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    /* 创建窗口 */
    GLFWwindow *glfwwnd;
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    if ((glfwwnd = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL)) == NULL)
        throw std::runtime_error("Error failed create window in opengl.");
    glfwMakeContextCurrent(glfwwnd);

    glfwSetWindowUserPointer(glfwwnd, this);

    /* 初始化渲染API */
    if (!INITIALIZED_GLFW) {
        // ApxInitializeRenderAPI(RenderAPI::OpenGL);
        AirEnableRenderAPI(AIR_ENABLE_RENDER_API_OPENGL_BIT);
        INITIALIZED_GLFW = GLFW_TRUE;
    }

    sportsWindowContext->handle = glfwwnd;
    sportsWindowContext->monitor = monitor;
    sportsWindowContext->vidmode = glfwGetVideoMode(monitor);

    /* 初始化 ImGui */
    const char *GLSL_VERSION = "#version 100";

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(glfwwnd, true);
    ImGui_ImplOpenGL3_Init(GLSL_VERSION);

    sportsWindowContext->io = &io;
    _handle = (const void* *) sportsWindowContext;
}

SportsWindow::~SportsWindow()
{
    glfwDestroyWindow(GLFWHANDLE(_handle));
    delete _handle;
}

bool SportsWindow::ShouldClose()
{
    return glfwWindowShouldClose(GLFWHANDLE(_handle));
}

void SportsWindow::Close()
{
    glfwSetWindowShouldClose(GLFWHANDLE(_handle), GLFW_TRUE);
}

void SportsWindow::Maximized()
{
    glfwMaximizeWindow(GLFWHANDLE(_handle));
}

void SportsWindow::Borderless()
{
    auto *vidmode = GLFWVIDMODE(_handle);
    glfwSetWindowMonitor(GLFWHANDLE(_handle), GLFWMONITOR(_handle),
                         0, 0, vidmode->width, vidmode->height, vidmode->refreshRate);
}

void SportsWindow::HideTitleBar()
{
    glfwSetWindowAttrib(GLFWHANDLE(_handle), GLFW_DECORATED, false);
}

void SportsWindow::ResetDimension(unsigned int width, unsigned int height)
{
    _width = width;
    _height = height;
    glfwSetWindowSize(GLFWHANDLE(_handle), _width, _height);
}

void SportsWindow::SwapBuffers()
{
    glfwSwapBuffers(GLFWHANDLE(_handle));
}

void SportsWindow::MakeCurrentContext()
{
    glfwMakeContextCurrent(GLFWHANDLE(_handle));
}

void SportsWindow::SetWindowSizeCallback(SportsWindowResizeCallback callback)
{
    _WindowSizeCallback = callback;
    glfwSetWindowSizeCallback(GLFWHANDLE(_handle), [](GLFWwindow *glfwwnd, int w, int h) {
        auto sportswin = (SportsWindow *) glfwGetWindowUserPointer(glfwwnd);
        sportswin->_WindowSizeCallback(sportswin, w, h);
    });
}

void SportsWindow::SetAttribResizable(bool value)
{
    glfwSetWindowAttrib(GLFWHANDLE(_handle), GLFW_RESIZABLE, value);
}

void SportsWindow::SetAttribOpacity(float opacity)
{
    glfwSetWindowOpacity(GLFWHANDLE(_handle), opacity);
}

void SportsWindow::SetAttribFloating(bool value)
{
    glfwSetWindowAttrib(GLFWHANDLE(_handle), GLFW_FLOATING, value);
}

void SportsWindow::SetAttribMousePassthrough(bool value)
{
    // TODO
}

bool SportsWindow::GetAttribResizable()
{
    return glfwGetWindowAttrib(GLFWHANDLE(_handle), GLFW_RESIZABLE);
}

float SportsWindow::GetAttribOpacity()
{
    return glfwGetWindowOpacity(GLFWHANDLE(_handle));
}

bool SportsWindow::GetAttribFloating()
{
    return glfwGetWindowAttrib(GLFWHANDLE(_handle), GLFW_FLOATING);
}

bool SportsWindow::GetAttribMousePassthrough()
{
    // TODO
    return false;
}

bool SportsWindow::GetKey(SportsInputKey key)
{
    return glfwGetKey(GLFWHANDLE(_handle), key) == GLFW_PRESS;
}

void SportsWindow::BeginImGuiRender()
{
    PollEvents();
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void SportsWindow::EndImGuiRender()
{
    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    SwapBuffers();
}

void SportsWindow::PollEvents()
{
    glfwPollEvents();
}
