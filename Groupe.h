#ifndef GROUPE_H
#define GROUPE_H

#include <iostream>
#include <list>
#include <string>
#include "MultimediaObject.h"
class MediaManager; // forward declaration

class Groupe : public std::list<MultimediaPtr>
{ // Utilisation du smart pointer
private:
    std::string nom;

public:
    using GroupPtr = std::shared_ptr<Groupe>;

protected:
    Groupe(std::string nom) : nom(nom) {}
    friend class MediaManager;

    // Accesseur pour le nom
    std::string getNom() const { return nom; }

    // Méthode d'affichage
    void affiche(std::ostream &os) const
    {
        os << "Groupe : " << nom << std::endl;
        // On parcourt la liste (this est lui-même la liste)
        for (auto const &obj : *this)
        {
            obj->affiche(os);
            os << std::endl;
        }
    }
};
using GroupePtr = std::shared_ptr<Groupe>;

#endif