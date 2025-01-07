/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Link.cpp
**
** The Link class manages a connection between two game entities.
** It holds an identifier used to reference the link and provides
** methods to retrieve and update the link's ID. The constructor
** initializes the connection with a given ID, and the destructor
** ensures proper cleanup when the link is no longer in use.
*/

#include "components/Link.hpp"
#include <iostream>

Link::Link(const int id) : _id(id) {}

int Link::getId() const {
    return this->_id;
}

void Link::setId(const int id) {
    this->_id = id;
}

void Link::display() const {
    std::cout << "Link component displayed!" << std::endl;
}

Link::~Link() {}