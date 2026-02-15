/**
 * @file server.cpp
 * @brief Serveur TCP pour la gestion des requêtes multimédias
 * @author Eric Lecolinet - Telecom ParisTech
 * @date 2016-2024
 *
 * Serveur C++ qui écoute les requêtes des clients et les traite à l'aide
 * du gestionnaire multimédia. Supporte les commandes SEARCH, PLAY et QUIT.
 */

#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "tcpserver.h"
#include "MediaManager.h"

/**
 * @brief Port d'écoute du serveur
 */
const int PORT = 3331;

/**
 * @brief Point d'entrée du serveur
 *
 * Crée un gestionnaire multimédia, initialise des objets de test,
 * puis démarre le serveur TCP pour écouter les requêtes des clients.
 *
 * Commandes supportées :
 * - SEARCH <nom> : affiche les informations d'un objet
 * - PLAY <nom> : joue un objet multimédia
 * - QUIT : arriv an ferme le serveur
 *
 * @param argc Nombre d'arguments en ligne de commande (non utilisé)
 * @param argv Arguments en ligne de commande (non utilisés)
 *
 * @return 0 en cas de succès, 1 en cas d'erreur au démarrage
 */
int main(int argc, char *argv[])
{

    /**
     * Création du gestionnaire multimédia avec des objets de test
     */
    auto myManager = std::make_shared<MediaManager>();
    myManager->createPhoto("Photo1", "montsouris.jpg", 48.8, 2.3);
    myManager->createVideo("Video1", "video.mp4", 120);

    /**
     * Création et démarrage du serveur TCP
     *
     * La fonction lambda traite chaque requête reçue :
     * - Analyse la commande et son paramètre
     * - Appelle la méthode appropriée du gestionnaire
     * - Capture la sortie dans un stringstream
     * - Retourne true pour garder la connexion ouverte, false pour la fermer
     */
    auto *server = new TCPServer([&](std::string const &request, std::string &response)
                                 {
        
        /**
         * Diagnostic : affiche chaque requête reçue
         */
        std::cout << "Requête reçue: " << request << std::endl;

        /**
         * Analyse de la commande
         * Format : "COMMANDE paramètre"
         * Exemple : "SEARCH Photo1", "PLAY Video1"
         */
        std::stringstream ss(request);
        std::string command, name;
        ss >> command >> name; // Découpe "SEARCH nom" ou "PLAY nom"

        std::stringstream resStream;

        /**
         * Traitement des commandes SEARCH et PLAY
         */
        if (command == "SEARCH") {
            // On utilise une stringstream pour capturer l'affichage
            myManager->displayObject(name, resStream); 
            response = resStream.str();
            
        } 
        else if (command == "PLAY") {
        myManager->playObject(name, resStream);
        response = resStream.str();
        }
        else if (command == "QUIT") {
        response = "Closing server...";
        /**
         * Retourner false ferme la connexion et arrête le serveur
         */
        return false;
        }
        else {
            response = "Unknown command: " + command;
        }

        /**
         * Nettoyage de la réponse : éliminer les caractères spéciaux
         * qui pourraient briser le protocole texte
         */
        std::replace(response.begin(), response.end(), '\n', ' ');
        std::replace(response.begin(), response.end(), '\r', ' ');

        /**
         * Garder la connexion ouverte pour d'autres requêtes
         */
        return true; });

    /**
     * Démarrage du serveur
     */
    std::cout << "Starting Server on port " << PORT << std::endl;
    int status = server->run(PORT);
    if (status < 0)
    {
        std::cerr << "Could not start Server on port " << PORT << std::endl;
        return 1;
    }

    return 0;
}
