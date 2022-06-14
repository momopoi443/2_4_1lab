
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>
#include "FlightInfo.h"

using namespace std;

void printMenu() {
    cout
    << "1. add" << endl
    << "2. print all" << endl
    << "3. edit flight" << endl
    << "4. delete flight" << endl
    << "5. list of flight with free places" << endl
    << "6. day flights info" << endl
    << "7. sort flights by ticket price" << endl
    << "8. exit" << endl;
}

bool isEmpty(std::fstream& file) {
    return file.peek() == std::ifstream::traits_type::eof();
}

size_t countElem(fstream& file) {
    file.seekg (0, std::fstream::end);
    size_t amount = file.tellg() / sizeof(FlightInfo);
    file.seekg (0);
    return amount;
}

bool compare(FlightInfo& a, FlightInfo& b) {
    if (strcmp(a.flight.date, b.flight.date) >= 0) {
        if (strcmp(a.flight.date, b.flight.date) == 0 && a.plane.ticketPrice <= b.plane.ticketPrice)
            return false;
        return true;
    } else {
        return false;
    }
}

void addFlight(char* path) {
    ofstream file(path, ios::app | ios::binary);
    FlightInfo toAdd;

    cin >> toAdd;

    file.write((char*)&toAdd, sizeof(FlightInfo));
    file.close();
}

void printAll(char* path) {

    fstream file(path, ios::in | ios::binary);

    if(isEmpty(file)) {
        cout << "The file is empty" << endl;
        return;
    }

    size_t elements = countElem(file);
    FlightInfo buff;

    for(int i = 0; i < elements; i++){
        file.read((char*)&buff, sizeof(FlightInfo));
        cout << i + 1 << ":" << endl << buff;
    }

    cout << endl;
    file.close();
}

void editFlight(char* path) {

    int index;
    cout << "Enter the number of flight: ";
    cin >> index;

    fstream file(path, ios::in | ios::binary);

    if (index > countElem(file) || index < 0) {
        cout << "No such element" << endl;
        return;
    }
    file.close();

    FlightInfo toEdit;
    cin >> toEdit;

    file.open(path, ios::out | ios::binary);
    file.seekp(sizeof(FlightInfo) * (index - 1));
    file.write((char*)&toEdit, sizeof(FlightInfo));
    file.close();
}

void deleteFlight(char* path) {

    int index;
    cout << "Enter the number of flight: " ;
    cin >> index;

    fstream fileFrom(path, ios::in | ios::binary);
    fstream fileTo("..\\resources\\buff.bin", ios::out | ios::binary);

    size_t size = countElem(fileFrom);
    if (index > size || index < 0) {
        cout << "No such element" << endl;
        return;
    }
    FlightInfo buff;

    for(int i = 0; i < size; i++) {
        fileFrom.read((char*)&buff, sizeof(FlightInfo));

        if (i == index - 1)
            continue;

        fileTo.write((char*)&buff, sizeof(FlightInfo));
    }

    fileFrom.close();
    fileTo.close();

    remove(path);
    rename("..\\resources\\buff.bin", path);
}

void printFlightsWithFreeSeats(char* path) {
    fstream file(path, ios::in | ios::binary);

    if(isEmpty(file)) {
        cout << "The file is empty" << endl;
        return;
    }

    size_t size = countElem(file);
    FlightInfo buff;

    int j = 1;
    for(int i = 0; i < size; i++){
        file.read((char*)&buff, sizeof(FlightInfo));

        if(buff.plane.availablePlaces > 0) {
            cout << j << ":" << endl << buff;
            j++;
        }
    }
    cout << endl;
    file.close();
}

void printByDate(char* path) {

    char date[11];
    cout << "Enter date: ";
    getchar();
    cin.getline(date, 11);

    fstream file(path, ios::in | ios::binary);
    if(isEmpty(file)) {
        cout << "The file is empty" << endl;
        return;
    }

    size_t size = countElem(file);
    FlightInfo buff;

    int j = 1;
    for(int i = 0; i < size; i++){
        file.read((char*)&buff, sizeof(FlightInfo));

        if(strcmp(buff.flight.date, date) == 0) {
            cout << j << ":" << endl
            << "Plane type:" << buff.plane.typeId << endl
            << "ID:" << buff.flight.id << endl;
            j++;
        }
    }
    cout << endl;
    file.close();
}

void sortFlightsByPrice(char* path) {

    fstream file(path, ios::in | ios::binary);
    size_t size = countElem(file);
    vector<FlightInfo> buffVec(size);

    for(int i = 0; i < size; i++) {
        file.read((char*)&buffVec[i], sizeof(FlightInfo));
    }
    file.close();

    sort (buffVec.begin(), buffVec.end(), compare);

    file.open(path, ios::out | ios::binary);
    file.write((char*)buffVec.data(), buffVec.size() * sizeof(FlightInfo));
    file.close();
}


int main() {

    char path[] = "..\\resources\\FlightsInfo.bin";

    while (true) {

        printMenu();

        short choice;
        cout << "Choose:";
        cin >> choice;
        cout << endl;

        switch (choice)
        {
            case 1:
                addFlight(path);
                break;
            case 2:
                printAll(path);
                break;
            case 3:
                editFlight(path);
                break;
            case 4:
                deleteFlight(path);
                break;
            case 5:
                printFlightsWithFreeSeats(path);
                break;
            case 6:
                printByDate(path);
                break;
            case 7:
                sortFlightsByPrice(path);
                break;
            case 8:
                exit(0);
            default:
                cout << "No such command" << endl;
        }
    }
}
