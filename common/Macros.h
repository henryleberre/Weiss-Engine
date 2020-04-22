#pragma once

#define CHECK_BIT(var,pos) ((var) & ( 1 << (pos)))

#define VK_FAILED(vkResult) ((vkResult) != VK_SUCCESS)