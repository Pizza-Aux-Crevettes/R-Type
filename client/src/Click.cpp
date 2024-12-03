/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Implements the logic for handling user clicks in the client.
** Click events are used to trigger specific interactions or actions within the
*game's interface.
** Responsibility:
** - Detect mouse clicks.
** - Change touch for mouse clicks.
** Click.cpp
*/

#include "Click.hpp"

Click::Click() {}

Click::~Click() {}

bool Click::getUp() {
    return (_up);
}

bool Click::getRight() {
    return (_right);
}

bool Click::getLeft() {
    return (_left);
}

bool Click::getDown() {
    return (_down);
}

bool Click::getAttack() {
    return (_attack);
}

bool Click::getAutoFire() {
    return (_autoFire);
}

void Click::setUp() {}

void Click::setRight() {}

void Click::setLeft() {}

void Click::setDown() {}

void Click::setAttack() {}

void Click::setAutoFire() {}
