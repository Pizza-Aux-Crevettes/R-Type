/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** OptionMenu.hpp
*/

#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class OptionMenu {
  private:
    int _volumnMusic;
    int _volumnGame;
    int _resolution;
    bool _adaptabilityText;
    float _elementSize;
    bool _difficulty;
    bool _control;
    bool _constrast;

  public:
    OptionMenu();
    ~OptionMenu();
    void displayOptionMenu(sf::RenderWindow &);
    int getVolumnMusic();
    void setVolumnMusic(int);
    int getVolumnGame();
    void setVolumnGame(int);
    int getResolution();
    void setResolution(int);
    bool getAdaptabilityText();
    void setAdaptabilityText();
    float getElementSize();
    void setElementSize(float);
    bool getDifficulty();
    void setDifficulty();
    bool getControl();
    void setControl();
    bool getContrast();
    void setContrast();
};