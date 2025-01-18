/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** WinMenu
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <System.hpp>
#include <iostream>
#include <functional>


class WinMenu {
    public:
        WinMenu();
        ~WinMenu();
        static WinMenu& get();

        GameEngine::Entity createEntityText(int id, const std::string text, const std::vector<std::pair<float, float>> position, unsigned int fontSize);
        GameEngine::Entity createEntityButton(int id, std::string title, std::string font, int fontSize, std::vector<std::pair<float, float>> position, std::function<void()> callback);
        GameEngine::Entity createEntitySprite(int id, const std::pair<float, float> size, std::string texture, std::vector<int> textureRect, const std::vector<std::pair<float, float>> position);
        GameEngine::Entity createEntityRect(
            int id, const std::pair<int, int> size,
            const std::vector<std::pair<float, float>> position, sf::Color color,
            std::function<void()> callback);
        void isClickedExit(sf::RenderWindow& window);
        void displayWnMenu(sf::RenderWindow& window, GameEngine::System system);
    protected:
    private:
        std::map<int, GameEngine::Entity> _entitiesWinMenu;
        bool _entitiesInitialized = false;

};

