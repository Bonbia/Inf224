// MultimediaObject.cpp
#include "MultimediaObject.h"

// Constructeur par défaut
MultimediaObject::MultimediaObject() : nom(""), nomFichier("") {}

// Constructeur avec arguments
MultimediaObject::MultimediaObject(const std::string &nom, const std::string &nomFichier) : nom(nom), nomFichier(nomFichier) {}

// Destructeur
MultimediaObject::~MultimediaObject() {
    std::cout << "Objet " << nom << " detruit." << std::endl;
}

// Getter
std::string MultimediaObject::getNom() const
{
    return nom;
}

std::string MultimediaObject::getNomFichier() const
{
    return nomFichier;
}

// Setters
void MultimediaObject::setNom(const std::string newNom)
{
    nom = newNom;
}

void MultimediaObject::setNomFichier(const std::string newNomFichier)
{
    nomFichier = newNomFichier;
}

// Affichage
void MultimediaObject::affiche(std::ostream &os) const
{
    os << "Nom : " << nom << " | Fichier : " << nomFichier;
}
void MultimediaObject::jouer(std::ostream &out) const
{
}