/**
 * @file Video.h
 * @brief Classe représentant une vidéo avec durée
 * @author Telecom Paristech
 * @date 2018-2024
 *
 * Définit la classe Video qui hérite de MultimediaObject et ajoute
 * les propriétés spécifiques aux vidéos (durée).
 */

#ifndef VIDEO_H
#define VIDEO_H

#include "MultimediaObject.h"

class MediaManager; // forward declaration

/**
 * @class Video
 * @brief Classe représentant une vidéo avec durée
 *
 * Cette classe étend MultimediaObject pour ajouter la durée de la vidéo.
 * Elle permet de jouer une vidéo et de consulter sa durée.
 */
class Video : public MultimediaObject
{
private:
    /**
     * @brief Durée de la vidéo en secondes
     */
    int Duree;

public:
    /**
     * @brief Constructeur par défaut
     *
     * Crée une vidéo avec des valeurs par défaut
     */
    Video();

    /**
     * @brief Destructeur
     */
    ~Video();

    /**
     * @brief Récupère la durée de la vidéo
     *
     * @return La durée en secondes
     */
    double getDuree() const;

    /**
     * @brief Modifie la durée de la vidéo
     *
     * @param Duree La nouvelle durée en secondes
     */
    void setDuree(double Duree);

    /**
     * @brief Affiche les informations complètes de la vidéo
     *
     * Affiche le nom, le fichier et la durée
     *
     * @param os Flux de sortie où afficher les informations
     */
    void affiche(std::ostream &os) const;

    // Play
    void jouer(std::ostream &out = std::cout) const override
    {
        out << "Playing video: " << getNomFichier() << " (Duration: " << Duree << "s)" << std::endl;
        std::string commande = "explorer.exe " + getNomFichier() + " &";
        system(commande.data());
    }

protected:
    Video(const std::string &nom, const std::string &nomFichier, int Duree) : MultimediaObject(nom, nomFichier), Duree(Duree) {}

    friend class MediaManager;
};

#endif // VIDEO_H