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
#include "Vpx_Backend_Impl_Vulkan.h"
#include <string.h>
#include <malloc.h>

// is vk success.
#define _ivs(ret) ( ret != VK_SUCCESS )

static struct vulkan_application_context *va_context;

VPXAPI_ATTR VpxResult VPXAPI_CALL VpxInitializeEnableRenderAPI(
  VpxDefineSupportRenderAPI                 api
)
{
    va_context = malloc(sizeof(struct vulkan_application_context));
    memset(va_context, 0, sizeof(struct vulkan_application_context));

    /* instance */
    VkApplicationInfo applicationInfo = {};
    applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    applicationInfo.pApplicationName = "VPX-VULKAN";
    applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    applicationInfo.pEngineName = "No Engine";
    applicationInfo.engineVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo instanceCreateInfo = {};
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pApplicationInfo = &applicationInfo;

    VpxUint glfwExtensionCount;
    const char **glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    instanceCreateInfo.enabledExtensionCount = glfwExtensionCount;
    instanceCreateInfo.ppEnabledExtensionNames = glfwExtensions;
    if (_ivs(vkCreateInstance(&instanceCreateInfo, NULL, &va_context->instance)))
        return VPX_ERROR;

    /* device */
    VpxUint32 deviceCount = 0;
    vkEnumeratePhysicalDevices(va_context->instance, &deviceCount, VK_NULL_HANDLE);
    if (deviceCount == 0)
        return VPX_NO_SUPPORT_CURRENT_API_DEVICE;

    VkPhysicalDevice physicalDevices[deviceCount];
    vkEnumeratePhysicalDevices(va_context->instance, &deviceCount, physicalDevices);
    va_context->physicalDevice = physicalDevices[0];

    // graphics queue family
    VpxUint32 queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(va_context->physicalDevice, &queueFamilyCount, VK_NULL_HANDLE);
    VkQueueFamilyProperties queueFamilyProperties[queueFamilyCount];
    vkGetPhysicalDeviceQueueFamilyProperties(va_context->physicalDevice, &queueFamilyCount, queueFamilyProperties);

    for (int i = 0; i < queueFamilyCount; i++) {
        VkQueueFamilyProperties queueFamily;
        queueFamily = queueFamilyProperties[i];
        if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            va_context->graphicsFamily = i;
            if (va_context->graphicsFamily >= 0)
                break;
        }
    }

    // logic device
    VkDeviceQueueCreateInfo deviceQueueCreateInfo = {};
    deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    deviceQueueCreateInfo.queueFamilyIndex = va_context->graphicsFamily;
    deviceQueueCreateInfo.queueCount = 1;
    float queuePriority = 1.0f;
    deviceQueueCreateInfo.pQueuePriorities = &queuePriority;

    VkDeviceCreateInfo deviceCreateInfo= {};
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;
    deviceCreateInfo.queueCreateInfoCount = 1;

    VkPhysicalDeviceFeatures deviceFeatures = {};
    deviceCreateInfo.pEnabledFeatures = &deviceFeatures;

    return VPX_SUCCESS;
}