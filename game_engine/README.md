# R-Type Project - Classes Overview

This README provides an overview of the main classes used in the R-Type project. Each class is designed to manage specific features like health, physics, graphics, and user interaction in the game. Below, you'll find detailed descriptions of each class along with its attributes and functions.

## Table of Contents

- [Health Class](#health-class)
- [Rigidbody Class](#rigidbody-class)
- [Position Class](#position-class)
- [Renderable Class](#renderable-class)
- [Text Class](#text-class)
- [Sprite Class](#sprite-class)
- [Bullet Class](#bullet-class)
- [Button Class](#button-class)
- [Velocity Class](#velocity-class)
- [Input Class](#input-class)
- [Collider Class](#collider-class)
- [Color Class](#color-class)
- [Sound Class](#sound-class)
- [Animation Class](#animation-class)

---

## Health Class

### Description:
The **Health** class manages the health system of an entity in the game, tracking both the current and maximum health.

### Attributes:
- **_currentHp**: Current health points.
- **_maxHp**: Maximum health points (fixed at 100).

### Functions:
- `getCurrentHp()`: Returns the current health points.
- `setCurrentHp(int currentHp)`: Sets the current health points.
- `getMaxHp()`: Returns the maximum health points.
- `setMaxHp(int maxHp)`: Sets the maximum health points.

---

## Rigidbody Class

### Description:
The **Rigidbody** class represents the physics body of an entity, with attributes to manage mass, drag, gravity, and forces.

### Attributes:
- **_mass**: Mass of the entity.
- **_drag**: Drag (resistance) factor.
- **_gravityScale**: Gravity scale applied to the entity.
- **_forceX**: Horizontal force applied to the entity.
- **_forceY**: Vertical force applied to the entity.

### Functions:
- `getMass()`: Returns the mass of the entity.
- `setMass(float mass)`: Sets the mass of the entity.
- `getDrag()`: Returns the drag factor.
- `setDrag(float drag)`: Sets the drag factor.
- `getGravityScale()`: Returns the gravity scale.
- `setGravityScale(float gravityScale)`: Sets the gravity scale.
- `getForceX()`: Returns the horizontal force.
- `setForceX(float forceX)`: Sets the horizontal force.
- `getForceY()`: Returns the vertical force.
- `setForceY(float forceY)`: Sets the vertical force.

---

## Position Class

### Description:
The **Position** class tracks the position of an entity in 2D space, using `x` and `y` coordinates.

### Attributes:
- **_x**: Horizontal position.
- **_y**: Vertical position.

### Functions:
- `getPositionX()`: Returns the horizontal position.
- `getPositionY()`: Returns the vertical position.
- `setPositionX(float x)`: Sets the horizontal position.
- `setPositionY(float y)`: Sets the vertical position.

---

## Renderable Class

### Description:
The **Renderable** class determines whether an entity is visible or not in the game world.

### Attributes:
- **_isVisible**: Visibility flag (true or false).

### Functions:
- `getIsVisible()`: Returns whether the entity is visible.
- `setIsVisible(bool isVisible)`: Sets the visibility of the entity.

---

## Text Class

### Description:
The **Text** class handles the display of text on the screen, storing the text content.

### Attributes:
- **_text**: The text string to be displayed.

### Functions:
- `getText()`: Returns the text content.
- `setText(std::string text)`: Sets the text content.

---

## Sprite Class

### Description:
The **Sprite** class handles the visual representation of an entity, including its texture path and size.

### Attributes:
- **_texturePath**: Path to the texture file.
- **_size**: Size of the sprite (width and height).

### Functions:
- `getTexturePath()`: Returns the texture file path.
- `setTexturePath(std::string texturePath)`: Sets the texture file path.
- `getSize()`: Returns the size of the sprite.
- `setSize(std::vector<double> size)`: Sets the size of the sprite.

---

## Bullet Class

### Description:
The **Bullet** class manages the properties of a bullet fired by an entity, including damage and source entity.

### Attributes:
- **_damage**: The damage dealt by the bullet.
- **_sourceEntity**: The entity that fired the bullet.

### Functions:
- `getDamage()`: Returns the bullet's damage.
- `setDamage(int damage)`: Sets the bullet's damage.

---

## Button Class

### Description:
The **Button** class represents a clickable button in the user interface, with text and size properties.

### Attributes:
- **_text**: The text displayed on the button.
- **_size**: The size of the button.

### Functions:
- `getText()`: Returns the button's text.
- `setText(std::string text)`: Sets the button's text.
- `getSize()`: Returns the button's size.
- `setSize(std::vector2f size)`: Sets the button's size.

---

## Velocity Class

### Description:
The **Velocity** class represents the movement speed of an entity in 2D space.

### Attributes:
- **_x**: Horizontal velocity.
- **_y**: Vertical velocity.

### Functions:
- `getVelocityX()`: Returns the horizontal velocity.
- `getVelocityY()`: Returns the vertical velocity.
- `setVelocityX(float x)`: Sets the horizontal velocity.
- `setVelocityY(float y)`: Sets the vertical velocity.

---

## Input Class

### Description:
The **Input** class tracks user input for player movement and actions, including direction and attack state.

### Attributes:
- **_up**: Movement up.
- **_right**: Movement right.
- **_left**: Movement left.
- **_down**: Movement down.
- **_attack**: Whether the player is attacking.
- **_autoFire**: Whether the player has auto-fire enabled.

### Functions:
- `getUp()`: Returns the "up" movement state.
- `getRight()`: Returns the "right" movement state.
- `getLeft()`: Returns the "left" movement state.
- `getDown()`: Returns the "down" movement state.
- `getAttack()`: Returns whether the player is attacking.
- `getAutoFire()`: Returns whether auto-fire is enabled.
- `setUp(bool up)`: Sets the "up" movement state.
- `setRight(bool right)`: Sets the "right" movement state.
- `setLeft(bool left)`: Sets the "left" movement state.
- `setDown(bool down)`: Sets the "down" movement state.
- `setAttack(bool attack)`: Sets the attack state.
- `setAutoFire(bool autoFire)`: Sets the auto-fire state.

---

## Collider Class

### Description:
The **Collider** class represents the collision boundaries of an entity, typically using a bounding box.

### Attributes:
- **_size**: Size of the collider.

### Functions:
- `getCollider()`: Returns the collider size.
- `setCollider(std::vector<double> size)`: Sets the collider size.

---

## Color Class

### Description:
The **Color** class defines the color of an entity using RGBA values stored in a vector.

### Attributes:
- **_color**: A vector storing the color components (R, G, B, A).

### Functions:
- `getColor()`: Returns the color.
- `setColor(std::vector<double> color)`: Sets the color.

---

## Sound Class

### Description:
The **Sound** class manages sound effects, including the file path and volume.

### Attributes:
- **_soundFile**: Path to the sound file.
- **_volume**: Volume level for the sound.

### Functions:
- `getSoundFile()`: Returns the sound file path.
- `setSoundFile(std::string soundFile)`: Sets the sound file path.
- `getVolume()`: Returns the volume level.
- `setVolume(int volume)`: Sets the volume level.

---

## Animation Class

### Description:
The **Animation** class handles frame-based animations, tracking the current frame and time-related parameters.

### Attributes:
- **_currentFrame**: The current frame of the animation.
- **_frameDuration**: Duration each frame should be displayed.
- **_elapsedTime**: Time elapsed since the last frame update.

### Functions:
- `getCurrentFrame()`: Returns the current animation frame.
- `setCurrentFrame(int currentFrame)`: Sets the current animation frame.
- `getFrameDuration()`: Returns the frame duration.
- `setFrameDuration(float frameDuration)`: Sets the frame duration.
- `getElapsedTime()`: Returns the elapsed time.
- `setElapsedTime(float elapsedTime)`: Sets the elapsed time.

---
