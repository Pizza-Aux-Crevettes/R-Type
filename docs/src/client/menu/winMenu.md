# WinMenu

The WinMenu class handles the creation and display of the lose menu in the game, where the player can view the game over screen and exit the game. It provides methods to create various entities such as buttons, text, sprites, and rectangles, and arranges them on the screen in a responsive manner. The class also includes a method to handle user interaction, specifically when the Exit button is clicked, closing the game window. 

| Functions                          | Description                                                                                       |
|-------------------------------------|---------------------------------------------------------------------------------------------------|
| createEntityButton                  | Creates and returns a button entity with specified properties, including a callback function for interaction. |
| createEntityText                    | Creates and returns a text entity with specified text, position, and font size, applying different colors based on text. |
| createEntitySprite                  | Creates and returns a sprite entity with specified size, texture, texture rectangle, and position.  |
| createEntityRect                    | Creates and returns a rectangle entity, which is typically used as a button, with a color and an interaction callback. |
| isClickedExit                       | Closes the window when the “Exit” button is clicked.                                               |
| displayWinMenu                     | Initializes and renders all entities for the Win menu, including sprites, text, and buttons, with responsive positioning based on window size. |