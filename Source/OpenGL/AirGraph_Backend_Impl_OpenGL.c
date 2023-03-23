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
#include "AirGraph_Backend_Impl_OpenGL.h"
#include <string.h>
#include <malloc.h>

AirResult AirEnableRenderAPI(
        AirRenderAPIFlags                       renderAPIFlag
)
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        AIR_THROW_ERROR("Error(Air_BackendImpl_OpenGL.c): Initialize glad failed.");

    return AIR_SUCCESS;
}

AirResult AirAllocateDeviceMemory(
        const AirDeviceMemoryAllocateInfo*      pAllocateInfo,
        AirDeviceMemory*                        pMemory
)
{
    AirDeviceMemory p_devmem = malloc(sizeof(AirDeviceMemory));
    p_devmem->size = pAllocateInfo->size;
    p_devmem->usage = GL_BIT_MAP(pAllocateInfo->usageFlag);

    int usage;
    usage = p_devmem->usage;

    glGenBuffers(1, &p_devmem->bufid);
    glBindBuffer(usage, p_devmem->bufid);
    glBufferData(usage, (GLintptr) p_devmem->size, AIR_NULL_HANDLE, GL_STATIC_DRAW);
    glBindBuffer(usage, 0);
    *pMemory = p_devmem;

    return AIR_SUCCESS;
}

AirResult AirBindDeviceMemory(
        AirDeviceMemory                         memory
)
{
    glBindBuffer(memory->usage, memory->bufid);
    return AIR_SUCCESS;
}

AirResult AirMapDeviceMemory(
        uint64_t                                off,
        AirDeviceMemoryAccessFlags              accessFlag,
        AirDeviceMemory                         memory,
        void**                                  pointer
)
{
    int usage = memory->usage;

    void *mmap = glMapBuffer(usage, GL_BIT_MAP(accessFlag));
    *pointer = (void *) (((char *) mmap) + off);

    return AIR_SUCCESS;
}

AirResult AirUnmapDeviceMemory(
        AirDeviceMemory                         memory
)
{
    glUnmapBuffer(memory->usage);
    return AIR_SUCCESS;
}

AirResult AirReadDeviceMemory(
        uint64_t                                off,
        uint64_t                                size,
        void*                                   pointer,
        AirDeviceMemory                         memory
)
{
    void *mmap;
    AirMapDeviceMemory(off, AIR_DEVICE_MEMORY_ACCESS_READ_ONLY_BIT, memory, &mmap);
    memcpy(pointer, ((char *) mmap) + off, size);

    return AIR_SUCCESS;
}

AirResult AirWriteDeviceMemory(
        uint64_t                                off,
        uint64_t                                size,
        void*                                   pointer,
        AirDeviceMemory                         memory
)
{
    void *mmap;
    AirMapDeviceMemory(off, AIR_DEVICE_MEMORY_ACCESS_WRITE_ONLY_BIT, memory, &mmap);
    memcpy(((char *) mmap) + off, pointer, size);

    return AIR_SUCCESS;
}

AirResult AirFreeDeviceMemory(
    AirDeviceMemory                             buffer
)
{
    glDeleteBuffers(1, &(buffer->bufid));
    free(buffer);

    return AIR_SUCCESS;
}

AirResult AirCmdClearColorBuffer(
        float                                   r,
        float                                   g,
        float                                   b,
        float                                   a
)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(r, g, b, a);
    return AIR_SUCCESS;
}