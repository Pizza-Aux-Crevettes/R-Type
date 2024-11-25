
# Comparaison ECS (Entity-Component-System) et COI (Composition-Over-Inheritance)

Ce document compare deux approches fondamentales utilisées dans les moteurs de jeu : **ECS** (Entity-Component-System) et **COI** (Composition-Over-Inheritance). Ces deux paradigmes influencent la manière dont les entités, les données et la logique sont structurées dans un projet.

---

## ECS (Entity-Component-System)

### Description :
- Les entités sont de simples identifiants.
- Les composants stockent uniquement des données.
- Les systèmes contiennent la logique métier et manipulent les composants associés.

### Avantages :
- **Modularité** : Très flexible, les composants peuvent être ajoutés ou retirés dynamiquement.
- **Performance** : Optimisé pour les processeurs multicœurs grâce à la parallélisation.
- **Séparation claire** : Les données et la logique sont bien isolées.

### Inconvénients :
- Complexité initiale plus élevée.
- Gestion des performances requiert une attention particulière (ex : allocations mémoire fréquentes).

### Cas d’utilisation :
- Moteurs AAA comme Unity et Unreal Engine.
- Jeux nécessitant la gestion simultanée de milliers d'entités.

### Références :
- [Introduction à ECS](https://en.wikipedia.org/wiki/Entity_component_system)
- [Formation d’un moteur ECS](http://guillaume.belz.free.fr/doku.php?id=ecs)

---

## COI (Composition-Over-Inheritance)

### Description :
- Privilégie l'agrégation d'objets (objets contenant d'autres objets) à l'héritage.
- Les fonctionnalités sont découpées en composants réutilisables et combinables.

### Avantages :
- **Flexibilité accrue** : Les composants peuvent être ajoutés ou retirés sans modifier les entités.
- **Indépendance** : Chaque comportement est autonome et remplaçable.
- **Évite les grandes hiérarchies** : Moins de dépendances rigides.

### Inconvénients :
- Peut nécessiter plus de code pour gérer explicitement les composants.
- Moins performant et plus dispersé que ECS pour les projets avec de nombreuses entités.

### Cas d’utilisation :
- Frameworks comme Godot (via des Nodes combinables).
- Projets de taille moyenne ou avec des besoins en flexibilité de comportement.

---

## Comparaison : ECS vs COI

| Aspect               | ECS                                   | COI                                       |
|----------------------|---------------------------------------|-------------------------------------------|
| **Description**      | Identifiants, données et systèmes séparés. | Composants indépendants combinés dans des entités. |
| **Structure des entités** | Identifiants simples associés à des composants. | Entités contenant directement leurs composants. |
| **Données**          | Conteneurs de données sans logique.  | Contiennent à la fois données et comportements. |
| **Logique**          | Centralisée dans des systèmes réutilisables. | Encapsulée dans chaque composant localement. |
| **Modularité**       | Dynamique : composants ajoutés/retirés facilement. | Intégrée directement dans l'entité. |
| **Performances**     | Excellentes (stockage contigu, cache-friendly). | Moins performant (cache-misses fréquents). |
| **Complexité**       | Plus complexe à initialiser et comprendre. | Simplicité pour des projets de taille moyenne. |
| **Exemples**         | Unity, Unreal Engine.                | Godot, projets flexibles de taille moyenne. |

---

## Recommandation

- **ECS** : Idéal pour les jeux complexes avec des milliers d’entités à gérer simultanément.
- **COI** : Parfait pour des projets de taille moyenne où la lisibilité et la flexibilité priment.