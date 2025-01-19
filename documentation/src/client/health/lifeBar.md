#LifeBar

The LifeBar class manages the health bar functionality for a player, including creating health-related UI elements, updating health points, and rendering the life bar on the screen. It uses a singleton pattern to ensure a single instance is accessible globally.

| Functions                          | Description                                                                                       |
|-------------------------------------|---------------------------------------------------------------------------------------------------|
| createEntityText           | Creates a text entity with specified attributes (text, position, font size) and adjusts its color based on health points. |
| displayLifeBar             | Displays the life bar with updated health points, rendering the entities to the window.           |
| manageHealth               | Updates the health points if the provided entity ID matches the player ID.                       |