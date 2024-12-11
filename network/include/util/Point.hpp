/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Point.hpp
*/

/**
 * @file Point.hpp
 * @brief Represents a 2D point with x and y coordinates.
 */

#pragma once

/**
 * @class Point
 * @brief A simple class for representing a 2D point in Cartesian coordinates.
 *
 * This class provides methods to get and set the x and y coordinates of a
 * point.
 */
class Point {
  public:
    /**
     * @brief Constructs a Point object with specified coordinates.
     *
     * @param x The x-coordinate of the point. Defaults to 0.
     * @param y The y-coordinate of the point. Defaults to 0.
     */
    Point(double x = 0, double y = 0);

    /**
     * @brief Gets the x-coordinate of the point.
     *
     * @return The x-coordinate as a double.
     */
    double getX() const;

    /**
     * @brief Gets the y-coordinate of the point.
     *
     * @return The y-coordinate as a double.
     */
    double getY() const;

    /**
     * @brief Sets the x-coordinate of the point.
     *
     * @param x The new x-coordinate.
     */
    void setX(double x);

    /**
     * @brief Sets the y-coordinate of the point.
     *
     * @param y The new y-coordinate.
     */
    void setY(double y);

  private:
    double _x; ///< The x-coordinate of the point.
    double _y; ///< The y-coordinate of the point.
};
