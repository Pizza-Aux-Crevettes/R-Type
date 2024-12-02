/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Checkpoint.cpp
*/

#include "Checkpoint.hpp"

Point Checkpoint::getPosition() const {
    return position;
}

void Checkpoint::setPosition(const Point &pos) {
    position = pos;
}
