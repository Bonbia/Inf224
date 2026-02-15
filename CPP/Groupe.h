/**
 * @file Groupe.h
 * @brief Classe représentant un groupe de objets multimédias
 * @author Telecom Paristech
 * @date 2018-2024
 *
 * Définit la classe Groupe qui hérite de std::list pour stocker
 * une collection d'objets multimédias avec un nom.
 */

#ifndef GROUPE_H
#define GROUPE_H

#include <iostream>
#include <list>
#include <string>
#include "MultimediaObject.h"
class MediaManager; // forward declaration

/**
 * @class Groupe
 * @brief Classe représentant un groupe nommé d'objets multimédias
 *
 * Cette classe hérite de std::list pour stocker une collection d'objets multimédias.
 * Elle fournit un nom au groupe et des méthodes pour afficher tous les objets du groupe.
 *
 * @note Utilise des pointeurs intelligents (shared_ptr) pour la gestion automatique de la mémoire
 */
class Groupe : public std::list<MultimediaPtr>
{ // Utilisation du smart pointer
private:
    /**
     * @brief Nom unique du groupe
     */
    std::string nom;

public:
    /**
     * @typedef GroupPtr
     * @brief Alias pour un pointeur intelligent partagé vers un groupe
     */
    using GroupPtr = std::shared_ptr<Groupe>;

protected:
    /**
     * @brief Constructeur protégé
     *
     * Initialise un groupe vide avec un nom.
     * Ce constructeur est protégé pour forcer l'utilisation de MediaManager::createGroupe()
     *
     * @param nom Le nom unique du groupe
     */
    Groupe(std::string nom) : nom(nom) {}

    friend class MediaManager;

    /**
     * @brief Accesseur pour obtenir le nom du groupe
     *
     * @return Le nom du groupe
     */
    std::string getNom() const { return nom; }

    /**
     * @brief Affiche tous les objets du groupe
     *
     * Affiche le nom du groupe suivi de la liste de tous les objets qu'il contient.
     * Appelle la méthode affiche() de chaque objet.
     *
     * @param os Flux de sortie où afficher les informations
     */
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

/**
 * @typedef GroupePtr
 * @brief Alias pour un pointeur intelligent partagé vers un groupe
 */
using GroupePtr = std::shared_ptr<Groupe>;

#endif