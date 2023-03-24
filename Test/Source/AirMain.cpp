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
    AirAllocateDeviceMemory(&deviceMemoryAllocateInfo, &memory);
    AirBindDeviceMemory(memory);

    glm::vec3 color{ 0.1f, 0.5f, 0.8f };
    AirWriteDeviceMemory(0, sizeof(glm::vec3), &color, memory);

    float vertices[3 * 3] = {
            -0.5, 0.5f, 0.0f,
            0.5, 0.5f, 0.0f,
            0.5, -0.5f, 0.0f,
    };

    AirVertexBuffer vtxbuffer;
    AirVertexBufferMemoryAllocateInfo vertexBufferMemoryAllocateInfo;
    vertexBufferMemoryAllocateInfo.size = sizeof(vertices);
    vertexBufferMemoryAllocateInfo.stride = sizeof(vertices);
    vertexBufferMemoryAllocateInfo.verticesCount = sizeof(vertices) / sizeof(float);
    vertexBufferMemoryAllocateInfo.pVertices = vertices;
    vertexBufferMemoryAllocateInfo.spaceFlag = AIR_DEVICE_MEMORY_SPACE_IN_GPU_BIT;

    AirVertexBufferMemoryLayout layouts[] = {
            { 0, 0, 3 },
    };

    AirAllocateVertexBufferMemory(&vertexBufferMemoryAllocateInfo, layouts, (sizeof(layouts) / sizeof(AirVertexBufferMemoryLayout)),
                                  &vtxbuffer);

    char *mmap;
    AirMapDeviceMemory(0, AIR_DEVICE_MEMORY_ACCESS_WRITE_ONLY_BIT, memory, (void **) &mmap);

   while (!sportswin->ShouldClose()) {
        // Begin
        AirCmdClearColorBuffer(0.5f, 0.2f, 0.4f, 1.0f);

        // Vpx
        sportswin->BeginImGuiRender();
        {
            AirCmdBindVertexBuffers(NULL, &vtxbuffer, 1);
            AirCmdDrawArray(NULL, 0, 3);

            ImGui::Begin("Memory");
            ImGui::DragFloat3("color", (float *) mmap, 0.01f, 0.01f, 1.0f);
            ImGui::End();
        }
        sportswin->EndImGuiRender();

    }

    AirUnmapDeviceMemory(memory);
    // AirFreeMemory(memory);

    return 0;
}
