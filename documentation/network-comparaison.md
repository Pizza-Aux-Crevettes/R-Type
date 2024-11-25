
# Comparaison des méthodes réseau pour le R-Type

Ce document détaille une comparaison directe entre les protocoles **TCP**, **UDP** et une approche hybride **TCP+UDP**, adaptés au projet de jeu multijoueur R-Type. Chaque méthode est évaluée en termes de performances, fiabilité et pertinence pour un environnement de jeu en réseau.

---

## Critères de Comparaison

### 1. **Latence**
- **TCP** : Latence élevée en raison de son mécanisme de retransmission et d'ordonnancement. Chaque perte de paquet entraîne un délai supplémentaire.
- **UDP** : Latence faible, les paquets sont envoyés immédiatement sans confirmation.
- **TCP+UDP** : Latence équilibrée, TCP gérant les données critiques et UDP les mises à jour fréquentes.

### 2. **Fiabilité**
- **TCP** : Très fiable, garantit que tous les paquets arrivent dans le bon ordre.
- **UDP** : Peu fiable, les paquets peuvent être perdus, dupliqués ou désordonnés.
- **TCP+UDP** : Fiabilité modulée. TCP assure la fiabilité pour les communications critiques, tandis qu’UDP tolère des pertes dans les mises à jour non essentielles.

### 3. **Complexité d’Implémentation**
- **TCP** : Facile à implémenter, les bibliothèques réseau gèrent la retransmission et l’ordonnancement.
- **UDP** : Plus complexe, nécessite des mécanismes personnalisés pour gérer les pertes, la latence et la synchronisation.
- **TCP+UDP** : Complexité élevée, les développeurs doivent intégrer et synchroniser les deux protocoles.

### 4. **Adaptabilité aux Jeux Rapides**
- **TCP** : Mauvaise, les délais causés par la retransmission impactent la réactivité.
- **UDP** : Excellente, adaptée aux mises à jour fréquentes et à faible latence.
- **TCP+UDP** : Bonne, chaque protocole est utilisé en fonction de ses forces.

---

## Comparaison en Tableau

| Critères                  | TCP                   | UDP                   | Hybride (TCP+UDP)       |
|---------------------------|-----------------------|-----------------------|-------------------------|
| **Latence**               | Élevée               | Faible                | Moyenne                |
| **Fiabilité**             | Très bonne           | Moyenne               | Très bonne             |
| **Complexité**            | Faible               | Élevée                | Élevée                 |
| **Adapté aux jeux rapides**| Non                  | Oui                   | Oui                    |

---

## Recommandation pour R-Type

Pour un jeu rapide comme R-Type, l’approche hybride **TCP+UDP** est fortement recommandée :
- **TCP** : Utilisé pour les données critiques telles que la gestion des connexions, la synchronisation initiale et les événements de jeu importants.
- **UDP** : Utilisé pour les mises à jour en temps réel des entités, les mouvements, les tirs et autres éléments nécessitant une faible latence.

Cette approche garantit un équilibre entre fiabilité et réactivité, crucial pour une expérience de jeu fluide.

---

## Références et Outils

### Références
- [Fast-Paced Multiplayer Game Networking (Gabriel Gambetta)](https://www.gabrielgambetta.com/client-side-prediction-live-demo.html)
- [Quake 3 Networking Model](https://fabiensanglard.net/quake3/network.php)
- [Overwatch Netcode Explained](https://gdcvault.com)

---