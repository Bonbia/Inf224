#ifndef FILM_H
#define FILM_H

#include "Video.h"
#include <memory>
class MediaManager; // forward declaration

class Film : public Video
{
private:
    int *chapitres = nullptr;
    int nbChapitres = 0;

protected:
    // Protected constructors to force creation via MediaManager
    Film() : Video(), chapitres(nullptr), nbChapitres(0) {}

    Film(const std::string &nom, const std::string &nomFichier, int duree) : Video(nom, nomFichier, duree),
                                                                             chapitres(nullptr),
                                                                             nbChapitres(0)
    {
    }

public:
    virtual ~Film()
    {
        delete[] chapitres;
    }
    // Copie profonde
    Film(const Film &from) : Video(from)
    {
        nbChapitres = from.nbChapitres;
        if (from.chapitres && nbChapitres > 0)
        {
            chapitres = new int[nbChapitres];
            for (int i = 0; i < nbChapitres; ++i)
            {
                chapitres[i] = from.chapitres[i];
            }
        }
        else
        {
            chapitres = nullptr;
        }
    }

    // 3. Opérateur d'affectation : gère le nettoyage et la nouvelle copie
    Film &operator=(const Film &from)
    {
        if (this != &from)
        {                           // Protection contre l'auto-affectation (f = f)
            Video::operator=(from); // Copie la partie Video

            delete[] chapitres; // Nettoyage de l'ancienne mémoire

            nbChapitres = from.nbChapitres;
            if (from.chapitres && nbChapitres > 0)
            {
                chapitres = new int[nbChapitres];
                for (int i = 0; i < nbChapitres; ++i)
                {
                    chapitres[i] = from.chapitres[i];
                }
            }
            else
            {
                chapitres = nullptr;
            }
        }
        return *this;
    }

    // --- MODIFIEURS/ACCESSEURS ---

    void setChapitres(const int *newChapitres, int newNbChapitres)
    {
        delete[] chapitres; // On libère l'ancien tableau
        nbChapitres = newNbChapitres;

        if (nbChapitres > 0 && newChapitres != nullptr)
        {
            chapitres = new int[nbChapitres];
            for (int i = 0; i < nbChapitres; ++i)
            {
                chapitres[i] = newChapitres[i];
            }
        }
        else
        {
            chapitres = nullptr;
            nbChapitres = 0;
        }
    }

    int getNbChapitres() const { return nbChapitres; }

    const int *getChapitres() const { return chapitres; }

    // Affichage (redéfinition de affiche)
    void affiche(std::ostream &s) const
    { // Override ???
        Video::affiche(s);
        s << " | Chapitres : "; // Affichage initial du titre
        if (nbChapitres > 0)
        {
            for (int i = 0; i < nbChapitres; ++i)
            {
                s << chapitres[i] << "s"; // Ajout de la durée et de l'unité

                // Logique pour la virgule traînante
                if (i < nbChapitres - 1)
                {
                    s << ", ";
                }
            }
        }
        else
        {
            s << "Aucun";
        }
    }

    friend class MediaManager;
};

#endif // FILM_H