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

/**
 * @brief Constructor for the Animation component.
 *
 * This constructor initializes the Animation component with the specified frame
 * details.
 *
 * @param currentFrame The current frame of the animation.
 * @param frameDuration The duration each frame should be displayed.
 * @param elapsedTime The elapsed time since the animation started.
 */
Animation::Animation(int currentFrame, float frameDuration, float elapsedTime)
    : _currentFrame(currentFrame), _frameDuration(frameDuration),
      _elapsedTime(elapsedTime) {}

/**
 * @brief Destructor for the Animation component.
 *
 * This destructor cleans up any resources used by the Animation component.
 */
Animation::~Animation() {}

/**
 * @brief Get the current frame of the Animation component.
 *
 * This function retrieves the current frame of the animation.
 *
 * @return The current frame index of the animation.
 */
int Animation::getCurrentFrame() const {
    return this->_currentFrame;
}

/**
 * @brief Set the current frame of the Animation component.
 *
 * This function sets the current frame index of the animation.
 *
 * @param currentFrame The new current frame index.
 */
void Animation::setCurrentFrame(int currentFrame) {
    this->_currentFrame = currentFrame;
}

/**
 * @brief Get the frame duration of the Animation component.
 *
 * This function retrieves the duration that each frame is displayed.
 *
 * @return The frame duration in seconds.
 */
float Animation::getFrameDuration() const {
    return this->_frameDuration;
}

/**
 * @brief Set the frame duration of the Animation component.
 *
 * This function sets the duration that each frame should be displayed.
 *
 * @param frameDuration The new frame duration in seconds.
 */
void Animation::setFrameDuration(float frameDuration) {
    this->_frameDuration = frameDuration;
}

/**
 * @brief Get the elapsed time of the Animation component.
 *
 * This function retrieves the time that has elapsed since the animation
 * started.
 *
 * @return The elapsed time in seconds.
 */
float Animation::getElapsedTime() const {
    return this->_elapsedTime;
}

/**
 * @brief Set the elapsed time of the Animation component.
 *
 * This function sets the elapsed time since the animation started.
 *
 * @param elapsedTime The new elapsed time in seconds.
 */
void Animation::setElapsedTime(float elapsedTime) {
    this->_elapsedTime = elapsedTime;
}

/**
 * @brief Display the Animation component information.
 *
 * This function displays a message indicating that the Animation component is
 * being displayed.
 */
void Animation::display() const {
    std::cout << "Animation component displayed!" << std::endl;
}