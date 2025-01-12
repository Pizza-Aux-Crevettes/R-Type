/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** System.cpp
*/

#include "System.hpp"
#include <components/Shape.hpp>
#include <components/Texture.hpp>

void GameEngine::System::shapeSystem(sf::RenderWindow& window, GameEngine::Entity& entity) {
    if (entity.hasComponent<Shape>() && entity.hasComponent<Position>()) {
        auto& shapeComp = entity.getComponent<Shape>();
        if (shapeComp.getShapeType() == Rectangle) {
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
                    textureComp.getTexture().loadFromFile(
                        textureComp.getTexturePath());
                    textureComp.setIsLoaded(true);
                    shapeComp.getRect().setTexture(&textureComp.getTexture());
                }
                shapeComp.setIsLoaded(true);
            }
            window.draw(shapeComp.getRect());
        }
        if (shapeComp.getShapeType() == Circle) {
            if (!shapeComp.getIsLoaded()) {
                sf::CircleShape circle;
                circle.setRadius(shapeComp.getRadius());
                setPosition(entity, circle);
                setColor(entity, circle);
                shapeComp.setShape(circle);
                if (entity.hasComponent<Texture>() &&
                    !entity.getComponent<Texture>().getIsLoaded()) {
                    auto& textureComp = entity.getComponent<Texture>();
                    textureComp.getTexture().loadFromFile(
                        textureComp.getTexturePath());
                    textureComp.setIsLoaded(true);
                    shapeComp.getCircle().setTexture(&textureComp.getTexture());
                }
                shapeComp.setIsLoaded(true);
            }
            window.draw(shapeComp.getCircle());
        }
    }
}
