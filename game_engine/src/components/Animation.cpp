/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Animation.cpp
**
** The Animation class represents an animation for an entity in the game.
** It tracks the current frame, frame duration, and elapsed time for animation
*playback.
** The constructor allows initializing the animation with the specified values
*for each parameter.
*/

#include "components/Animation.hpp"
#include "iostream"

Animation::Animation(int currentFrame, float frameDuration, float elapsedTime)
    : _currentFrame(currentFrame), _frameDuration(frameDuration),
      _elapsedTime(elapsedTime) {}

Animation::~Animation() {}

int Animation::getCurrentFrame() const {
    return this->_currentFrame;
}

void Animation::setCurrentFrame(int currentFrame) {
    this->_currentFrame = currentFrame;
}

float Animation::getFrameDuration() const {
    return this->_frameDuration;
}

void Animation::setFrameDuration(float frameDuration) {
    this->_frameDuration = frameDuration;
}

float Animation::getElapsedTime() const {
    return this->_elapsedTime;
}

void Animation::setElapsedTime(float elapsedTime) {
    this->_elapsedTime = elapsedTime;
}

void Animation::display() const {
    std::cout << "Animation component displayed!" << std::endl;
}