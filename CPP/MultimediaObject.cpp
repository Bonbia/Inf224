/**
 * @file MultimediaObject.cpp
 * @brief Implémentation de la classe MultimediaObject
 *
 * Contient les définitions des méthodes de la classe de base MultimediaObject
 */

#include "MultimediaObject.h"

/**
 * @brief Constructeur par défaut de MultimediaObject
 *
 * Initialise les attributs nom et nomFichier avec des valeurs vides
 */
MultimediaObject::MultimediaObject() : nom(""), nomFichier("") {}

/**
 * @brief Constructeur paramétré de MultimediaObject
 *
 * @param nom Nom unique de l'objet multimédia
 * @param nomFichier Chemin vers le fichier multimédia
 */
MultimediaObject::MultimediaObject(const std::string &nom, const std::string &nomFichier) : nom(nom), nomFichier(nomFichier) {}

/**
 * @brief Destructeur de MultimediaObject
 *
 * Affiche un message de destruction pour tracer le cycle de vie de l'objet
 */
MultimediaObject::~MultimediaObject()
{
    std::cout << "Objet " << nom << " detruit." << std::endl;
}

/**
 * @brief Retourne le nom de l'objet
 *
 * @return Référence constante au nom de l'objet
 */
std::string MultimediaObject::getNom() const
{
    return nom;
}

/**
 * @brief Retourne le chemin du fichier multimédia
 *
 * @return Référence constante au chemin du fichier
 */
std::string MultimediaObject::getNomFichier() const
{
    return nomFichier;
}

/**
 * @brief Modifie le nom de l'objet
 *
 * @param newNom Nouveau nom à attribuer à l'objet
 */
void MultimediaObject::setNom(const std::string newNom)
{
    nom = newNom;
}

/**
 * @brief Modifie le chemin du fichier multimédia
 *
 * @param newNomFichier Nouveau chemin du fichier
 */
void MultimediaObject::setNomFichier(const std::string newNomFichier)
{
    nomFichier = newNomFichier;
}

/**
 * @brief Affiche les informations de base de l'objet
 *
 * Affiche le nom et le chemin du fichier dans le flux de sortie fourni
 *
 * @param os Flux de sortie (habituellement std::cout ou un fichier)
 */
void MultimediaObject::affiche(std::ostream &os) const
{
    os << "Nom : " << nom << " | Fichier : " << nomFichier;
}
void MultimediaObject::jouer(std::ostream &out) const
{
}