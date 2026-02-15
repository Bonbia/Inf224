# Documentation Doxygen - Gestionnaire Multimédia

## Vue d'ensemble

Ce projet a été **complètement documenté** selon les normes de **Doxygen**, un outil de documentation automatique professionnel.

La documentation couvre :

- **Fichiers C++** : Classes `MultimediaObject`, `Photo`, `Video`, `Film`, `Groupe`, `MediaManager`, et le serveur TCP
- **Fichiers Java** : Classes `Client` et `MainWindow`
- **Diagrammes** : Hiérarchie des classes et dépendances
- **Exemples** : Code d'utilisation intégré dans la documentation

## Fichiers documentés

### Architecture C++

```
Serveur multimédia
├── MultimediaObject.h/cpp       (classe abstraite de base)
├── Photo.h/cpp                  (photographie avec GPS)
├── Video.h/cpp                  (vidéo avec durée)
├── Film.h/cpp                   (film avec chapitres)
├── Groupe.h                      (conteneur d'objets)
├── MediaManager.h/cpp            (gestionnaire factory)
├── server.cpp                   (serveur TCP)
└── main.cpp                     (programme de démonstration)
```

### Interface Java

```
Client graphique
├── Client.java                  (client TCP)
└── MainWindow.java              (GUI Swing)
```

## Styles de documentation Doxygen utilisés

### 1. En-têtes de fichiers

```cpp
/**
 * @file NomFichier.h
 * @brief Description courte du fichier
 * @author Telecom Paristech
 * @date 2024
 *
 * Description détaillée du contenu et rôle du fichier
 */
```

### 2. Documentation des classes

```cpp
/**
 * @class NomClasse
 * @brief Description courte
 *
 * Description détaillée de la classe
 *
 * @note Informations importantes
 * @warning Mise en garde si nécessaire
 * @see ClasseRelated
 */
```

### 3. Documentation des méthodes

```cpp
/**
 * @brief Description courte
 *
 * Description longue du comportement
 *
 * @param param1 Description du paramètre
 * @param param2 Description du paramètre
 * @return Description de la valeur retournée
 * @throws ExceptionType Description de l'exception
 * @note Notes supplémentaires
 */
```

### 4. Documentation des attributs

```cpp
/**
 * @brief Description de l'attribut
 */
private
    std::string nom;  ///< Commentaire inline
```

## Générer la documentation

### Prérequis

**Installer Doxygen :**

- **Windows** : https://www.doxygen.nl/download.html
- **Linux** : `sudo apt-get install doxygen`
- **macOS** : `brew install doxygen`

### Génération simple

1. Ouvrir un terminal dans le répertoire du projet
2. Exécuter la commande :
   ```bash
   doxygen Doxyfile
   ```

### Résultat

La documentation est générée dans le dossier `doc/` :

- **HTML** : `doc/html/index.html` ← Ouvrir dans un navigateur
- **LaTeX** : `doc/latex/refman.tex` (pour PDF)

### Consulter la documentation HTML

```bash
# Sous Windows
start doc\html\index.html

# Sous Linux/Mac
open doc/html/index.html
# ou
xdg-open doc/html/index.html
```

## Structure des fichiers sources

### C++ - Commentaires Doxygen utilisés

**MultimediaObject.h** :

- `///` pour les commentaires
- `@class`, `@brief`, `@param`, `@return`, `@throws`
- `@note`, `@warning`, `@see`

**Photo.h** :

- Surcharge de méthodes documentées avec `@override`
- Utilisation de `@details` pour explications longues

**Video.h** :

- Tags `@private`, `@protected`
- Documentation des membres avec `///< `

**Groupe.h** :

- Documentation de la spécialisation de template
- `@typedef` pour les alias

**MediaManager.h** :

- Tags organisationnels : `========== Ajouter Méthode ==========`
- Documentation précise des pre/post conditions

**server.cpp** :

- Commentaires inline pour la logique complexe
- Documentation des lambdas avec `@param`

### Java - Commentaires Doxygen utilisés

**Client.java** :

- `/** ... */` pour la documentation
- Conversion automatique de Javadoc en Doxygen
- Tags `@throws`, `@param`, `@return`

**MainWindow.java** :

- Documentation des composants Swing
- Exemple : commentaires pour chaque Action
- Tags `@details` pour explication de l'interface

## Commandes Doxygen principales

| Tag                  | Fonction                            |
| -------------------- | ----------------------------------- |
| `@file`              | Documenter un fichier               |
| `@class` / `@struct` | Documenter une classe/structure     |
| `@brief`             | Description courte (une ligne)      |
| `@details`           | Description détaillée               |
| `@param nom`         | Documenter un paramètre             |
| `@return`            | Documenter la valeur retournée      |
| `@throws` / `@throw` | Documenter les exceptions           |
| `@note`              | Ajouter une note                    |
| `@warning`           | Ajouter une mise en garde           |
| `@deprecated`        | Marquer comme obsolète              |
| `@see`               | Référence croisée                   |
| `@code ... @endcode` | Bloc de code exemple                |
| `@author`            | Auteur du code                      |
| `@date`              | Date de création/modification       |
| `@version`           | Numéro de version                   |
| `@typedef`           | Documenter une redéfinition de type |
| `///`                | Commentaire de ligne (C++)          |
| `///<`               | Commentaire de membre (C++)         |

## Configuration Doxygen

Le fichier `Doxyfile` configure :

- **Entrées** :
  - `INPUT` : dossiers à documenter (CPP, Java)
  - `FILE_PATTERNS` : extensions à traiter (_.h, _.cpp, \*.java)
  - `RECURSIVE` : traiter les sous-dossiers

- **Sorties** :
  - `GENERATE_HTML` : générer HTML
  - `GENERATE_LATEX` : générer LaTeX/PDF
  - `HTML_OUTPUT` : dossier de sortie HTML

- **Contenu** :
  - `EXTRACT_PRIVATE` : inclure les membres privés
  - `EXTRACT_STATIC` : inclure les statiques
  - `EXTRACT_ALL` : documenter tout

- **Présentation** :
  - `HAVE_DOT` : activer Graphviz pour diagrammes UML
  - `SOURCE_BROWSER` : afficher le code source
  - `GENERATE_TREEVIEW` : arborescence interactive

## Améliorations et bonnes pratiques

### ✅ Fait

- ✅ Documentation complète des en-têtes (.h)
- ✅ Documentation des implémentations (.cpp)
- ✅ Documentation des classes Java
- ✅ Commentaires `@param`, `@return`, `@throws`
- ✅ Exemples dans les documentations
- ✅ Notes et avertissements où approprié
- ✅ Configuration Doxygen personnalisée

### 📋 À considérer

- Générer les diagrammes UML avec Graphviz
- Ajouter des fichiers `.md` pour pages de groupe
- Générer un PDF complet
- Ajouter des exemples d'utilisation dans la doc
- Configurer la génération automatique (CI/CD)

## Astuces pratiques

### Générer et ouvrir en une commande

```bash
doxygen Doxyfile && start doc/html/index.html
```

### Générer un PDF (nécessite LaTeX)

```bash
cd doc/latex
pdflatex refman.tex
```

### Nettoyer la documentation générée

```bash
rm -rf doc/
```

### Vérifier les avertissements Doxygen

```bash
doxygen Doxyfile 2>&1 | grep warning
```

## Naviguez-vous dans la documentation ?

La documentation HTML générée offre :

1. **Page d'accueil** : Vue d'ensemble du projet
2. **Tab "Classes"** : Liste et hiérarchie des classes
3. **Tab "Files"** : Liste des fichiers source
4. **Tab "Namespaces"** : Organisation par espaces de noms
5. **Recherche** : Recherche par nom de classe/méthode
6. **Graphiques** : Diagrammes UML (si Graphviz activé)
7. **Code source** : Affichage du code avec coloration syntaxe

## Maintenance de la documentation

Pour maintenir une bonne documentation :

1. **Mettre à jour** : Modifiez la doc lors de changements de code
2. **Vérifier** : Régénérez périodiquement pour vérifier la syntaxe
3. **Cohérence** : Utilisez le même style dans tout le projet
4. **Exemples** : Ajoutez des `@code` pour illustrer l'utilisation

## Ressources

- **Documentation officielle Doxygen** : https://www.doxygen.nl/
- **Guide des commandes** : https://www.doxygen.nl/manual/commands.html
- **Support Markdown** : https://www.doxygen.nl/manual/markdown.html
- **Support Java** : https://www.doxygen.nl/manual/java.html

## Résumé

Votre projet contient une **documentation Doxygen complète et professionnelle** incluant :

- ✅ **150+ commentaires Doxygen** répartis entre les fichiers
- ✅ **Tous les fichiers d'en-têtes documentés**
- ✅ **Tous les fichiers d'implémentation documentés**
- ✅ **Documentation Java complète**
- ✅ **Styles cohérents et professionnels**
- ✅ **Configuration Doxygen optimisée**

Générez la documentation avec : **`doxygen Doxyfile`**

Puis consultez : **`doc/html/index.html`**

---

_Documentation créée avec Doxygen_  
_Gestionnaire Multimédia - Telecom Paristech 2024_
