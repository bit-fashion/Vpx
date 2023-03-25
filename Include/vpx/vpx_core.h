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

typedef unsigned int  VpxUint;
typedef uint32_t      VpxUint32;
typedef uint64_t      VpxUint64;
typedef float         VpxFloat;
typedef VpxUint32     VpxFlags;
typedef VpxUint64     VpxPointer;
typedef VpxUint32     VpxBool32;
#define VPX_TRUE      (0U)
#define VPX_FALSE     (1U)

// <VPX DEFINE>: Define handles.
VPX_DEFINE_HANDLE(VpxBuffer)
VPX_DEFINE_HANDLE(VpxVertexBuffer)
VPX_DEFINE_HANDLE(VpxIndexBuffer)
VPX_DEFINE_HANDLE(VpxTexture)
VPX_DEFINE_HANDLE(VpxShaderModule)
VPX_DEFINE_HANDLE(VpxPipeline)
VPX_DEFINE_HANDLE(VpxFramebuffer)
VPX_DEFINE_HANDLE(VpxRenderPass)
VPX_DEFINE_HANDLE(VpxCommandBuffer)
// VPX_DEFINE_HANDLE(VpxAllocator)

#define VPX_WHOLE_SIZE (~0ULL)

#ifndef VPX_NULL_HANDLE
#  define VPX_NULL_HANDLE (NULL)
#endif

// <VPX DEFINE>: The following defines the enum.
typedef enum VpxDefineSupportRenderAPIBits {
    // VPX_RENDER_API_OPENGL = 0,
    VPX_RENDER_API_VULKAN = 1,
} VpxDefineSupportRenderAPIBits;
typedef VpxFlags VpxDefineSupportRenderAPI;

typedef enum VpxResult {
    VPX_SUCCESS = 0,
    VPX_ERROR = 1,
    VPX_NO_SUPPORT_CURRENT_API_DEVICE = 2,
} VpxResult;

typedef enum VpxBufferFlagBits {
    VPX_BUFFER_USAGE_VERTEX_BUFFER_BIT = 0xA1008600,
    VPX_BUFFER_USAGE_INDEX_BUFFER_BIT = 0xA1008601,
    VPX_BUFFER_STORAGE_IN_GPU_BIT = 0xA1008602,
    VPX_BUFFER_STORAGE_IN_CPU_BIT = 0xA1008603,
    VPX_BUFFER_ACCESS_READ_BIT = 0xA1008604,
    VPX_BUFFER_ACCESS_WRITE_BIT = 0xA1008605,
    VPX_BUFFER_ACCESS_ALL_BIT = 0xA1008606,
} VpxBufferFlagBits;
typedef VpxFlags VpxBufferUsageFlags;
typedef VpxFlags VpxBufferStorageFlags;
typedef VpxFlags VpxBufferAccessFlags;

typedef enum VpxPipelineFlagBits {
    VPX_PIPELINE_BIND_POINT_GRAPHICS_BIT = 0xA1008700,
} VpxPipelineFlagBits;
typedef VpxFlags VpxPipelineBindPointFlags;

//== <VPX DEFINE FUNCTION>: Initialize Vpx. ==//
VPXAPI_ATTR VpxResult VPXAPI_CALL VpxInitializeEnableRenderAPI(
  VpxDefineSupportRenderAPI                 api
);

//== <VPX DEFINE FUNCTION>: VpxBuffer. ==//
VPXAPI_ATTR VpxResult VPXAPI_CALL VpxAllocateBuffer(
  VpxUint64                                 size,
  VpxBufferUsageFlags                       usageFlags,
  VpxBufferStorageFlags                     storageFlags,
  VpxBuffer*                                pBuffer
);

VPXAPI_ATTR VpxResult VPXAPI_CALL VpxBindBuffer(
  VpxBuffer                                 buffer
);

VPXAPI_ATTR VpxResult VPXAPI_CALL VpxMapBuffer(
  VpxUint64                                 offset,
  VpxUint64                                 size,
  VpxBufferAccessFlags                      accessFlags,
  VpxBuffer                                 buffer
);

VPXAPI_ATTR VpxResult VPXAPI_CALL VpxUnmapBuffer(
  VpxBuffer                                 buffer
);

VPXAPI_ATTR VpxResult VPXAPI_CALL VpxReadBuffer(
  VpxUint64                                 offset,
  VpxUint64                                 size,
  void**                                    ppData,
  VpxBuffer                                 buffer
);

VPXAPI_ATTR VpxResult VPXAPI_CALL VpxWriteBuffer(
  VpxUint64                                 offset,
  VpxUint64                                 size,
  void**                                    ppData,
  VpxBuffer                                 buffer
);

VPXAPI_ATTR VpxResult VPXAPI_CALL VpxFreeBuffer(
  VpxBuffer                                 buffer
);

//== <VPX DEFINE FUNCTION>: VpxCmd. ==//
VPXAPI_ATTR VpxResult VPXAPI_CALL VpxBeginCommandBuffer(
  VpxCommandBuffer                          commandBuffer
);

VPXAPI_ATTR VpxResult VPXAPI_CALL VpxEndCommandBuffer(
  VpxCommandBuffer                          commandBuffer
);

VPXAPI_ATTR VpxResult VPXAPI_CALL VpxCmdBindPipeline(
  VpxCommandBuffer                          commandBuffer,
  VpxPipelineBindPointFlags                 bindPoint,
  VpxPipeline                               pipeline
);

VPXAPI_ATTR VpxResult VPXAPI_CALL VpxCmdBindVertexBuffer(
  VpxCommandBuffer                          commandBuffer,
  VpxUint32                                 firstBinding,
  VpxUint32                                 bindingCount,
  VpxVertexBuffer                           buffer,
  VpxUint64                                 offset
);

VPXAPI_ATTR VpxResult VPXAPI_CALL VpxCmdDraw(
  VpxCommandBuffer                          commandBuffer,
  VpxUint32                                 firstVertex,
  VpxUint32                                 vertexCount
);

#ifdef __cplusplus
};
#endif

#endif /* _VPX_CORE_H */