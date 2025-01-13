/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** ShapeSystem.cpp
*/

#include <components/Shape.hpp>
#include <components/Texture.hpp>
#include "System.hpp"

void GameEngine::System::loadRectangle(GameEngine::Entity& entity,
                                       auto& shapeComp) {
    if (!shapeComp.getIsLoaded()) {
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(shapeComp.getSize().first,
                                       shapeComp.getSize().second));
        setPosition(entity, rectangle);
        setColor(entity, rectangle);
        shapeComp.setShape(rectangle);
        if (entity.hasComponent<Texture>() &&
            !entity.getComponent<Texture>().getIsLoaded()) {
            auto& textureComp = entity.getComponent<Texture>();
            textureComp.getTexture().loadFromFile(textureComp.getTexturePath());
            if (textureComp.getTextureRect().size() == 4) {
                const auto& textureRect = textureComp.getTextureRect();
                shapeComp.getRect().setTextureRect(
                    sf::IntRect(textureRect[0], textureRect[1], textureRect[2],
                                textureRect[3]));
            }
            shapeComp.getRect().setTexture(&textureComp.getTexture());
            textureComp.setIsLoaded(true);
        }
        shapeComp.setIsLoaded(true);
    }
}

void GameEngine::System::loadCircle(GameEngine::Entity& entity,
                                    auto& shapeComp) {
    if (!shapeComp.getIsLoaded()) {
        sf::CircleShape circle;
        circle.setRadius(shapeComp.getRadius());
        setPosition(entity, circle);
        setColor(entity, circle);
        shapeComp.setShape(circle);
        if (entity.hasComponent<Texture>() &&
            !entity.getComponent<Texture>().getIsLoaded()) {
            auto& textureComp = entity.getComponent<Texture>();
            textureComp.getTexture().loadFromFile(textureComp.getTexturePath());
            if (textureComp.getTextureRect().size() == 4) {
                const auto& textureRect = textureComp.getTextureRect();
                shapeComp.getCircle().setTextureRect(
                    sf::IntRect(textureRect[0], textureRect[1], textureRect[2],
                                textureRect[3]));
            }
            shapeComp.getCircle().setTexture(&textureComp.getTexture());
            textureComp.setIsLoaded(true);
        }
        shapeComp.setIsLoaded(true);
    }
}

void GameEngine::System::shapeSystem(sf::RenderWindow& window,
                                     GameEngine::Entity& entity) {
    if (entity.hasComponent<Shape>() && entity.hasComponent<Position>()) {
        auto& shapeComp = entity.getComponent<Shape>();
        if (shapeComp.getShapeType() == Rectangle) {
            loadRectangle(entity, shapeComp);
            window.draw(shapeComp.getRect());
        }
        if (shapeComp.getShapeType() == Circle) {
            loadCircle(entity, shapeComp);
            window.draw(shapeComp.getCircle());
        }
    }
}
