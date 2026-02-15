/**
 * @file MultimediaObject.h
 * @brief Classe abstraite de base pour tous les objets multimédias
 * @author Telecom Paristech
 * @date 2018-2024
 *
 * Définit la classe de base abstraite MultimediaObject qui sert de fondation
 * pour tous les types d'objets multimédias (Photos, Vidéos, Films, etc.).
 */

#ifndef MULTIMEDIAOBJECT_H
#define MULTIMEDIAOBJECT_H

#include <string>   // Pour std::string
#include <iostream> // Pour std::ostream
#include <memory>

class MultimediaObject; // Déclaration anticipée
/**
 * @typedef MultimediaPtr
 * @brief Alias pour un pointeur intelligent partagé vers un MultimediaObject
 */
using MultimediaPtr = std::shared_ptr<MultimediaObject>;

/**
 * @class MultimediaObject
 * @brief Classe abstraite et polymorphe pour représenter un objet multimédia générique
 *
 * Cette classe abstraite fournit l'interface commune à tous les objets multimédias.
 * Elle définit les propriétés de base (nom et chemin du fichier) et les opérations
 * essentielles (affichage et lecture).
 *
 * @note Cette classe ne peut pas être instanciée directement (classe abstraite).
 *       Utilisez les classes dérivées : Photo, Video ou Film.
 *
 * @see Photo
 * @see Video
 * @see Film
 */
class MultimediaObject
{
private:
    /**
     * @brief Nom unique de l'objet multimédia
     */
    std::string nom;

    /**
     * @brief Chemin d'accès au fichier multimédia
     */
    std::string nomFichier;

public:
    /**
     * @typedef MultimediaPtr
     * @brief Alias pour un pointeur intelligent partagé vers cet objet
     */
    using MultimediaPtr = std::shared_ptr<MultimediaObject>;

    /**
     * @brief Constructeur par défaut
     *
     * Initialise un objet avec des valeurs vides
     */
    MultimediaObject();

    /**
     * @brief Constructeur paramétré
     *
     * @param nom Le nom unique identifiant cet objet multimédia
     * @param nomFichier Le chemin vers le fichier multimédia associé
     */
    MultimediaObject(const std::string &nom, const std::string &nomFichier);

    /**
     * @brief Récupère le nom de l'objet
     *
     * @return std::string Le nom unique de cet objet
     */
    std::string getNom() const;

    /**
     * @brief Récupère le chemin du fichier multimédia
     *
     * @return std::string Le chemin d'accès au fichier
     */
    std::string getNomFichier() const;

    /**
     * @brief Modifie le nom de l'objet
     *
     * @param nom Le nouveau nom à assigner
     */
    void setNom(const std::string nom);

    /**
     * @brief Modifie le chemin du fichier multimédia
     *
     * @param nomFichier Le nouveau chemin du fichier
     */
    void setNomFichier(const std::string nomFichier);

    /**
     * @brief Destructeur virtuel
     *
     * Affiche un message de trace pour suivre la destruction de l'objet.
     * La nature virtuelle permet une destruction polymorphe correcte.
     */
    virtual ~MultimediaObject();

    /**
     * @brief Affiche les informations de base de l'objet
     *
     * Affiche le nom et le chemin du fichier sur le flux de sortie fourni.
     * Les classes dérivées peuvent surcharger cette méthode pour ajouter
     * des informations spécifiques.
     *
     * @param os Le flux de sortie (habituellement std::cout ou un fichier)
     */
    void affiche(std::ostream &os) const;

    /**
     * @brief Joue/lit l'objet multimédia (méthode abstraite)
     *
     * Méthode virtuelle pure qui doit être implémentée par les classes dérivées.
     * Elle gère la lecture/exécution du media selon son type.
     *
     * @param out Le flux de sortie pour les messages (par défaut: std::cout)
     *
     * @note Chaque classe dérivée doit implémenter cette méthode
     * @note Exemple pour Photo: ouvre l'image avec le visualiseur par défaut
     * @note Exemple pour Video: ouvre la vidéo avec le lecteur par défaut
     */
    virtual void jouer(std::ostream &out = std::cout) const = 0;
};

#endif // MULTIMEDIAOBJECT_H