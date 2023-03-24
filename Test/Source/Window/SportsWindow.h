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
#pragma once

#include <string>
#include <stdexcept>
#include "Include/AirGraph/vpx.h"
#include <GLFW//glfw3.h>
#include <imgui.h>

enum SportsInputKey {
    /* The unknown key */
    SPORTS_WINDOW_INPUT_KEY_UNKNOWN=            -1,

    /* Printable keys */
    SPORTS_WINDOW_INPUT_KEY_SPACE=              32,
    SPORTS_WINDOW_INPUT_KEY_APOSTROPHE=         39,  /* ' */
    SPORTS_WINDOW_INPUT_KEY_COMMA=              44,  /* , */
    SPORTS_WINDOW_INPUT_KEY_MINUS=              45,  /* - */
    SPORTS_WINDOW_INPUT_KEY_PERIOD=             46,  /* . */
    SPORTS_WINDOW_INPUT_KEY_SLASH=              47,  /* / */
    SPORTS_WINDOW_INPUT_KEY_0=                  48,
    SPORTS_WINDOW_INPUT_KEY_1=                  49,
    SPORTS_WINDOW_INPUT_KEY_2=                  50,
    SPORTS_WINDOW_INPUT_KEY_3=                  51,
    SPORTS_WINDOW_INPUT_KEY_4=                  52,
    SPORTS_WINDOW_INPUT_KEY_5=                  53,
    SPORTS_WINDOW_INPUT_KEY_6=                  54,
    SPORTS_WINDOW_INPUT_KEY_7=                  55,
    SPORTS_WINDOW_INPUT_KEY_8=                  56,
    SPORTS_WINDOW_INPUT_KEY_9=                  57,
    SPORTS_WINDOW_INPUT_KEY_SEMICOLON=          59,  /* ; */
    SPORTS_WINDOW_INPUT_KEY_EQUAL=              61,  /* = */
    SPORTS_WINDOW_INPUT_KEY_A=                  65,
    SPORTS_WINDOW_INPUT_KEY_B=                  66,
    SPORTS_WINDOW_INPUT_KEY_C=                  67,
    SPORTS_WINDOW_INPUT_KEY_D=                  68,
    SPORTS_WINDOW_INPUT_KEY_E=                  69,
    SPORTS_WINDOW_INPUT_KEY_F=                  70,
    SPORTS_WINDOW_INPUT_KEY_G=                  71,
    SPORTS_WINDOW_INPUT_KEY_H=                  72,
    SPORTS_WINDOW_INPUT_KEY_I=                  73,
    SPORTS_WINDOW_INPUT_KEY_J=                  74,
    SPORTS_WINDOW_INPUT_KEY_K=                  75,
    SPORTS_WINDOW_INPUT_KEY_L=                  76,
    SPORTS_WINDOW_INPUT_KEY_M=                  77,
    SPORTS_WINDOW_INPUT_KEY_N=                  78,
    SPORTS_WINDOW_INPUT_KEY_O=                  79,
    SPORTS_WINDOW_INPUT_KEY_P=                  80,
    SPORTS_WINDOW_INPUT_KEY_Q=                  81,
    SPORTS_WINDOW_INPUT_KEY_R=                  82,
    SPORTS_WINDOW_INPUT_KEY_S=                  83,
    SPORTS_WINDOW_INPUT_KEY_T=                  84,
    SPORTS_WINDOW_INPUT_KEY_U=                  85,
    SPORTS_WINDOW_INPUT_KEY_V=                  86,
    SPORTS_WINDOW_INPUT_KEY_W=                  87,
    SPORTS_WINDOW_INPUT_KEY_X=                  88,
    SPORTS_WINDOW_INPUT_KEY_Y=                  89,
    SPORTS_WINDOW_INPUT_KEY_Z=                  90,
    SPORTS_WINDOW_INPUT_KEY_LEFT_BRACKET=       91,  /* [ */
    SPORTS_WINDOW_INPUT_KEY_BACKSLASH=          92,  /* \ */
    SPORTS_WINDOW_INPUT_KEY_RIGHT_BRACKET=      93,  /* ] */
    SPORTS_WINDOW_INPUT_KEY_GRAVE_ACCENT=       96,  /* ` */
    SPORTS_WINDOW_INPUT_KEY_WORLD_1=            161, /* non-US #1 */
    SPORTS_WINDOW_INPUT_KEY_WORLD_2=            162, /* non-US #2 */

    /* Function keys */
    SPORTS_WINDOW_INPUT_KEY_ESCAPE=             256,
    SPORTS_WINDOW_INPUT_KEY_ENTER=              257,
    SPORTS_WINDOW_INPUT_KEY_TAB=                258,
    SPORTS_WINDOW_INPUT_KEY_BACKSPACE=          259,
    SPORTS_WINDOW_INPUT_KEY_INSERT=             260,
    SPORTS_WINDOW_INPUT_KEY_DELETE=             261,
    SPORTS_WINDOW_INPUT_KEY_RIGHT=              262,
    SPORTS_WINDOW_INPUT_KEY_LEFT=               263,
    SPORTS_WINDOW_INPUT_KEY_DOWN=               264,
    SPORTS_WINDOW_INPUT_KEY_UP=                 265,
    SPORTS_WINDOW_INPUT_KEY_PAGE_UP=            266,
    SPORTS_WINDOW_INPUT_KEY_PAGE_DOWN=          267,
    SPORTS_WINDOW_INPUT_KEY_HOME=               268,
    SPORTS_WINDOW_INPUT_KEY_END=                269,
    SPORTS_WINDOW_INPUT_KEY_CAPS_LOCK=          280,
    SPORTS_WINDOW_INPUT_KEY_SCROLL_LOCK=        281,
    SPORTS_WINDOW_INPUT_KEY_NUM_LOCK=           282,
    SPORTS_WINDOW_INPUT_KEY_PRINT_SCREEN=       283,
    SPORTS_WINDOW_INPUT_KEY_PAUSE=              284,
    SPORTS_WINDOW_INPUT_KEY_F1=                 290,
    SPORTS_WINDOW_INPUT_KEY_F2=                 291,
    SPORTS_WINDOW_INPUT_KEY_F3=                 292,
    SPORTS_WINDOW_INPUT_KEY_F4=                 293,
    SPORTS_WINDOW_INPUT_KEY_F5=                 294,
    SPORTS_WINDOW_INPUT_KEY_F6=                 295,
    SPORTS_WINDOW_INPUT_KEY_F7=                 296,
    SPORTS_WINDOW_INPUT_KEY_F8=                 297,
    SPORTS_WINDOW_INPUT_KEY_F9=                 298,
    SPORTS_WINDOW_INPUT_KEY_F10=                299,
    SPORTS_WINDOW_INPUT_KEY_F11=                300,
    SPORTS_WINDOW_INPUT_KEY_F12=                301,
    SPORTS_WINDOW_INPUT_KEY_F13=                302,
    SPORTS_WINDOW_INPUT_KEY_F14=                303,
    SPORTS_WINDOW_INPUT_KEY_F15=                304,
    SPORTS_WINDOW_INPUT_KEY_F16=                305,
    SPORTS_WINDOW_INPUT_KEY_F17=                306,
    SPORTS_WINDOW_INPUT_KEY_F18=                307,
    SPORTS_WINDOW_INPUT_KEY_F19=                308,
    SPORTS_WINDOW_INPUT_KEY_F20=                309,
    SPORTS_WINDOW_INPUT_KEY_F21=                310,
    SPORTS_WINDOW_INPUT_KEY_F22=                311,
    SPORTS_WINDOW_INPUT_KEY_F23=                312,
    SPORTS_WINDOW_INPUT_KEY_F24=                313,
    SPORTS_WINDOW_INPUT_KEY_F25=                314,
    SPORTS_WINDOW_INPUT_KEY_KP_0=               320,
    SPORTS_WINDOW_INPUT_KEY_KP_1=               321,
    SPORTS_WINDOW_INPUT_KEY_KP_2=               322,
    SPORTS_WINDOW_INPUT_KEY_KP_3=               323,
    SPORTS_WINDOW_INPUT_KEY_KP_4=               324,
    SPORTS_WINDOW_INPUT_KEY_KP_5=               325,
    SPORTS_WINDOW_INPUT_KEY_KP_6=               326,
    SPORTS_WINDOW_INPUT_KEY_KP_7=               327,
    SPORTS_WINDOW_INPUT_KEY_KP_8=               328,
    SPORTS_WINDOW_INPUT_KEY_KP_9=               329,
    SPORTS_WINDOW_INPUT_KEY_KP_DECIMAL=         330,
    SPORTS_WINDOW_INPUT_KEY_KP_DIVIDE=          331,
    SPORTS_WINDOW_INPUT_KEY_KP_MULTIPLY=        332,
    SPORTS_WINDOW_INPUT_KEY_KP_SUBTRACT=        333,
    SPORTS_WINDOW_INPUT_KEY_KP_ADD=             334,
    SPORTS_WINDOW_INPUT_KEY_KP_ENTER=           335,
    SPORTS_WINDOW_INPUT_KEY_KP_EQUAL=           336,
    SPORTS_WINDOW_INPUT_KEY_LEFT_SHIFT=         340,
    SPORTS_WINDOW_INPUT_KEY_LEFT_CONTROL=       341,
    SPORTS_WINDOW_INPUT_KEY_LEFT_ALT=           342,
    SPORTS_WINDOW_INPUT_KEY_LEFT_SUPER=         343,
    SPORTS_WINDOW_INPUT_KEY_RIGHT_SHIFT=        344,
    SPORTS_WINDOW_INPUT_KEY_RIGHT_CONTROL=      345,
    SPORTS_WINDOW_INPUT_KEY_RIGHT_ALT=          346,
    SPORTS_WINDOW_INPUT_KEY_RIGHT_SUPER=        347,
    SPORTS_WINDOW_INPUT_KEY_MENU=               348,
    SPORTS_WINDOW_INPUT_KEY_LAST=               SPORTS_WINDOW_INPUT_KEY_MENU,
};

class SportsWindow;

typedef void (*SportsWindowResizeCallback) (const SportsWindow *p_window, int w, int h);

/* 封装的GLFW窗口函数 */
class SportsWindow {
public:
    SportsWindow(int width, int height, std::string title);
    ~SportsWindow();

    bool ShouldClose();
    void Close();
    void Maximized();
    void Borderless(); /* 无边框窗口 */
    void HideTitleBar();
    void ResetDimension(unsigned int width, unsigned int height);
    void SwapBuffers();
    void MakeCurrentContext();

    void SetWindowSizeCallback(SportsWindowResizeCallback callback);

    void SetAttribResizable(bool value);
    void SetAttribOpacity(float opacity);
    void SetAttribFloating(bool value);
    void SetAttribMousePassthrough(bool value);

    bool GetAttribResizable();
    float GetAttribOpacity();
    bool GetAttribFloating();
    bool GetAttribMousePassthrough();
    bool GetKey(SportsInputKey key);

    int GetWidth()
      {
        return _width;
      }

    int GetHeight()
      {
        return _height;
      }

    void BeginImGuiRender();
    void EndImGuiRender();

    void PollEvents();

private:
    int _width;
    int _height;
    std::string _title;
    const void* *_handle;

private:
    SportsWindowResizeCallback _WindowSizeCallback = nullptr;
};