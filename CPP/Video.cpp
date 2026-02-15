/**
 * @file Video.cpp
 * @brief Implémentation de la classe Video
 *
 * Contient les définitions des méthodes pour gérer les vidéos
 * et leur durée.
 */

#include "Video.h"

/**
 * @brief Constructeur par défaut de Video
 *
 * Initialise une vidéo avec une durée de 0 secondes
 */
Video::Video() : MultimediaObject(), Duree(0) {}

/**
 * @brief Destructeur de Video
 */
Video::~Video() {}

/**
 * @brief Retourne la durée de la vidéo
 * @return La durée en secondes
 */
double Video::getDuree() const { return Duree; }

/**
 * @brief Modifie la durée de la vidéo
 * @param d Nouvelle durée en secondes
 */
void Video::setDuree(double d) { Duree = static_cast<int>(d); }

/**
 * @brief Affiche les informations complètes de la vidéo
 *
 * Affiche le nom, le fichier et la durée
 *
 * @param os Flux de sortie où afficher les informations
 */
void Video::affiche(std::ostream &os) const
{
    MultimediaObject::affiche(os);
    os << " | Duree: " << Duree << "s";
}
