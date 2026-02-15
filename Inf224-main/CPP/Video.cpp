#include "Video.h"

Video::Video() : MultimediaObject(), Duree(0) {}

Video::~Video() {}

double Video::getDuree() const { return Duree; }

void Video::setDuree(double d) { Duree = static_cast<int>(d); }

void Video::affiche(std::ostream &os) const
{
    MultimediaObject::affiche(os);
    os << " | Duree: " << Duree << "s";
}
