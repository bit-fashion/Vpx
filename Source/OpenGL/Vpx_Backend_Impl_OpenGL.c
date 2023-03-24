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

/* Creates on 2023/3/24. */
#include "Vpx_Backend_Impl_OpenGL.h"
#include <string.h>
#include <malloc.h>

//AirResult AirEnableRenderAPI(
//        AirRenderAPIFlags                       renderAPIFlag
//)
//{
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//        AIR_THROW_ERROR("Error(Air_BackendImpl_OpenGL.c): Initialize glad failed.");
//
//    return AIR_SUCCESS;
//}
//
//AirResult AirAllocateDeviceMemory(
//        const AirDeviceMemoryAllocateInfo*      pAllocateInfo,
//        AirDeviceMemory*                        pMemory
//)
//{
//    AirDeviceMemory p_devmem = malloc(sizeof(AirDeviceMemory));
//    p_devmem->size = pAllocateInfo->size;
//    p_devmem->usage = GL_BIT_MAP(pAllocateInfo->usageFlag);
//
//    int usage;
//    usage = p_devmem->usage;
//
//    glGenBuffers(1, &p_devmem->bufid);
//    glBindBuffer(usage, p_devmem->bufid);
//    glBufferData(usage, (GLintptr) p_devmem->size, AIR_NULL_HANDLE, GL_STATIC_DRAW);
//    glBindBuffer(usage, 0);
//    *pMemory = p_devmem;
//
//    return AIR_SUCCESS;
//}
//
//AirResult AirBindDeviceMemory(
//        AirDeviceMemory                         memory
//)
//{
//    glBindBuffer(memory->usage, memory->bufid);
//    return AIR_SUCCESS;
//}
//
//AirResult AirMapDeviceMemory(
//        uint64_t                                offset,
//        AirDeviceMemoryAccessFlags              accessFlag,
//        AirDeviceMemory                         memory,
//        void**                                  pointer
//)
//{
//    int usage = memory->usage;
//
//    void *mmap = glMapBuffer(usage, GL_BIT_MAP(accessFlag));
//    *pointer = (void *) (((char *) mmap) + offset);
//
//    return AIR_SUCCESS;
//}
//
//AirResult AirUnmapDeviceMemory(
//        AirDeviceMemory                         memory
//)
//{
//    glUnmapBuffer(memory->usage);
//    return AIR_SUCCESS;
//}
//
//AirResult AirReadDeviceMemory(
//        uint64_t                                offset,
//        uint64_t                                size,
//        void*                                   pointer,
//        AirDeviceMemory                         memory
//)
//{
//    void *mmap;
//    AirMapDeviceMemory(offset, AIR_DEVICE_MEMORY_ACCESS_READ_ONLY_BIT, memory, &mmap);
//    memcpy(pointer, ((char *) mmap) + offset, size);
//    AirUnmapDeviceMemory(memory);
//
//    return AIR_SUCCESS;
//}
//
//AirResult AirWriteDeviceMemory(
//        uint64_t                                offset,
//        uint64_t                                size,
//        void*                                   pointer,
//        AirDeviceMemory                         memory
//)
//{
//    void *mmap;
//    AirMapDeviceMemory(offset, AIR_DEVICE_MEMORY_ACCESS_WRITE_ONLY_BIT, memory, &mmap);
//    memcpy(((char *) mmap) + offset, pointer, size);
//    AirUnmapDeviceMemory(memory);
//
//    return AIR_SUCCESS;
//}
//
//AirResult AirFreeDeviceMemory(
//    AirDeviceMemory                             buffer
//)
//{
//    glDeleteBuffers(1, &(buffer->bufid));
//    free(buffer);
//
//    return AIR_SUCCESS;
//}
//
//AirResult AirAllocateVertexBufferMemory(
//    AirVertexBufferMemoryAllocateInfo*          pAllocateInfo,
//    AirVertexBufferMemoryLayout*                pLayouts,
//    unsigned int                                layoutsCount,
//    AirVertexBuffer*                            pVertexBuffer
//)
//{
//    unsigned int vao;
//    AirDeviceMemory memory;
//    AirVertexBuffer vtxbuf = malloc(sizeof(AirVertexBuffer));
//
//    glGenVertexArrays(1, &vao);
//    glBindVertexArray(vao);
//
//    AirDeviceMemoryAllocateInfo deviceMemoryAllocateInfo;
//    deviceMemoryAllocateInfo.size = pAllocateInfo->size;
//    deviceMemoryAllocateInfo.spaceFlag = pAllocateInfo->spaceFlag;
//    deviceMemoryAllocateInfo.usageFlag = AIR_DEVICE_MEMORY_USAGE_VERTEX_BUFFER_BIT;
//    AirAllocateDeviceMemory(&deviceMemoryAllocateInfo, &memory);
//    AirBindDeviceMemory(memory);
//    AirWriteDeviceMemory(0, pAllocateInfo->size, pAllocateInfo->pVertices, memory);
//
//    for (int i = 0; i < layoutsCount; i++) {
//        const AirVertexBufferMemoryLayout *layout = &pLayouts[i];
//        glVertexAttribPointer(layout->location, (int) layout->count, GL_FLOAT, GL_FALSE, (int) pAllocateInfo->stride,
//                              (const void *) ((intptr_t) layout->offset));
//        glEnableVertexAttribArray(layout->location);
//    }
//
//    vtxbuf->vao = vao;
//    vtxbuf->buf = memory;
//    *pVertexBuffer = vtxbuf;
//
//    return AIR_SUCCESS;
//}
//
//AirResult AirGetDeviceMemoryFromVertexBufferMemory(
//        AirVertexBuffer                             vertexBuffer,
//        AirDeviceMemory*                            pDeviceMemory
//)
//{
//    *pDeviceMemory = vertexBuffer->buf;
//    return AIR_SUCCESS;
//}
//
//AirResult AirBindVertexBufferMemory(
//        AirVertexBuffer                             vertexBuffer
//)
//{
//    glBindVertexArray(vertexBuffer->vao);
//    return AIR_SUCCESS;
//}
//
//AirResult AirFreeVertexBufferMemory(
//        AirVertexBuffer                             vertexBuffer
//)
//{
//    AirFreeDeviceMemory(vertexBuffer->buf);
//    glDeleteVertexArrays(1, &vertexBuffer->vao);
//    return AIR_SUCCESS;
//}
//
//AirResult AirBeginCommandBuffer(
//        AirCommandBuffer                            commandBuffer
//)
//{
//    return AIR_SUCCESS;
//}
//
//AirResult AirEndCommandBuffer(
//        AirCommandBuffer                            commandBuffer
//)
//{
//    return AIR_SUCCESS;
//}
//
//AirResult AirCmdClearColorBuffer(
//        float                                   r,
//        float                                   g,
//        float                                   b,
//        float                                   a
//)
//{
//    glClear(GL_COLOR_BUFFER_BIT);
//    glClearColor(r, g, b, a);
//    return AIR_SUCCESS;
//}
//
//AirResult AirCmdBindVertexBuffers(
//        AirCommandBuffer                            commandBuffer,
//        AirVertexBuffer*                            pBuffers,
//        uint32_t                                    bufferCount
//)
//{
//    for (int i = 0; i < bufferCount; i++) {
//        AirVertexBuffer vtxbuffer = (&pBuffers[i]);
//        glBindVertexArray(vtxbuffer->vao);
//    }
//
//    return AIR_SUCCESS;
//}
//
//AirResult AirCmdDrawArray(
//        AirCommandBuffer                        commandBuffer,
//        uint32_t                                firstVertex,
//        uint32_t                                vertexCount
//)
//{
//    glDrawArrays(GL_TRIANGLES, firstVertex, vertexCount);
//    return AIR_SUCCESS;
//}