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

Link::Link(int id) : _id(id) {}

int Link::getId() const {
    return _id;
}

void Link::setId(int id) {
    _id = id;
}

Link::~Link() {}