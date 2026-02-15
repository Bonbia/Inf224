//
//  server.cpp
//  TP C++
//  Eric Lecolinet - Telecom ParisTech - 2016.
//

#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "tcpserver.h"
#include "MediaManager.h"

const int PORT = 3331;


int main(int argc, char* argv[])
{
    
    auto myManager = std::make_shared<MediaManager>();
    myManager->createPhoto("Photo1", "montsouris.jpg", 48.8, 2.3);
    myManager->createVideo("Video1", "video.mp4", 120);

    auto* server = new TCPServer([&](std::string const& request, std::string& response) {
        
        std::cout << "Requête reçue: " << request << std::endl;

        std::stringstream ss(request);
        std::string command, name;
        ss >> command >> name; // Découpe "SEARCH nom" ou "PLAY nom"

        std::stringstream resStream;

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
        return false; // Retourner false ferme la connexion/le serveur
        }
        else {
            response = "Unknown command: " + command;
        }

        // IMPORTANT : Nettoyer les '\n' et '\r' car ils cassent le protocole
        std::replace(response.begin(), response.end(), '\n', ' ');
        std::replace(response.begin(), response.end(), '\r', ' ');

        return true; // Garder la connexion ouverte
    });

    std::cout << "Starting Server on port " << PORT << std::endl;
    int status = server->run(PORT);
    if (status < 0) {
        std::cerr << "Could not start Server on port " << PORT << std::endl;
        return 1;
    }

    return 0;
}
