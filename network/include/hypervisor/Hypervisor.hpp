/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Hypervisor.hpp
*/

#pragma once

#include <QMainWindow>

class Hypervisor : public QMainWindow {
    Q_OBJECT

  public:
    explicit Hypervisor(QWidget* parent = nullptr);
    ~Hypervisor();
};
