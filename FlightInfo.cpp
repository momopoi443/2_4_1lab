
#include "FlightInfo.h"

using namespace std;

std::ostream& operator<< (std::ostream &out, const FlightInfo &flightInfo) {

    out
            << "Date:" << flightInfo.flight.date << endl
            << "ID:" << flightInfo.flight.id << endl
            << "Plane type:" << flightInfo.plane.typeId << endl
            << "Available places:" << flightInfo.plane.availablePlaces << endl
            << "Ticket price:" << flightInfo.plane.ticketPrice << endl;

    return out;
}

std::istream& operator>> (std::istream& in, FlightInfo& flightInfo) {

    cout << "Date:";
    getchar();
    in.getline(flightInfo.flight.date, 11);
    cout << "ID:";
    in >> flightInfo.flight.id;
    cout << "Plane type:";
    in >> flightInfo.plane.typeId;
    cout << "Available places:";
    in >> flightInfo.plane.availablePlaces;
    cout << "Ticket price:";
    in >> flightInfo.plane.ticketPrice;

    return in;
}

FlightInfo::FlightInfo() {

    this->flight.date[0] = '0';
    this->flight.id = 0;
    this->plane.typeId = 0;
    this->plane.availablePlaces = 0;
    this->plane.ticketPrice = 0;
}

