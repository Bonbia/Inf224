

# Introduction
 Ce projet implémente une set-top box multimédia avec un serveur en C++ et une interface de télécommande en Java Swing. 
Voici les réponses aux questions théoriques posées dans le sujet du TP.

# Partie 1 : C++ / Objet

## 4e Étape : Photos et vidéos

**Q : Comment appelle-t-on ce type de méthode et comment faut-il les déclarer ?**

R : La méthode `play()` doit être déclarée comme une **méthode virtuelle pure**.
En C++, cela se déclare avec `= 0` à la fin de la signature dans la classe de base (ex: `virtual void play() const = 0;`). Cela rend la classe de base **abstraite**.

**Q : Si vous avez fait ce qui précède comme demandé, il ne sera plus possible d'instancer des objets de la classe de base. Pourquoi ?**

R : Une classe contenant au moins une méthode virtuelle pure est considérée comme une **classe abstraite**.On ne peut pas instancier une classe abstraite car elle est incomplète.

## 5e Étape : Traitement uniforme

**Q : Quelle est la propriété caractéristique de l'orienté objet qui permet de faire cela ?**

R : C'est le **polymorphisme**, qui permet de traiter de manière uniforme une liste comprenant à la fois des photos et des vidéos.

**Q : Qu'est-il spécifiquement nécessaire de faire dans le cas du C++ ?**

R : En C++, il est nécessaire que les méthodes soient déclarées `virtual` dans la classe de base et que l'on manipule les objets via des pointeurs ou des références.

**Q : Quel est le type des éléments du tableau : le tableau doit-il contenir des objets ou des pointeurs vers ces objets ? Pourquoi ? Comparer à Java.**

R : Le tableau doit contenir des **pointeurs vers ces objets**.
Si on stockait les objets par valeur, on subirait le phénomène de "slicing" (troncature), perdant le polymorphisme.
En Java, ce problème ne se pose pas de la même manière car les variables d'objets sont des références (ce qui s'apparente à des pointeurs gérés automatiquement).

## 6e Étape : Films et tableaux

**Q : Que doit retourner l'accesseur au tableau de durées ?**

R : L'accesseur ne doit pas permettre à l'appelant de modifier le contenu du tableau (ce qui romprait l'encapsulation). Il doit donc retourner une copie ou un pointeur constant (`const`).

**Q : Comment le modifieur doit-il stocker le tableau ?**

R : L'objet `Film` doit assurer la pérennité de ses données. Le modifieur doit donc effectuer une copie profonde du tableau passé en argument, car ce dernier pourrait être détruit ou modifié ailleurs.

## 7e Étape : Destruction et copie des objets

**Q : Parmi les classes précédemment écrites quelles sont celles qu'il faut modifier afin qu'il n'y ait pas de fuite mémoire quand on détruit les objets ?**

R : Il faut modifier la classe `Film`. Puisque les tableaux en C/C++ ne sont pas gérés automatiquement, il faut supprimer explicitement le tableau de durées dans le destructeur

**Q : La copie d'objet peut également poser problème quand ils ont des variables d'instance qui sont des pointeurs. Quel est le problème et quelles sont les solutions ?**

R : La copie par défaut copie uniquement l'adresse du pointeur (copie superficielle). Si l'objet original est détruit, la copie pointe vers une mémoire invalide.
Les solutions sont d'implémenter une copie profonde (réallocation) ou d'interdire la copie (via `delete` sur le constructeur de copie).

## 8e Étape : Créer des groupes

**Q : On rappelle aussi que la liste d'objets doit en fait être une liste de pointeurs d'objets. Pourquoi ? Comparer à Java.**

R : Une liste d'objets entraînerait la copie des objets (lourd) et le slicing (perte du type réel). Une liste de pointeurs est plus légère et préserve le polymorphisme.
En Java, les listes stockent naturellement des références.

## 10e Étape : Gestion cohérente des données

**Q : Comment peut-on l'interdire, afin que seule la classe servant à manipuler les objets puisse en créer de nouveaux ?**

R : Pour empêcher de créer un objet avec `new` directement (qui n'appartiendrait à aucune table), on peut rendre les constructeurs privés ou protégés et déclarer la classe de gestion comme `friend`.

# Partie 2 : Java / Swing

## 1ere Étape : Fenêtre principale

**Q : Lancez votre programme, cliquez plusieurs fois sur les deux premiers bouton, retaillez la fenêtre. Que constate-t-on ?**

R : On constate que sans ascenseurs, le texte ajouté disparaît ou n'est plus visible quand il dépasse la taille de la zone.
Il faut mettre le `JTextArea` dans un `JScrollPane` pour le rendre réellement utilisable.