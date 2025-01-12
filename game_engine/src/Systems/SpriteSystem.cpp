/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** SpriteSystem.cpp
*/

#include <components/Sprite.hpp>
#include "System.hpp"

void GameEngine::System::loadSprite(GameEngine::Entity& entity,
                                    auto& spriteComp, auto& textureComp) {
    if (!spriteComp.getIsLoaded()) {
        if (textureComp.getTextureRect().size() == 4) {
            const auto& textureRect = textureComp.getTextureRect();
            spriteComp.getSprite().setTextureRect(
                sf::IntRect(textureRect[0], textureRect[1], textureRect[2],
                            textureRect[3]));
        }
        spriteComp.getSprite().setTexture(textureComp.getTexture());
        setPosition(entity, spriteComp.getSprite());
        if (spriteComp.getSize().first != -1 &&
            spriteComp.getSize().second != -1) {
            spriteComp.getSprite().setScale(spriteComp.getSize().first,
                                            spriteComp.getSize().second);
        }
        setColor(entity, spriteComp.getSprite());
        spriteComp.setIsLoaded(true);
    }
}

void GameEngine::System::spriteSystem(sf::RenderWindow& window,
                                      GameEngine::Entity& entity) {
    if (entity.hasComponent<Sprite>() && entity.hasComponent<Texture>()) {
        auto& spriteComp = entity.getComponent<Sprite>();
        auto& textureComp = entity.getComponent<Texture>();
        if (!textureComp.getIsLoaded()) {
            textureComp.getTexture().loadFromFile(textureComp.getTexturePath());
            textureComp.setIsLoaded(true);
        }
        loadSprite(entity, spriteComp, textureComp);
        if (entity.getComponent<Position>().getPositions().size() > 1) {
            auto& positionComp = entity.getComponent<Position>();
            for (auto& position : positionComp.getPositions()) {
                spriteComp.getSprite().setPosition(position.first,
                                                   position.second);
                window.draw(spriteComp.getSprite());
            }
        } else {
            window.draw(spriteComp.getSprite());
        }
    }
}
