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

class MediaManager
{
private:
    std::map<std::string, MultimediaPtr> objects;
    std::map<std::string, GroupePtr> groups;

public:
    MediaManager() = default;

    // Creation methods
    std::shared_ptr<Photo> createPhoto(const std::string &name, const std::string &filename, double lat, double lon);
    std::shared_ptr<Video> createVideo(const std::string &name, const std::string &filename, int duree);
    std::shared_ptr<Film> createFilm(const std::string &name, const std::string &filename, int duree);
    GroupePtr createGroupe(const std::string &name);

    // Lookup / display
    void displayObject(const std::string &name, std::ostream &out = std::cout) const;
    void displayGroupe(const std::string &name, std::ostream &out = std::cout) const;

    // Play
    void playObject(const std::string &name, std::ostream &out = std::cout) const;    
    // Remove
    bool removeObject(const std::string &name);
    bool removeGroupe(const std::string &name);
};

#endif // MEDIAMANAGER_H
