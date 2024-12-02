/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Rigidbody.hpp
*/

#ifndef RIGIDBODY_HPP_
#define RIGIDBODY_HPP_

class Rigidbody {
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

  protected:
  private:
    float _mass;
    float _drag;
    float _gravityScale;
    float _forceX;
    float _forceY;
};

#endif /* !RIGIDBODY_HPP_ */
