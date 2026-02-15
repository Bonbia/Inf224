#include "Photo.h"
#include <iostream>

Photo::Photo() : MultimediaObject(), latitude(0.0), longitude(0.0) {}

Photo::~Photo() {}

double Photo::getLatitude() const { return latitude; }
double Photo::getLongitude() const { return longitude; }

void Photo::setLatitude(double lat) { latitude = lat; }
void Photo::setLongitude(double lon) { longitude = lon; }

void Photo::affiche(std::ostream &os) const
{
    MultimediaObject::affiche(os);
    os << " | Latitude: " << latitude << " | Longitude: " << longitude;
}
