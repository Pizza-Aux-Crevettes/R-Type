
# clang-format pour R-Type

Ce document explique comment configurer et utiliser **clang-format** pour garantir une norme de codage cohérente dans le projet R-Type.

---

## Pourquoi utiliser clang-format ?

- Assure un style de code uniforme pour tous les contributeurs.
- Compatible avec la majorité des IDE (Visual Studio Code, CLion, etc.).
- Automatise le formatage du code pour se concentrer sur le développement.

---

## Installation de clang-format

### **Linux**
1. Installez clang-format via votre gestionnaire de paquets :
   ```bash
   sudo apt install clang-format
   ```

### **MacOS**
1. Installez clang-format avec Homebrew :
   ```bash
   brew install clang-format
   ```

### **Vérification**
1. Assurez-vous que clang-format est correctement installé :
   ```bash
   clang-format --version
   ```

---

## Configuration avec `.clang-format`

Ajoutez le fichier `.clang-format` suivant à la racine du projet R-Type pour définir les règles de style.

```yaml
BasedOnStyle: LLVM
IndentWidth: 4
ColumnLimit: 100
BreakBeforeBraces: Allman
AllowShortIfStatementsOnASingleLine: false
AlwaysBreakTemplateDeclarations: true
SortIncludes: true
IncludeBlocks: Preserve
SpacesInParentheses: false
```

---

## Utilisation de clang-format

### **Manuel**
1. Formatez un fichier spécifique :
   ```bash
   clang-format -i chemin/vers/fichier.cpp
   ```

2. Formatez tout le projet :
   ```bash
   find . -name '*.cpp' -o -name '*.h' | xargs clang-format -i
   ```

### **Avec les IDE**

#### **VS Code**
1. Installez les extensions **C/C++** et **Clang-Format**.
2. Ajoutez ceci dans `settings.json` :
   ```json
   {
       "C_Cpp.clang_format_style": "file",
       "editor.formatOnSave": true
   }
   ```

#### **CLion**
1. Allez dans **File > Settings > Editor > Code Style > C/C++**.
2. Activez **Use clang-format file**.

---

## Intégration CI/CD

Ajoutez une étape dans votre pipeline CI pour valider le formatage :
```yaml
- name: Vérification clang-format
  run: |
    find . -name '*.cpp' -o -name '*.h' | xargs clang-format --dry-run --Werror
```

---

## Commandes essentielles

| Action                          | Commande                                        |
|---------------------------------|------------------------------------------------|
| Formater un fichier             | `clang-format -i fichier.cpp`                  |
| Formater tous les fichiers      | `find . -name '*.cpp' -o -name '*.h' | xargs clang-format -i` |
| Vérifier sans modifier          | `clang-format --dry-run fichier.cpp`           |

---

## Références

- [Documentation officielle clang-format](https://clang.llvm.org/docs/ClangFormat.html)
- [Exemple de fichier .clang-format](https://github.com/llvm/llvm-project/tree/main/clang/tools/clang-format)

---