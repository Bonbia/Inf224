//
// main.cpp
// Created on 21/10/2018
//

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

int main()
{
    MediaManager manager;

    auto p1 = manager.createPhoto("Photo1", "montsouris.jpg", 48.8, 2.3);
    auto v1 = manager.createVideo("Video1", "video.mp4", 120);

    auto monGroupe = manager.createGroupe("Mes Medias");
    monGroupe->push_back(p1);
    monGroupe->push_back(v1);

    // Affichage de test
    manager.displayObject("Photo1");
    manager.displayObject("Video1");
    manager.displayGroupe("Mes Medias");

    // Jouer la vidéo (exemple)
    manager.playObject("Photo1");

    p1.reset();

    return 0; // Les destructeurs vont s'appeler ici et afficher les messages
}