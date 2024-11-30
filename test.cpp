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

// Fonction pour ajouter deux nombres
int add(int a, int b) {
    return a + b;
}

// Fonction principale
int main() {
    int num1 = 10;
    int num2 = 20;

    // Calcul de la somme
    int result = add(num1, num2);

    printf("La somme de %d et %d est %d\n", num1, num2, result);

    // Boucle pour afficher des nombres
    for (int i = 0; i < 5; i++) {
        printf("Nombre : %d\n", i);
    }

    return 0;
}
