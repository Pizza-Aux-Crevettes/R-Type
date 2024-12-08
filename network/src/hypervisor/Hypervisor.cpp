/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Hypervisor.cpp
*/

#include "hypervisor/Hypervisor.hpp"

Hypervisor::Hypervisor(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("R-Type Server Hypervisor (by fōhz)");
    resize(800, 600);
}

Hypervisor::~Hypervisor() {}
