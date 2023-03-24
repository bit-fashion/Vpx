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

#ifndef _VPX_CORE_H
#define _VPX_CORE_H 1

#include <stdio.h>
#include <stdint.h>
#include "vpx_platform.h"

#ifdef __cplusplus
extern "C" {
#endif

#define VPX_VERSION_1_0_0

#define VPX_DEFINE_HANDLE(object) typedef struct object##_T *(object);

// <VPX DEFINE>: The VPXAPI use export api.
#if defined(_WIN32)
#  define VPXAPI_ATTR
#  define VPXAPI_CALL __stdcall
#else
#  define VPXAPI_ATTR
#  define VPXAPI_CALL
#endif

#ifndef NDEBUG
#  define VPX_ASSERT(exp) assert(exp)
#else
#  define VPX_ASSERT(exp) /* DO NOTHIN! */
#endif

#define VPX_THROW_ERROR(msg) \
    fprintf(stderr, "%s\n", msg)

// <VPX DEFINE>: The VPX_MVPXE_VERSION is unified define version for apx applicatio.
#define VPX_MAKE_VERSION(major, minor, patch) \
    ( (((uint32_t)(major)) << 32) | (((uint32_t)(minor)) << 22) | (((uint32_t)(patch)) << 12) )

typedef uint32_t      VpxUint32;
typedef uint64_t      VpxUint64;
typedef float         VpxFloat;
typedef VpxUint32     VpxFlags;
typedef VpxUint64     VpxPointer;
typedef VpxUint32     VpxBool32;
#define VPX_TRUE      (0U)
#define VPX_FALSE     (1U)

// <VPX DEFINE>: Define handles.
VPX_DEFINE_HANDLE(VpxDeviceMemory)
VPX_DEFINE_HANDLE(VpxVertexBuffer)
VPX_DEFINE_HANDLE(VpxIndexBuffer)
VPX_DEFINE_HANDLE(VpxTexture)
VPX_DEFINE_HANDLE(VpxShaderModule)
VPX_DEFINE_HANDLE(VpxPipeline)
VPX_DEFINE_HANDLE(VpxFramebuffer)
VPX_DEFINE_HANDLE(VpxRenderPass)
VPX_DEFINE_HANDLE(VpxCommandBuffer)

#ifndef VPX_NULL_HANDLE
#  define VPX_NULL_HANDLE (NULL)
#endif

// <VPX DEFINE>: The following defines the enum.
typedef enum VpxDefineSupportRenderAPI {
    VPX_RENDER_API_OPENGL = 0,
    VPX_RENDER_API_VULKAN = 1,
} VpxDefineSupportRenderAPI;

typedef enum VpxResult {
    VPX_SUCCESS = 0,
} VpxResult;

typedef enum VpxDeviceMemoryFlagBits {
    VPX_DEVICE_MEMORY_USAGE_VERTEX_BUFFER_BIT = 0xA1008600,
    VPX_DEVICE_MEMORY_USAGE_INDEX_BUFFER_BIT = 0xA1008601,
    VPX_DEVICE_MEMORY_STORAGE_GPU_BIT = 0xA1008602,
    VPX_DEVICE_MEMORY_STORAGE_CPU_BIT = 0xA1008603,
    VPX_DEVICE_MEMORY_ACCESS_READ_ONLY_BIT = 0xA1008604,
    VPX_DEVICE_MEMORY_ACCESS_WRITE_ONLY_BIT = 0xA1008605,
    VPX_DEVICE_MEMORY_ACCESS_WRITE_READ_BIT = 0xA1008606,
} VpxDeviceMemoryFlagBits;
typedef VpxFlags VpxDeviceMemoryUsageFlags;
typedef VpxFlags VpxDeviceMemoryStorageFlags;
typedef VpxFlags VpxDeviceMemoryAccessFlags;

typedef struct VpxDeviceMemoryAllocateInfo {
    VpxUint64                                   size;
    VpxDeviceMemoryStorageFlags                 storage;
    VpxDeviceMemoryUsageFlags                   usage;
} VpxDeviceMemoryAllocateInfo;

typedef struct VpxDeviceMemoryMapInfo {
    VpxUint64                                   offset;
    VpxUint64                                   size;
    VpxDeviceMemoryAccessFlags                  access;
    void**                                      ppData;
} VpxDeviceMemoryMapInfo;

typedef struct VpxDeviceMemoryReadWriteInfo {
    VpxUint64                                   offset;
    VpxUint64                                   size;
    void**                                      ppData;
} VpxDeviceMemoryReadInfo, VpxDeviceMemoryWriteInfo;

//== <VPX DEFINE>: VpxDeviceMemory. ==//
VPXAPI_ATTR VpxResult VPXAPI_CALL VpxAllocateDeviceMemory(
    const VpxDeviceMemoryAllocateInfo*          pAllocateInfo,
    VpxDeviceMemory*                            pMemory
);

VPXAPI_ATTR VpxResult VPXAPI_CALL VpxBindDeviceMemory(
    VpxDeviceMemory                             memory
);

VPXAPI_ATTR VpxResult VPXAPI_CALL VpxMapDeviceMemory(
    const VpxDeviceMemoryMapInfo*               pMapInfo,
    VpxDeviceMemory                             memory
);

VPXAPI_ATTR VpxResult VPXAPI_CALL VpxUnmapDeviceMemory(
    VpxDeviceMemory                             memory
);

VPXAPI_ATTR VpxResult VPXAPI_CALL VpxReadDeviceMemory(
    const VpxDeviceMemoryReadInfo*              pReadInfo,
    VpxDeviceMemory                             memory
);

VPXAPI_ATTR VpxResult VPXAPI_CALL VpxWriteDeviceMemory(
    const VpxDeviceMemoryWriteInfo*             pWriteInfo,
    VpxDeviceMemory                             memory
);

VPXAPI_ATTR VpxResult VPXAPI_CALL VpxFreeDeviceMemory(
    VpxDeviceMemory                             memory
);

#ifdef __cplusplus
};
#endif

#endif /* _VPX_CORE_H */