/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** TextSystem.cpp
*/

#include <components/Text.hpp>
#include "System.hpp"

void GameEngine::System::loadText(GameEngine::Entity& entity, auto& textComp) {
    if (!textComp.getIsLoaded()) {
        textComp.getFont().loadFromFile(textComp.getFontFile());
        textComp.getText().setFont(textComp.getFont());
        textComp.getText().setString(textComp.getString());
        textComp.getText().setCharacterSize(textComp.getCharacterSize());
        setPosition(entity, textComp.getText());
        setColor(entity, textComp.getText());
        textComp.setIsLoaded(true);
    } else {
        updateText(entity, textComp.getString());
    }
}

void GameEngine::System::textSystem(sf::RenderWindow& window,
                                    GameEngine::Entity& entity) {
    if (entity.hasComponent<Text>() && entity.hasComponent<Position>()) {
        auto& textComp = entity.getComponent<Text>();
        loadText(entity, textComp);
        if (entity.getComponent<Position>().getPositions().size() > 1) {
            auto& positionComp = entity.getComponent<Position>();
            for (auto& position : positionComp.getPositions()) {
                textComp.getText().setPosition(position.first, position.second);
                window.draw(textComp.getText());
            }
        } else {
            window.draw(textComp.getText());
        }
    }
}