#ifndef MULTIMEDIAOBJECT_H
#define MULTIMEDIAOBJECT_H

#include <string>   // Pour std::string
#include <iostream> // Pour std::ostream
#include <memory>

class MultimediaObject; // Déclaration anticipée
using MultimediaPtr = std::shared_ptr<MultimediaObject>;

class MultimediaObject
{
private:
    std::string nom;
    std::string nomFichier;

public:
    using MultimediaPtr = std::shared_ptr<MultimediaObject>;

    // Constructeurs
    MultimediaObject();
    MultimediaObject(const std::string &nom, const std::string &nomFichier);

    // Getter
    std::string getNom() const;
    std::string getNomFichier() const;

    // Setter
    void setNom(const std::string nom);
    void setNomFichier(const std::string nomFichier);

    // Destructeur
    virtual ~MultimediaObject();

    // Affichage
    void affiche(std::ostream &os) const;

    // Play
    virtual void jouer() const = 0;
};

#endif // MULTIMEDIAOBJECT_H