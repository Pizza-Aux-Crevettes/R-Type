/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Rigidbody.hpp
*/

#pragma once

class Rigidbody : public Component {
  public:
    Rigidbody(float mass, float drag, float gravityScale, float forceX,
              float forceY);
    ~Rigidbody();
    float getMass() const;
    void setMass(float mass);
    float getDrag() const;
    void setDrag(float drag);
    float getGravityScale() const;
    void setGravityScale(float gravityScale);
    float getForceX() const;
    void setForceX(float forceX);
    float getForceY() const;
    void setForceY(float forceY);
    void display() const override;

  protected:
  private:
    float _mass;
    float _drag;
    float _gravityScale;
    float _forceX;
    float _forceY;
};
