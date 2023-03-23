# CMakeList.txt: SportsSoftware 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
CMAKE_MINIMUM_REQUIRED (VERSION 3.8)

PROJECT ("Sp2rTest")

# SET(CMAKE_EXE_LINKER_FLAGS "-static")

INCLUDE_DIRECTORIES(${PROJECT_NAME} ./ Include)
INCLUDE_DIRECTORIES(${PROJECT_NAME} SYSTEM ../Include)
INCLUDE_DIRECTORIES(${PROJECT_NAME} SYSTEM Depnedencies/include Depnedencies/include/imgui Depnedencies/imgui/backends)

LINK_LIBRARIES(imm32)
LINK_DIRECTORIES(${PROJECT_NAME} "../cmake-build-debug")

# 将源代码添加到此项目的可执行文件。
ADD_EXECUTABLE(${PROJECT_NAME}
        Source/AirMain.cpp
        Source/Window/SportsWindow.cpp
        # --* glad *-- #
        "Depnedencies/glad/glad.c"
        # --* imgui *-- #
        "Depnedencies/imgui/imgui.cpp"
        "Depnedencies/imgui/imgui_tables.cpp"
        "Depnedencies/imgui/imgui_demo.cpp"
        "Depnedencies/imgui/imgui_draw.cpp"
        "Depnedencies/imgui/imgui_widgets.cpp"
        "Depnedencies/imgui/backends/imgui_impl_opengl3.cpp"
        "Depnedencies/imgui/backends/imgui_impl_glfw.cpp"
)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} -lgraph0)
