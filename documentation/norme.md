
# Norme de Commit pour R-Type

Ce document décrit la norme de commit basée sur **Conventional Commits**, adaptée au projet R-Type. Cette convention garantit des messages clairs et structurés pour une meilleure lisibilité et gestion du code.

---

## Structure des Messages de Commit

Chaque message de commit doit suivre ce format :
```
<TYPE>: <DESCRIPTION>
```
- **TYPE** : Le type du changement, écrit en **majuscule**.
- **DESCRIPTION** : Une description concise et précise de la modification.

### Types Principaux

| Type       | Description                                                               |
|------------|---------------------------------------------------------------------------|
| **FEAT**   | Ajout d'une nouvelle fonctionnalité                                       |
| **FIX**    | Correction d'un bug                                                      |
| **DOCS**   | Modification ou ajout de documentation                                   |
| **STYLE**  | Changement lié au style (formatage, espaces, etc.) sans impact fonctionnel |
| **REFACTOR** | Modification du code sans ajout de fonctionnalités ou correction de bug |
| **TEST**   | Ajout ou mise à jour des tests                                           |
| **CHORE**  | Changements divers sans impact sur le code source ou les tests           |

### Exemples de Messages

- **Ajout d'une fonctionnalité** :
  ```
  FEAT: Added collision system for missiles
  ```

- **Correction d'un bug** :
  ```
  FIX: Fixed crash when moving player
  ```

- **Mise à jour de la documentation** :
  ```
  DOCS: Updated installation instructions
  ```

- **Amélioration du style** :
  ```
  STYLE: Applying clang-format to source files
  ```

---

## Règles Complémentaires

- **Langue** : Tous les messages de commit doivent être rédigés en anglais.
- **Taille** : La description doit tenir en une seule ligne (environ 72 caractères).
- **Concision** : Évitez les détails inutiles. Les explications détaillées peuvent être ajoutées dans la description étendue (optionnelle).

### Format Étendu (Optionnel)
Pour un commit complexe, vous pouvez ajouter une description étendue après une ligne vide :
```
<TYPE>: <DESCRIPTION>

<DESCRIPTION ÉTENDUE>
```

Exemple :
```
FIX: Fixed poorly rendered borders on enemies

Borders were misaligned due to a problem in the method
render() of the Enemy object. The function has been fixed to handle sizes.
```

---