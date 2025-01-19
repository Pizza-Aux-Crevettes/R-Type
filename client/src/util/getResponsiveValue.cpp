/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** This file implements the GetResponsiveValue class, which provides methods
** to adjust the position and size of elements in a responsive layout.
** getResponsiveValue.cpp
*/

#include "util/getResponsiveValue.hpp"

float GetResponsiveValue::getResponsivePosX(int baseWidth, int currentWidth,
                                            int originalPosX) {
    return static_cast<int>(originalPosX *
                            (static_cast<float>(currentWidth) / baseWidth));
}

float GetResponsiveValue::getResponsivePosY(int baseHeight, int currentHeight,
                                            int originalPosY) {
    return static_cast<int>(originalPosY *
                            (static_cast<float>(currentHeight) / baseHeight));
}

float GetResponsiveValue::getResponsiveSizeX(int baseWidth, int currentWidth,
                                             int originalWidth) {
    return originalWidth * (static_cast<float>(currentWidth) / baseWidth);
}

float GetResponsiveValue::getResponsiveSizeY(int baseHeight, int currentHeight,
                                             int originalHeight) {
    return originalHeight * (static_cast<float>(currentHeight) / baseHeight);
}