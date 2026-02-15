/**
 * @file Photo.h
 * @brief Classe Photo pour gérer les photographies avec coordonnées GPS
 * @author Telecom Paristech
 * @date 2018-2024
 *
 * Définit la classe Photo qui hérite de MultimediaObject et ajoute
 * les propriétés spécifiques aux photographs (latitude, longitude).
 */

#ifndef PHOTO_H
#define PHOTO_H

#include "MultimediaObject.h"
class MediaManager; // forward declaration for friend

/**
 * @class Photo
 * @brief Classe représentant une photographie avec coordonnées GPS
 *
 * Cette classe étend MultimediaObject pour ajouter les coordonnées
 * géographiques (latitude/longitude) d'une photograph.
 * Elle permet d'ouvrir et d'afficher une photograph avec ses métadonnées.
 */
class Photo : public MultimediaObject
{
private:
    /**
     * @brief Latitude du lieu où la photograph a été prise
     */
    double latitude;

    /**
     * @brief Longitude du lieu où la photograph a été prise
     */
    double longitude;

public:
    /**
     * @brief Constructeur par défaut
     *
     * Crée une photographie avec des valeurs par défaut
     */
    Photo();

    /**
     * @brief Destructeur
     */
    ~Photo();

    /**
     * @brief Récupère la latitude de la photograph
     *
     * @return La latitude en degrés
     */
    double getLatitude() const;

    /**
     * @brief Récupère la longitude de la photograph
     *
     * @return La longitude en degrés
     */
    double getLongitude() const;

    /**
     * @brief Modifie la latitude de la photograph
     *
     * @param latitude La nouvelle latitude en degrés
     */
    void setLatitude(double latitude);

    /**
     * @brief Modifie la longitude de la photograph
     *
     * @param longitude La nouvelle longitude en degrés
     */
    void setLongitude(double longitude);

    /**
     * @brief Affiche les informations complètes de la photograph
     *
     * Affiche le nom, le fichier et les coordonnées GPS
     *
     * @param os Flux de sortie où afficher les informations
     */
    void affiche(std::ostream &os) const;

    // Play
    void jouer(std::ostream &out = std::cout) const override
    {
        out << "Opening photo: " << getNomFichier() << std::endl;
        std::string commande = "explorer.exe " + getNomFichier() + " &"; // Commande pour ouvrir la photo avec l'application par défaut sur Windows mettre un imagej ou un xdg-open
        system(commande.data());
    }

protected:
    // Protected constructor: creation only via MediaManager
    Photo(const std::string &nom, const std::string &nomFichier, double lat, double lon) : MultimediaObject(nom, nomFichier), latitude(lat), longitude(lon) {}

    friend class MediaManager;
};

#endif // PHOTO_H