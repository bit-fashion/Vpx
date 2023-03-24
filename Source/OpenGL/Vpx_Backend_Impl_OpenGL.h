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
#ifndef SP2R_SP2R_BACKEND_IMPL_OPENGL_H
#define SP2R_SP2R_BACKEND_IMPL_OPENGL_H

#include "AirGraph/vpx.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef struct SportsEnumMap {
    uint32_t sports;
    uint32_t gl;
} SportsEnumMap;

static struct SportsEnumMap static_sports_enum_map[] = {
        { AIR_DEVICE_MEMORY_USAGE_VERTEX_BUFFER_BIT, GL_ARRAY_BUFFER },
        { AIR_DEVICE_MEMORY_USAGE_INDEX_BUFFER_BIT, GL_ELEMENT_ARRAY_BUFFER },

        { AIR_DEVICE_MEMORY_ACCESS_READ_ONLY_BIT, GL_READ_ONLY },
        { AIR_DEVICE_MEMORY_ACCESS_WRITE_ONLY_BIT, GL_WRITE_ONLY },
        { AIR_DEVICE_MEMORY_ACCESS_READ_WRITE_BIT, GL_READ_WRITE },
};

__attribute__((always_inline))
inline static uint32_t static_find_sports_enum_map(uint32_t sports_enum_value)
{
    int array_count = sizeof(static_sports_enum_map) / sizeof(SportsEnumMap);
    for (int i = 0; i < array_count; i++) {
        struct SportsEnumMap _map;
        _map = static_sports_enum_map[i];

        if (_map.sports == sports_enum_value)
            return _map.gl;
    }

    return (0);
}

#define GL_BIT_MAP(eval) static_find_sports_enum_map(eval)

struct AirDeviceMemory_T {
    uint64_t                size;
    int                     usage;
    unsigned int            bufid;
};

struct AirVertexBuffer_T {
    unsigned int            vao;
    AirDeviceMemory         buf;
};

#endif /* SP2R_SP2R_BACKEND_IMPL_OPENGL_H */
