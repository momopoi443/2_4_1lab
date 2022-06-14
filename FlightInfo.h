
#ifndef INC_2_4_1LAB_FLIGHTINFO_H
#define INC_2_4_1LAB_FLIGHTINFO_H

#include <iostream>

class Plane {
public:
    unsigned int typeId;
    unsigned int availablePlaces;
    unsigned int ticketPrice;
};

class Flight {
public:
    char date[11];
    unsigned int id;
};

class FlightInfo {
public:
    Plane plane{};
    Flight flight{};

    friend std::ostream& operator<< (std::ostream &out, const FlightInfo &flightInfo);

    friend std::istream& operator>> (std::istream &in, FlightInfo &flightInfo);

    FlightInfo();
};

#endif
