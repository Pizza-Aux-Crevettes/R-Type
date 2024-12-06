/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Point
*/

#pragma once

class Point {
  public:
    Point(double x = 0, double y = 0);

    double getX() const;
    double getY() const;

    void setX(double x);
    void setY(double y);

  private:
    double _x;
    double _y;
};
