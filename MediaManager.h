/**
 * @file MediaManager.h
 * @brief Gestionnaire centralisé pour tous les objets multimédias
 * @author Telecom Paristech
 * @date 2018-2024
 *
 * Définit la classe MediaManager qui centralise la création, la gestion
 * et l'accès à tous les objets multimédias et groupes du système.
 */

#ifndef MEDIAMANAGER_H
#define MEDIAMANAGER_H

#include <map>
#include <string>
#include <memory>
#include <iostream>

#include "MultimediaObject.h"
#include "Photo.h"
#include "Video.h"
#include "Film.h"
#include "Groupe.h"

/**
 * @class MediaManager
 * @brief Gestionnaire centralisé pour tous les objets et groupes multimédias
 *
 * Cette classe utilise le pattern Factory et centralise :
 * - La création des objets multimédias (Photo, Video, Film)
 * - La création des groupes
 * - L'accès aux objets par leur nom
 * - La lecture/affichage des objets
 *
 * @note Utilise des maps pour indexer les objets et groupes par nom
 * @note Utilise des pointeurs intelligents (shared_ptr) pour la RAII
 */
class MediaManager
{
private:
    /**
     * @brief Map stockant tous les objets multimédias indexés par leur nom
     */
    std::map<std::string, MultimediaPtr> objects;

    /**
     * @brief Map stockant tous les groupes indexés par leur nom
     */
    std::map<std::string, GroupePtr> groups;

public:
    /**
     * @brief Constructeur par défaut
     *
     * Initialise un gestionnaire vide
     */
    MediaManager() = default;

    // ========== Méthodes de création ==========

    /**
     * @brief Crée une nouvelle photographie et l'enregistre
     *
     * @param name Nom unique de la photographie
     * @param filename Chemin vers le fichier d'image
     * @param lat Latitude du lieu de prise de photo
     * @param lon Longitude du lieu de prise de photo
     *
     * @return Pointeur intelligent vers la photographie créée
     *
     * @note La photographie est automatiquement enregistrée dans la map objects
     */
    std::shared_ptr<Photo> createPhoto(const std::string &name, const std::string &filename, double lat, double lon);

    /**
     * @brief Crée une nouvelle vidéo et l'enregistre
     *
     * @param name Nom unique de la vidéo
     * @param filename Chemin vers le fichier vidéo
     * @param duree Durée de la vidéo en secondes
     *
     * @return Pointeur intelligent vers la vidéo créée
     *
     * @note La vidéo est automatiquement enregistrée dans la map objects
     */
    std::shared_ptr<Video> createVideo(const std::string &name, const std::string &filename, int duree);

    /**
     * @brief Crée un nouveau film et l'enregistre
     *
     * @param name Nom unique du film
     * @param filename Chemin vers le fichier vidéo du film
     * @param duree Durée du film en secondes
     *
     * @return Pointeur intelligent vers le film créé
     *
     * @note Le film est automatiquement enregistré dans la map objects
     */
    std::shared_ptr<Film> createFilm(const std::string &name, const std::string &filename, int duree);

    /**
     * @brief Crée un nouveau groupe et l'enregistre
     *
     * @param name Nom unique du groupe
     *
     * @return Pointeur intelligent vers le groupe créé
     *
     * @note Le groupe est automatiquement enregistré dans la map groups
     */
    GroupePtr createGroupe(const std::string &name);

    // ========== Méthodes de consultation/affichage ==========

    /**
     * @brief Affiche les informations d'un objet par son nom
     *
     * @param name Nom unique de l'objet à afficher
     * @param out Flux de sortie (par défaut: std::cout)
     *
     * @note Si l'objet n'existe pas, rien n'est affiché
     */
    void displayObject(const std::string &name, std::ostream &out = std::cout) const;

    /**
     * @brief Affiche tous les objets d'un groupe
     *
     * @param name Nom unique du groupe à afficher
     * @param out Flux de sortie (par défaut: std::cout)
     *
     * @note Si le groupe n'existe pas, rien n'est affiché
     */
    void displayGroupe(const std::string &name, std::ostream &out = std::cout) const;

    // ========== Méthodes de lecture ==========

    /**
     * @brief Joue un objet multimédia par son nom
     *
     * Appelle la méthode jouer() de l'objet pour le lancer
     *
     * @param name Nom unique de l'objet à jouer
     * @param out Flux de sortie pour les messages (par défaut: std::cout)
     *
     * @note Si l'objet n'existe pas, rien ne se passe
     */
    void playObject(const std::string &name, std::ostream &out = std::cout) const;

    // ========== Méthodes de suppression ==========

    /**
     * @brief Supprime un objet multimédia par son nom
     *
     * @param name Nom unique de l'objet à supprimer
     *
     * @return true si l'objet existait et a été supprimé, false sinon
     *
     * @note L'objet est également supprimé de tout groupe qui le contient
     */
    bool removeObject(const std::string &name);

    /**
     * @brief Supprime un groupe par son nom
     *
     * @param name Nom unique du groupe à supprimer
     *
     * @return true si le groupe existait et a été supprimé, false sinon
     *
     * @note Seul le groupe est supprimé, pas les objets qu'il contient
     */
    bool removeGroupe(const std::string &name);
};

#endif // MEDIAMANAGER_H
