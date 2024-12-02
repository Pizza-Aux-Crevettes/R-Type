/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Animation.hpp
*/

#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

class Animation {
  public:
    Animation(int currentFrame = 0, float frameDuration = 0.0f,
              float elapsedTime = 0.0f);
    ~Animation();
    int getCurrentFrame() const;
    void setCurrentFrame(int currentFrame);
    float getFrameDuration() const;
    void setFrameDuration(float frameDuration);
    float getElapsedTime() const;
    void setElapsedTime(float elapsedTime);

  private:
    int _currentFrame;
    float _frameDuration;
    float _elapsedTime;
};

#endif /* ANIMATION_HPP_ */
