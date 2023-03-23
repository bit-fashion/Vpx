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

/* Creates on 2023/3/20. */

#ifndef AIR_CORE_H
#define AIR_CORE_H 1

#include <stdio.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define AIR_VERSION_1_0_0

#define AIR_DEFINE_HANDLE(object) typedef struct object##_T *(object);

// <AIR DEFINE>: The AIR_API use export api.
#if defined(_WIN32)
#  define AIR_API_ATTR
#  define AIR_API_CALL __stdcall
#else
#  define AIR_API_ATTR
#  define AIR_API_CALL
#endif

#ifndef NDEBUG
#  define AIR_ASSERT(exp) assert(exp)
#else
#  define AIR_ASSERT(exp) /* DO NOTHIN! */
#endif

#define AIR_THROW_ERROR(msg) \
    fprintf(stderr, "%s\n", msg)

// <AIR DEFINE>: The AIR_MAIRE_VERSION is unified define version for apx applicatio.
#define AIR_MAKE_VERSION(major, minor, patch) \
    ( (((uint32_t)(major)) << 32) | (((uint32_t)(minor)) << 22) | (((uint32_t)(patch)) << 12) )

typedef uint32_t      AirBool32;
typedef uint64_t      AirPointer;
typedef uint32_t      AirFlags;
#define AIR_TRUE      (0U)
#define AIR_FALSE     (1U)

// <AIR DEFINE>: Define handles.
AIR_DEFINE_HANDLE(AirDeviceMemory)
AIR_DEFINE_HANDLE(AirVertexBuffer)
AIR_DEFINE_HANDLE(AirIndexBuffer)
AIR_DEFINE_HANDLE(AirTexture)
AIR_DEFINE_HANDLE(AirShaderModule)
AIR_DEFINE_HANDLE(AirPipeline)
AIR_DEFINE_HANDLE(AirFramebuffer)
AIR_DEFINE_HANDLE(AirRenderPass)
AIR_DEFINE_HANDLE(AirCommandBuffer)

#ifndef AIR_NULL_HANDLE
#  define AIR_NULL_HANDLE (NULL)
#endif

// <AIR DEFINE>: The following defines the enum.
typedef enum AirResult {
    AIR_SUCCESS = 0,
} AirResult;

typedef enum AirRenderAPI {
    AIR_ENABLE_RENDER_API_OPENGL_BIT = 0,
} AirRenderAPI;
typedef AirFlags AirRenderAPIFlags;

typedef enum AirDeviceMemoryFlagBits {
    AIR_DEVICE_MEMORY_USAGE_VERTEX_BUFFER_BIT = 0xA1008600,
    AIR_DEVICE_MEMORY_USAGE_INDEX_BUFFER_BIT = 0xA1008601,
    AIR_DEVICE_MEMORY_ACCESS_READ_ONLY_BIT = 0xA1008602,
    AIR_DEVICE_MEMORY_ACCESS_WRITE_ONLY_BIT = 0xA1008603,
    AIR_DEVICE_MEMORY_ACCESS_READ_WRITE_BIT = 0xA1008604,
    AIR_DEVICE_MEMORY_SPACE_IN_GPU_BIT = 0xA1008605,
    AIR_DEVICE_MEMORY_SPACE_IN_CPU_BIT = 0xA1008606,
} AirDeviceMemoryFlagBits;
typedef AirFlags AirDeviceMemoryUsageFlags;
typedef AirFlags AirDeviceMemoryAccessFlags;
typedef AirFlags AirDeviceMemorySpaceFlags;

typedef enum AirPolygonModeFlagBits {
    AIR_POLYGON_MODE_FILL_BIT = 0xA1008700,
    AIR_POLYGON_MODE_LINE_BIT = 0xA1008701,
    AIR_POLYGON_MODE_POINT_BIT = 0xA1008702,
} AirPolygognModeFlagBits;
typedef AirFlags AirPolygonModeFlags;

typedef enum AirTextureSamplerModeFlagBits {
    AIR_SAMPLER_MODE_REPEAT_BIT = 0xA100880,
    AIR_SAMPLER_MODE_MIRRORED_REPEAT_BIT = 0xA1008801,
    AIR_SAMPLER_MODE_CLAMP_TO_EDGE_BIT = 0xA1008802,
    AIR_SAMPLER_MODE_CLAMP_TO_BORDER_BIT = 0xA1008803,
    AIR_SAMPLER_FILTER_MODE_LINEAR_BIT = 0xA1008804,
    AIR_SAMPLER_FILTER_MODE_NEAREST_BIT = 0xA1008805,
} AirTextureSamplerModeFlagBits;
typedef AirFlags AirTextureSamplerModeFlags;

// <AIR DEFINE>: The following defines the struct.
typedef struct AirDeviceMemoryAllocateInfo {
    uint64_t                                    size;
    AirDeviceMemoryUsageFlags                   usageFlag;
    AirDeviceMemorySpaceFlags                   spaceFlag;
} AirDeviceMemoryAllocateInfo;

typedef struct AirVertexBufferMemoryAllocateInfo {
    uint64_t                                    size;
    unsigned int                                count;
    float*                                      pVertices;
    AirDeviceMemorySpaceFlags                   sapceFlag;
} AirVertexBufferMemoryAllocateInfo;

typedef struct AirVertexBufferMemoryLayout {
    unsigned int                                location;
    unsigned int                                size;
    unsigned int                                off;
} AirVertexBufferMemoryLayout;

// <AIR DEFINE>: The following defines the functions.
AIR_API_ATTR AirResult AIR_API_CALL AirEnableRenderAPI(
    AirRenderAPIFlags                           renderAPIFlag
);

AIR_API_ATTR AirResult AIR_API_CALL AirAllocateDeviceMemory(
    const AirDeviceMemoryAllocateInfo*          pAllocateInfo,
    AirDeviceMemory*                            pMemory
);

AIR_API_ATTR AirResult AIR_API_CALL AirBindDeviceMemory(
    AirDeviceMemory                             memory
);

AIR_API_ATTR AirResult AIR_API_CALL AirMapDeviceMemory(
    uint64_t                                    off,
    AirDeviceMemoryAccessFlags                  accessFlag,
    AirDeviceMemory                             memory,
    void**                                      pointer
);

AIR_API_ATTR AirResult AIR_API_CALL AirUnmapDeviceMemory(
    AirDeviceMemory                             memory
);

AIR_API_ATTR AirResult AIR_API_CALL AirReadDeviceMemory(
    uint64_t                                    off,
    uint64_t                                    size,
    void*                                       pointer,
    AirDeviceMemory                             memory
);

AIR_API_ATTR AirResult AIR_API_CALL AirWriteDeviceMemory(
    uint64_t                                    off,
    uint64_t                                    size,
    void*                                       pointer,
    AirDeviceMemory                             memory
);

AIR_API_ATTR AirResult AIR_API_CALL AirFreeDeviceMemory(
    AirDeviceMemory                             buffer
);

AIR_API_ATTR AirResult AIR_API_CALL AirAllocateVertexBufferMemory(
    AirVertexBufferMemoryAllocateInfo*          pAllocateInfo,
    AirVertexBufferMemoryLayout*                pLayouts,
    unsigned int                                layoutsCount,
    AirVertexBuffer*                            pVertexBuffer
);

AIR_API_ATTR AirResult AIR_API_CALL AirGetDeviceMemoryFromVertexBufferMemory(
    AirVertexBuffer                             vertexBuffer,
    AirDeviceMemory*                            pDeviceMemory
);

AIR_API_ATTR AirResult AIR_API_CALL AirFreeVertexBufferMemory(
    AirVertexBuffer                             vertexBuffer
);

AIR_API_ATTR AirResult AIR_API_CALL AirBeginCommandBuffer(
    AirCommandBuffer                            commandBuffer
);

AIR_API_ATTR AirResult AIR_API_CALL AirEndCommandBuffer(
    AirCommandBuffer                            commandBuffer
);

AIR_API_ATTR AirResult AIR_API_CALL AirCmdClearColorBuffer(
    float                                       r,
    float                                       g,
    float                                       b,
    float                                       a
);

AIR_API_ATTR AirResult AIR_API_CALL AirCmdBindVertexBuffers(
    AirCommandBuffer                            commandBuffer,
    AirVertexBuffer*                            pBuffers,
    uint32_t                                    bufferCount
);

AIR_API_ATTR AirResult AIR_API_CALL AirCmdBindIndexBuffer(
    AirCommandBuffer                            commandBuffer,
    AirIndexBuffer                              indexBuffer
);

AIR_API_ATTR AirResult AIR_API_CALL AirCmdDrawArray(
        AirCommandBuffer                        commandBuffer,
        uint32_t                                firstVertex,
        uint32_t                                vertexCount
);

AIR_API_ATTR AirResult AIR_API_CALL AirCmdDrawIndexed(
        AirCommandBuffer                        commandBuffer,
        uint32_t                                firstIndex,
        uint32_t                                indexCount
);

#ifdef __cplusplus
};
#endif

#endif /* AIR_CORE_H */