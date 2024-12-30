/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** OptionMenu.cpp
*/

#include "menu/OptionMenu.hpp"
#include "Client.hpp"

OptionMenu::OptionMenu() {}

OptionMenu::~OptionMenu() {}

void OptionMenu::displayOptionMenu(sf::RenderWindow &window) {
    
}

// Volumn music
int OptionMenu::getVolumnMusic() {
    return _volumnMusic;
}

void OptionMenu::setVolumnMusic(int new_volumn) {
    _volumnMusic = new_volumn;
    std::cout << "New volumn music" << _volumnMusic << std::endl;
}

// Volumn game
int OptionMenu::getVolumnGame() {
    return _volumnGame;
}

void OptionMenu::setVolumnGame(int new_volumn) {
    _volumnGame = new_volumn;
    std::cout << "New volumn game" << _volumnGame << std::endl;
}

// Resolution
int OptionMenu::getResolution() {
    return _resolution;
}

void OptionMenu::setResolution(int new_resolution) {
    _resolution = new_resolution;
    std::cout << "New resolution" << _resolution << std::endl;
}

// Adaptability text
bool OptionMenu::getAdaptabilityText() {
    return _adaptabilityText;
}

void OptionMenu::setAdaptabilityText() {
    _adaptabilityText = !_adaptabilityText;
    std::cout << "New adaptability state" << _adaptabilityText << std::endl;
}

// Element size
float OptionMenu::getElementSize() {
    return _elementSize;
}

void OptionMenu::setElementSize(float new_size) {
    _elementSize = new_size;
    std::cout << "New element size" << _elementSize << std::endl;
}

// Difficulty : false = normal && true = difficult
bool OptionMenu::getDifficulty() {
    return _difficulty;
}

void OptionMenu::setDifficulty() {
    _difficulty = !_difficulty;
    std::cout << "New difficulty state" << _difficulty << std::endl;
}

// Control : false = keyboard && true = controller
bool OptionMenu::getControl() {
    return _control;
}

void OptionMenu::setControl() {
    _control = !_control;
    std::cout << "New control state" << _control << std::endl;
}

// Contrast : false = disabled && true = enabled
bool OptionMenu::getContrast() {
    return _constrast;
}

void OptionMenu::setContrast() {
    _constrast = !_constrast;
    std::cout << "New contrast state" << _constrast << std::endl;
}