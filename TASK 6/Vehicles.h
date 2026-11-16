// Vehicles.h - Task 6 class hierarchy (existing classes - never edited again)
#pragma once
#include <iostream>
#include <string>
using namespace std;

class Date {                                  // member class (has-a)
    int d, m, y;
public:
    Date(int d, int m, int y) : d(d), m(m), y(y) {}
    string str() const { return to_string(d) + "/" + to_string(m) + "/" + to_string(y); }
};

class Vehicle {                               // ABSTRACT base class
protected:
    string regNo; double dailyRate; bool rented = false;
public:
    Vehicle(const string& r, double d) : regNo(r), dailyRate(d) {}
    virtual ~Vehicle() {}
    virtual double charge(int days, double used) const = 0;   // pure virtual
    virtual string kind() const = 0;
    virtual string details() const { return ""; }
    double lateFee(int lateDays) const { return lateDays * dailyRate * 1.5; }
    bool isRented() const { return rented; }
    void setRented(bool r) { rented = r; }
    const string& reg() const { return regNo; }
    void print() const {
        cout << kind() << " " << regNo << " Rs." << dailyRate << "/day" << details()
             << (rented ? " [RENTED]" : " [FREE]") << "\n";
    }
};

class Bicycle : public Vehicle {
public:
    Bicycle(const string& r, double d) : Vehicle(r, d) {}
    double charge(int days, double) const override { return days * dailyRate; }
    string kind() const override { return "Bicycle    "; }
};

class MotorVehicle : public Vehicle {         // still abstract (charge not defined)
protected:
    int level; Date serviceDue;
    double fuelCost(double litres) const { return litres * 110; }   // Rs.110 per litre
public:
    MotorVehicle(const string& r, double d, int lvl, const Date& s)
        : Vehicle(r, d), level(lvl), serviceDue(s) {}
    string details() const override {
        return " level=" + to_string(level) + "% service=" + serviceDue.str();
    }
};

class TwoWheeler : public MotorVehicle {
public:
    using MotorVehicle::MotorVehicle;
    double charge(int days, double litres) const override { return days * dailyRate + fuelCost(litres); }
    string kind() const override { return "TwoWheeler "; }
};

class Car : public MotorVehicle {
protected:
    int seats;
public:
    Car(const string& r, double d, int lvl, const Date& s, int seats)
        : MotorVehicle(r, d, lvl, s), seats(seats) {}
    double charge(int days, double litres) const override { return days * dailyRate + fuelCost(litres); }
    string kind() const override { return "Car        "; }
    string details() const override { return MotorVehicle::details() + " seats=" + to_string(seats); }
};

class ElectricCar : public Car {
    double batteryKWh;
public:
    ElectricCar(const string& r, double d, int lvl, const Date& s, int seats, double kwh)
        : Car(r, d, lvl, s, seats), batteryKWh(kwh) {}
    double charge(int days, double kWh) const override { return days * dailyRate + kWh * 12; } // Rs.12 per kWh
    string kind() const override { return "ElectricCar"; }
    string details() const override { return Car::details() + " battery=" + to_string((int)batteryKWh) + "kWh"; }
};
