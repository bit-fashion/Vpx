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

#ifndef VPX_CORE_H
#define VPX_CORE_H 1

#include <stdio.h>
#include <stdint.h>

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

typedef float         VpxFloat32;
typedef uint32_t      VpxBool32;
typedef uint32_t      VpxFlags;
typedef uint64_t      VpxPointer;
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
typedef enum VpxResult {
    VPX_SUCCESS = 0,
} VpxResult;

typedef enum VpxDefineRenderAPI {
    VPX_RENDER_API_OPENGL = 0,
    VPX_RENDER_API_VULKAN = 1,
} VpxDefineRenderAPI;

//== <VPX DEFINE>: The following defines the functions. ==//
VPXAPI_ATTR

#ifdef __cplusplus
};
#endif

#endif /* VPX_CORE_H */