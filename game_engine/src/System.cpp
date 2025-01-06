/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** System.cpp
*/

#include "System.hpp"
#include <components/Color.hpp>
#include <components/Position.hpp>
#include <components/Sprite.hpp>
#include <components/Text.hpp>
#include <components/Texture.hpp>
#include <components/OptionButton.hpp>
#include <components/Slider.hpp>
#include <iostream>

GameEngine::System::System() {}

static void spriteSystem(sf::RenderWindow& window, GameEngine::Entity& entity) {
    if (entity.hasComponent<Sprite>() && entity.hasComponent<Texture>() &&
        entity.hasComponent<Position>()) {
        auto& spriteComp = entity.getComponent<Sprite>();
        auto& textureComp = entity.getComponent<Texture>();
        auto& positionComp = entity.getComponent<Position>();

        if (!textureComp.getIsLoaded()) {
            textureComp.getTexture().loadFromFile(textureComp.getTexturePath());
            textureComp.setIsLoaded(true);
        }
        if (!spriteComp.getIsLoaded()) {
            if (textureComp.getTextureRect().size() == 4) {
                const auto textureRect = textureComp.getTextureRect();
                spriteComp.getSprite().setTextureRect(
                    sf::IntRect(textureRect[0], textureRect[1], textureRect[2],
                                textureRect[3]));
            }
            spriteComp.getSprite().setTexture(textureComp.getTexture());
            spriteComp.getSprite().setPosition(positionComp.getPositionX(),
                                               positionComp.getPositionY());
            if (spriteComp.getSize().first != -1 &&
                spriteComp.getSize().second != -1) {
                spriteComp.getSprite().setScale(spriteComp.getSize().first,
                                                spriteComp.getSize().second);
            }
            if (entity.hasComponent<Color>() &&
                entity.getComponent<Color>().getColor().size() == 4) {
                auto& colorComp = entity.getComponent<Color>();
                const auto color = colorComp.getColor();
                spriteComp.getSprite().setColor(
                    sf::Color(color[0], color[1], color[2], color[3]));
            }
            spriteComp.setIsLoaded(true);
        }
        window.draw(spriteComp.getSprite());
    }
}

static void textSystem(sf::RenderWindow& window, GameEngine::Entity& entity) {
    if (entity.hasComponent<Text>() && entity.hasComponent<Position>()) {
        auto& textComp = entity.getComponent<Text>();
        auto& positionComp = entity.getComponent<Position>();

        if (!textComp.getIsLoaded()) {
            textComp.getFont().loadFromFile(textComp.getFontFile());
            textComp.getText().setFont(textComp.getFont());
            textComp.getText().setString(textComp.getString());
            textComp.getText().setCharacterSize(textComp.getCharacterSize());
            textComp.getText().setPosition(positionComp.getPositionX(),
                                           positionComp.getPositionY());
            if (entity.hasComponent<Color>() &&
                entity.getComponent<Color>().getColor().size() == 4) {
                auto& colorComp = entity.getComponent<Color>();
                const auto color = colorComp.getColor();
                textComp.getText().setColor(
                    sf::Color(color[0], color[1], color[2], color[3]));
            }
            textComp.setIsLoaded(true);
        }
        window.draw(textComp.getText());
    }
}

static void optionButtonSystem(sf::RenderWindow& window, GameEngine::Entity& entity) {
    if (entity.hasComponent<OptionButton>() && entity.hasComponent<Position>()) {
        auto& buttonComp = entity.getComponent<OptionButton>();
        auto& positionComp = entity.getComponent<Position>();

        if (!buttonComp.getIsLoaded()) {
            sf::RectangleShape buttonShape;
            buttonShape.setSize({static_cast<float>(buttonComp.getSize().first), 
                                 static_cast<float>(buttonComp.getSize().second)});
            buttonShape.setPosition(positionComp.getPositionX(), positionComp.getPositionY());
            buttonShape.setOutlineThickness(2);
            if (entity.hasComponent<Color>() &&
                entity.getComponent<Color>().getColor().size() == 4) {
                auto& colorComp = entity.getComponent<Color>();
                const auto color = colorComp.getColor();
                buttonComp.getShape().setOutlineColor(
                    sf::Color(color[0], color[1], color[2], color[3]));
                buttonShape.setFillColor(sf::Color::Transparent);
            }
            buttonComp.setShape(buttonShape);
            buttonComp.setIsLoaded();
        }

        static std::map<GameEngine::Entity*, bool> wasPressedMap;

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::FloatRect buttonBounds = buttonComp.getShape().getGlobalBounds();

        if (buttonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

            if (isPressed && !wasPressedMap[&entity]) {
                buttonComp.setChecked();
                buttonComp.executeCallback();
                wasPressedMap[&entity] = true;
            } else if (!isPressed) {
                wasPressedMap[&entity] = false;
            }
        }

        if (buttonComp.getChecked()) {
            buttonComp.getShape().setFillColor(sf::Color::White);
        } else {
            buttonComp.getShape().setFillColor(sf::Color::Transparent);
        }

        window.draw(buttonComp.getShape());
    }
}

static void sliderSystem(sf::RenderWindow& window, GameEngine::Entity& entity) {
    if (entity.hasComponent<Slider>() && entity.hasComponent<Position>()) {
        auto& sliderComp = entity.getComponent<Slider>();
        auto& positionComp = entity.getComponent<Position>();

        if (!sliderComp.getIsLoaded()) {
            sf::RectangleShape barShape;
            barShape.setPosition(positionComp.getPositionX(), positionComp.getPositionY());
            barShape.setSize({static_cast<float>(sliderComp.getSize().first), static_cast<float>(sliderComp.getSize().second)});
            barShape.setOutlineThickness(5);
            barShape.setOutlineColor(sf::Color::Transparent);

            sf::CircleShape cursorShape;
            cursorShape.setPosition(positionComp.getPositionX(), positionComp.getPositionY() - 7);
            cursorShape.setRadius(9.f);

            sliderComp.setBarShape(barShape);
            sliderComp.setCursorShape(cursorShape);
            if (entity.hasComponent<Color>() &&
                entity.getComponent<Color>().getColor().size() == 4) {
                auto& colorComp = entity.getComponent<Color>();
                const auto color = colorComp.getColor();
                sliderComp.getBarShape().setFillColor(
                    sf::Color(color[0], color[1], color[2], color[3]));
                sliderComp.getCursorShape().setFillColor(
                    sf::Color(color[0], color[1], color[2], color[3]));
            }

            sliderComp.setIsLoaded();
            sliderComp.setValue(sliderComp.getValue());
        }
        static std::map<GameEngine::Entity*, bool> wasPressedMap;
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::FloatRect barBounds = sliderComp.getBarShape().getGlobalBounds();

        if (barBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

            if (isPressed && !wasPressedMap[&entity]) {
                wasPressedMap[&entity] = true;
            } else if (!isPressed) {
                wasPressedMap[&entity] = false;
            }
            if (wasPressedMap[&entity]) {
                float newValue = sliderComp.triggerGetCallback();
                newValue = std::clamp(newValue, 0.f, 1.f);

                float sliderValue = sliderComp.getMinValue() + newValue * (sliderComp.getMaxValue() - sliderComp.getMinValue());

                sliderComp.setValue(sliderValue);

                float cursorX = barBounds.left + newValue * barBounds.width;
                sliderComp.getCursorShape().setPosition(
                    cursorX - sliderComp.getCursorShape().getRadius(), 
                    sliderComp.getCursorShape().getPosition().y
                );
                sliderComp.triggerSetCallback(sliderValue);
            }
        }

        window.draw(sliderComp.getBarShape());
        window.draw(sliderComp.getCursorShape());
    }
}

void GameEngine::System::render(sf::RenderWindow& window,
                                std::map<int, Entity>& entities) {
    for (auto& [id, entity] : entities) {
        spriteSystem(window, entity);
        textSystem(window, entity);
        optionButtonSystem(window, entity);
        sliderSystem(window, entity);
    }
}

void GameEngine::System::update(Entity& entity, const UpdateType type,
                                std::any value) {
    switch (type) {
    case UpdateType::Position: {
        auto pos = std::any_cast<std::pair<float, float>>(value);
        entity.getComponent<Position>().setPositionX(pos.first);
        entity.getComponent<Position>().setPositionY(pos.second);
        entity.getComponent<Sprite>().getSprite().setPosition(pos.first,
                                                              pos.second);
        break;
    }
    default:;
    }
}

GameEngine::System::~System() {}