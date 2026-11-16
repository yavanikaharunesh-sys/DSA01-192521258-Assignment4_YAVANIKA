// Task 6 - Stage 5: rent, return (with late charge), list, add a new type
#include "Vehicles.h"
#include "ElectricBus.h"          // new type plugged in, nothing else edited

void listFleet(Vehicle* fleet[], int n) {
    for (int i = 0; i < n; ++i) fleet[i]->print();
}
bool rentVehicle(Vehicle* v) {
    if (v->isRented()) { cout << v->reg() << " already rented\n"; return false; }
    v->setRented(true);
    cout << "Rented   " << v->kind() << " " << v->reg() << "\n";
    return true;
}
void returnVehicle(Vehicle* v, int booked, int actual, double used) {
    int late = actual > booked ? actual - booked : 0;
    double bill = v->charge(booked, used) + v->lateFee(late);
    v->setRented(false);
    cout << "Returned " << v->kind() << " " << v->reg() << " booked=" << booked
         << " actual=" << actual << " late=" << late << " -> Rs. " << bill << "\n";
}

int main() {
    Vehicle* fleet[5] = {
        new Bicycle("BC-01", 100),
        new TwoWheeler("TN-22-A-1111", 400, 80, Date(1, 3, 2027)),
        new Car("TN-22-B-2222", 1500, 60, Date(15, 4, 2027), 5),
        new ElectricCar("TN-22-E-3333", 2000, 90, Date(10, 6, 2027), 5, 40),
        new ElectricBus("TN-22-EB-4444", 6000, 95, Date(20, 7, 2027), 30)   // new type
    };
    cout << "--- fleet ---\n";           listFleet(fleet, 5);
    cout << "--- renting every type ---\n";
    for (int i = 0; i < 5; ++i) rentVehicle(fleet[i]);
    rentVehicle(fleet[0]);                                  // already rented
    cout << "--- returns ---\n";
    returnVehicle(fleet[0], 2, 2, 0);       // bicycle, on time
    returnVehicle(fleet[1], 3, 3, 5);       // two-wheeler, 5 litres
    returnVehicle(fleet[2], 2, 4, 10);      // car, 2 days LATE
    returnVehicle(fleet[3], 2, 2, 25);      // electric car, 25 kWh
    returnVehicle(fleet[4], 1, 2, 60);      // electric bus, 1 day LATE
    cout << "--- fleet after returns ---\n"; listFleet(fleet, 5);
    for (Vehicle* v : fleet) delete v;
}
