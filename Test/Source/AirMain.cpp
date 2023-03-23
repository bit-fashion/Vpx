#include "Window/SportsWindow.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

int main()
{
    auto *sportswin = new SportsWindow(1000, 800, "sp2r-test-main");
    sportswin->SetAttribFloating(false);
    sportswin->SetAttribMousePassthrough(true);

    // Allocate Buffer Memory.
    AirDeviceMemoryAllocateInfo deviceMemoryAllocateInfo;
    deviceMemoryAllocateInfo.size = sizeof(glm::vec3);
    deviceMemoryAllocateInfo.usageFlag = AIR_DEVICE_MEMORY_USAGE_VERTEX_BUFFER_BIT;
    deviceMemoryAllocateInfo.spaceFlag = AIR_DEVICE_MEMORY_SPACE_IN_GPU_BIT;

    AirDeviceMemory memory;
    AirAllocateMemory(&deviceMemoryAllocateInfo, &memory);
    AirBindMemory(memory);

    glm::vec3 color{ 0.1f, 0.5f, 0.8f };
    AirWriteMemory(0, sizeof(glm::vec3), &color, memory);

    char *mmap;
    AirMapMemory(0, AIR_DEVICE_MEMORY_ACCESS_WRITE_ONLY_BIT, memory, (void **) &mmap);

    while (!sportswin->ShouldClose()) {
        // Begin
        AirCmdClearColorBuffer(0.5f, 0.2f, 0.4f, 1.0f);

        // Air
        sportswin->BeginImGuiRender();
        {
            ImGui::Begin("Memory");
            ImGui::DragFloat3("color", (float *) mmap, 0.01f, 0.01f, 1.0f);
            ImGui::End();
        }
        sportswin->EndImGuiRender();

    }

    AirUnmapMemory(memory);
    // AirFreeMemory(memory);

    return 0;
}
