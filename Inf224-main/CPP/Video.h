#ifndef VIDEO_H
#define VIDEO_H

#include "MultimediaObject.h"

class MediaManager; // forward declaration

class Video : public MultimediaObject
{
private:
    int Duree;

public:
    // Constructeurs
    Video();
    ~Video();
    // Getters
    double getDuree() const;

    // Setters
    void setDuree(double Duree);
    // Destructeur

    // Affichage
    void affiche(std::ostream &os) const;

    // Play
    void jouer(std::ostream &out = std::cout) const override
{
    out << "Playing video: " << getNomFichier() << " (Duration: " << Duree << "s)" << std::endl;
    std::string commande = "mpv"  + getNomFichier()+" &";
    system(commande.data());
    }

protected:
    Video(const std::string &nom, const std::string &nomFichier, int Duree) : MultimediaObject(nom, nomFichier), Duree(Duree) {}

    friend class MediaManager;
};

#endif // VIDEO_H