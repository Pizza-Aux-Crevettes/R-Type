/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Point.hpp
*/

#pragma once

#include <cmath>
#include <iostream>

class Point {
  public:
    explicit Point(double x = 0, double y = 0);

    double getX() const;
    void setX(double x);
    double getY() const;
    void setY(double y);
    Point getPoint() const;
    void setPoint(double x, double y);
    void normalize();

  private:
    double _x;
    double _y;
};
