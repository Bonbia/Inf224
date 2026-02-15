/**
 * @file main.cpp
 * @brief Programme principal de démonstration du gestionnaire multimédia
 * @author Telecom Paristech
 * @date 2018-2024
 *
 * Ce programme démontre l'utilisation du système de gestion multimédia :
 * - Création de photos avec coordonnées GPS
 * - Création de vidéos avec durée
 * - Création de groupes pour organiser les objets
 * - Affichage et lecture des objets
 */

#include <iostream>
#include "Photo.h"
#include "Video.h"
#include "MediaManager.h"
#include <string>
#include <vector>
#include "Groupe.h"
#include <memory>
#include "MultimediaObject.h"
using namespace std;

/**
 * @brief Point d'entrée du programme
 *
 * Crée un gestionnaire multimédia et démontre ses fonctionnalités :
 * 1. Création d'une photographie
 * 2. Création d'une vidéo
 * 3. Création d'un groupe
 * 4. Ajout des objets au groupe
 * 5. Affichage des objets
 * 6. Lecture des objets
 *
 * @return 0 en cas de succès
 *
 * @note Les destructeurs s'exécutent automatiquement à la fin du programme
 */
int main()
{
    MediaManager manager;

    /// Création d'une photographie avec coordonnées GPS
    auto p1 = manager.createPhoto("Photo1", "montsouris.jpg", 48.8, 2.3);

    /// Création d'une vidéo avec durée de 120 secondes
    auto v1 = manager.createVideo("Video1", "video.mp4", 120);

    /// Création d'un groupe pour organiser les objets
    auto monGroupe = manager.createGroupe("Mes Medias");

    /// Ajout des objets au groupe
    monGroupe->push_back(p1);
    monGroupe->push_back(v1);

    // === Affichage de test ===
    manager.displayObject("Photo1");
    manager.displayObject("Video1");
    manager.displayGroupe("Mes Medias");

    // === Lecture des objets ===
    manager.playObject("Photo1");

    /// Tests de gestion mémoire : libération d'un objet
    p1.reset();

    return 0; // Les destructeurs vont s'appeler ici et afficher les messages
}