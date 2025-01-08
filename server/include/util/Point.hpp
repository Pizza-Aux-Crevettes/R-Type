/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Point.hpp
*/

#pragma once

class Point {
  public:
    explicit Point(double x = 0, double y = 0);

    [[nodiscard]] Point getPoint() const;
    [[nodiscard]] double getX() const;
    [[nodiscard]] double getY() const;
    void setX(double x);
    void setY(double y);
    void setPoint(double x, double y);

  private:
    double _x;
    double _y;
};
