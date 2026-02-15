/**
 * @file Photo.cpp
 * @brief Implémentation de la classe Photo
 *
 * Contient les définitions des méthodes pour gérer les photographies
 * avec leurs coordonnées GPS.
 */

#include "Photo.h"
#include <iostream>

/**
 * @brief Constructeur par défaut de Photo
 *
 * Initialise une photo avec des coordonnées null (0.0, 0.0)
 */
Photo::Photo() : MultimediaObject(), latitude(0.0), longitude(0.0) {}

/**
 * @brief Destructeur de Photo
 */
Photo::~Photo() {}

/**
 * @brief Retourne la latitude de la photo
 * @return La latitude en degrés
 */
double Photo::getLatitude() const { return latitude; }

/**
 * @brief Retourne la longitude de la photo
 * @return La longitude en degrés
 */
double Photo::getLongitude() const { return longitude; }

/**
 * @brief Modifie la latitude
 * @param lat Nouvelle latitude en degrés
 */
void Photo::setLatitude(double lat) { latitude = lat; }

/**
 * @brief Modifie la longitude
 * @param lon Nouvelle longitude en degrés
 */
void Photo::setLongitude(double lon) { longitude = lon; }

/**
 * @brief Affiche les informations complètes de la photo
 *
 * Affiche le nom, le fichier et les coordonnées GPS
 *
 * @param os Flux de sortie où afficher les informations
 */
void Photo::affiche(std::ostream &os) const
{
    MultimediaObject::affiche(os);
    os << " | Latitude: " << latitude << " | Longitude: " << longitude;
}
