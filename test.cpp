/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Implements the `GameEngine` class, which acts as the core of
** the game engine. It coordinates the initialization, update, and shutdown
** of the entire system.
** Responsibilities:
** - Initialize core engine components like systems and managers.
** - Manage the game loop, including updates and rendering.
*/

#include <stdio.h>

int add(int a, int b) { return a + b; }

int main()
{
    int num1 = 10;
    int num2 = 20;
    int result = add(num1, num2);

    printf("La somme de %d et %d est %d\n", num1, num2, result);
    for (int i = 0; i < 5; i++)
    {
        printf("Nombre : %d\n", i);
    }
    return 0;
}
