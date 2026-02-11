#ifndef PHOTO_H
#define PHOTO_H

#include "MultimediaObject.h"
class MediaManager; // forward declaration for friend

class Photo : public MultimediaObject
{
private:
    double latitude;
    double longitude;

public:
    // Constructeurs
    Photo();
    ~Photo();
    // Getters
    // Getters
    double getLatitude() const;
    double getLongitude() const;
    // Setters
    void setLatitude(double latitude);
    void setLongitude(double longitude);
    // Destructeur
    // Affichage
    void affiche(std::ostream &os) const;

    // Play
    void jouer(std::ostream &out = std::cout) const override
    {
        out << "Opening photo: " << getNomFichier() << std::endl;
        std::string commande = "explorer.exe " + getNomFichier() + " &";   // Commande pour ouvrir la photo avec l'application par défaut sur Windows mettre un imagej ou un xdg-open
        system(commande.data());
    }

protected:
    // Protected constructor: creation only via MediaManager
    Photo(const std::string &nom, const std::string &nomFichier, double lat, double lon) : MultimediaObject(nom, nomFichier), latitude(lat), longitude(lon) {}

    friend class MediaManager;
};

#endif // PHOTO_H