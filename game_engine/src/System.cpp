/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** System.cpp
*/

#include "System.hpp"
#include <components/Button.hpp>
#include <components/Color.hpp>
#include <components/Link.hpp>
#include <components/OptionButton.hpp>
#include <components/Position.hpp>
#include <components/Shape.hpp>
#include <components/Slider.hpp>
#include <components/Sprite.hpp>
#include <components/Text.hpp>
#include <components/Texture.hpp>
#include <iostream>

GameEngine::System::System() {}

template <typename Drawable>
static void updatePos(GameEngine::Entity& entity, Drawable& drawable,
                      const std::pair<float, float>& pos, const int& posId) {
    if (entity.hasComponent<Position>()) {
        auto& positionComp = entity.getComponent<Position>();
        positionComp.setPositionX(posId, pos.first);
        positionComp.setPositionY(posId, pos.second);
        drawable.setPosition(pos.first, pos.second);
    }
}

template <typename Drawable>
void setColor(GameEngine::Entity& entity, Drawable& drawable) {
    if (entity.hasComponent<Color>() &&
        entity.getComponent<Color>().getColor().size() == 4) {
        auto& colorComp = entity.getComponent<Color>();
        const auto& color = colorComp.getColor();
        if constexpr (std::is_same_v<Drawable, sf::Sprite>) {
            drawable.setColor(
                sf::Color(color[0], color[1], color[2], color[3]));
        } else if constexpr (std::is_same_v<Drawable, sf::Text> ||
                             std::is_same_v<Drawable, sf::RectangleShape> ||
                             std::is_same_v<Drawable, sf::CircleShape>) {
            drawable.setFillColor(
                sf::Color(color[0], color[1], color[2], color[3]));
        }
    }
}

template <typename Drawable>
static void setPosition(GameEngine::Entity& entity, Drawable& drawable) {
    if (entity.hasComponent<Position>()) {
        auto& positionComp = entity.getComponent<Position>();
        drawable.setPosition(positionComp.getPositionX(0),
                             positionComp.getPositionY(0));
    }
}

static void linkSystem(int id, std::map<int, GameEngine::Entity>& entities,
                       std::pair<float, float> newLinkedEntityPos,
                       const int posId) {
    for (int i = 0; i < entities.size(); i++) {
        if (entities[i].hasComponent<Link>() &&
            entities[i].getComponent<Link>().getId() == id) {
            GameEngine::Entity entity = entities[i];
            GameEngine::Entity entityLinked = entities[id];
            auto oldLinkedEntityPos = entityLinked.getComponent<Position>();
            const std::pair dist = {newLinkedEntityPos.first -
                                        oldLinkedEntityPos.getPositionX(posId),
                                    newLinkedEntityPos.second -
                                        oldLinkedEntityPos.getPositionY(posId)};
            auto entityPos = entity.getComponent<Position>();
            const std::pair newPos = {entityPos.getPositionX(0) + dist.first,
                                      entityPos.getPositionY(0) + dist.second};
            if (entity.hasComponent<Sprite>()) {
                updatePos(entity, entity.getComponent<Sprite>().getSprite(),
                          newPos, 0);
            }
            if (entity.hasComponent<Text>()) {
                updatePos(entity, entity.getComponent<Text>().getText(), newPos,
                          0);
            }
        }
    }
}

static void spriteSystem(sf::RenderWindow& window, GameEngine::Entity& entity) {
    if (entity.hasComponent<Sprite>() && entity.hasComponent<Texture>() &&
        entity.hasComponent<Position>()) {
        auto& spriteComp = entity.getComponent<Sprite>();
        auto& textureComp = entity.getComponent<Texture>();
        if (!textureComp.getIsLoaded()) {
            textureComp.getTexture().loadFromFile(textureComp.getTexturePath());
            textureComp.setIsLoaded(true);
        }
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

static void textSystem(sf::RenderWindow& window, GameEngine::Entity& entity) {
    if (entity.hasComponent<Text>() && entity.hasComponent<Position>()) {
        auto& textComp = entity.getComponent<Text>();
        if (!textComp.getIsLoaded()) {
            textComp.getFont().loadFromFile(textComp.getFontFile());
            textComp.getText().setFont(textComp.getFont());
            textComp.getText().setString(textComp.getString());
            textComp.getText().setCharacterSize(textComp.getCharacterSize());
            setPosition(entity, textComp.getText());
            setColor(entity, textComp.getText());
            textComp.setIsLoaded(true);
        }
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

static void buttonSystem(sf::RenderWindow& window, GameEngine::Entity& entity) {
    if (entity.hasComponent<Button>() && entity.hasComponent<Position>()) {
        auto& buttonComp = entity.getComponent<Button>();
        auto& positionComp = entity.getComponent<Position>();

        if (!buttonComp.getIsLoaded()) {

            buttonComp.getFont().loadFromFile(buttonComp.getFontFile());

            buttonComp.getText().setFont(buttonComp.getFont());
            buttonComp.getText().setString(buttonComp.getString());
            buttonComp.getText().setCharacterSize(
                buttonComp.getCharacterSize());
            buttonComp.getText().setFillColor(sf::Color::White);

            sf::FloatRect textBounds = buttonComp.getText().getGlobalBounds();

            buttonComp.getButton().setSize(
                sf::Vector2f(textBounds.width, textBounds.height));
            buttonComp.getButton().setFillColor(sf::Color::Transparent);
            buttonComp.getButton().setPosition(positionComp.getPositionX(0),
                                               positionComp.getPositionY(0));

            buttonComp.getText().setOrigin(textBounds.width / 2,
                                           textBounds.height / 2);
            buttonComp.getText().setPosition(
                buttonComp.getButton().getPosition().x +
                    buttonComp.getButton().getSize().x / 2,
                (buttonComp.getButton().getPosition().y +
                 buttonComp.getButton().getSize().y / 2) -
                    15);

            buttonComp.setIsLoaded(true);
        }
        static std::map<GameEngine::Entity*, bool> wasPressedMap;
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::FloatRect buttonBounds = buttonComp.getButton().getGlobalBounds();

        if (buttonBounds.contains(static_cast<float>(mousePos.x),
                                  static_cast<float>(mousePos.y))) {
            bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
            if (isPressed && !wasPressedMap[&entity]) {
                buttonComp.executeCallback();
                wasPressedMap[&entity] = true;
            } else if (!isPressed) {
                wasPressedMap[&entity] = false;
            }
        }
        window.draw(buttonComp.getButton());
        window.draw(buttonComp.getText());
    }
}

static void shapeSystem(sf::RenderWindow& window, GameEngine::Entity& entity) {
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
                    std::cout << "Texture loaded" << std::endl;
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
                    std::cout << "Texture loaded" << std::endl;
                }
                shapeComp.setIsLoaded(true);
            }
            window.draw(shapeComp.getCircle());
        }
    }
}

static void optionButtonSystem(sf::RenderWindow& window,
                               GameEngine::Entity& entity) {
    if (entity.hasComponent<OptionButton>() &&
        entity.hasComponent<Position>()) {
        auto& buttonComp = entity.getComponent<OptionButton>();
        auto& positionComp = entity.getComponent<Position>();

        if (!buttonComp.getIsLoaded()) {
            sf::RectangleShape buttonShape;
            buttonShape.setSize(
                {static_cast<float>(buttonComp.getSize().first),
                 static_cast<float>(buttonComp.getSize().second)});
            buttonShape.setPosition(positionComp.getPositionX(0),
                                    positionComp.getPositionY(0));
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

        if (buttonBounds.contains(static_cast<float>(mousePos.x),
                                  static_cast<float>(mousePos.y))) {
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
            barShape.setPosition(positionComp.getPositionX(0),
                                 positionComp.getPositionY(0));
            barShape.setSize({static_cast<float>(sliderComp.getSize().first),
                              static_cast<float>(sliderComp.getSize().second)});
            barShape.setOutlineThickness(5);
            barShape.setOutlineColor(sf::Color::Transparent);

            sf::CircleShape cursorShape;
            cursorShape.setPosition(positionComp.getPositionX(0),
                                    positionComp.getPositionY(0) - 7);
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

        if (barBounds.contains(static_cast<float>(mousePos.x),
                               static_cast<float>(mousePos.y))) {
            bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

            if (isPressed && !wasPressedMap[&entity]) {
                wasPressedMap[&entity] = true;
            } else if (!isPressed) {
                wasPressedMap[&entity] = false;
            }
            if (wasPressedMap[&entity]) {
                float newValue =
                    (mousePos.x - barBounds.left) / barBounds.width;
                newValue = std::clamp(newValue, 0.f, 1.f);

                float sliderValue = sliderComp.getMinValue() +
                                    newValue * (sliderComp.getMaxValue() -
                                                sliderComp.getMinValue());
                sliderComp.setValue(sliderValue);

                float cursorX = barBounds.left + newValue * barBounds.width;
                sliderComp.getCursorShape().setPosition(
                    cursorX - sliderComp.getCursorShape().getRadius(),
                    sliderComp.getCursorShape().getPosition().y);
                sliderComp.triggerSetCallback(sliderComp.getValue());
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
        buttonSystem(window, entity);
        optionButtonSystem(window, entity);
        sliderSystem(window, entity);
        shapeSystem(window, entity);
    }
}

void GameEngine::System::update(const int id, std::map<int, Entity>& entities,
                                const UpdateType type, const std::any& value,
                                const int posId) {
    Entity entity = entities[id];
    switch (type) {
    case UpdateType::Position: {
        auto pos = std::any_cast<std::pair<float, float>>(value);
        // linkSystem(id, entities, pos, posId);
        if (entity.hasComponent<Sprite>()) {
            updatePos(entity, entity.getComponent<Sprite>().getSprite(), pos,
                      posId);
        }
        if (entity.hasComponent<Text>()) {
            updatePos(entity, entity.getComponent<Text>().getText(), pos,
                      posId);
        }
        break;
    }
    default:;
    }
}

GameEngine::System::~System() {}