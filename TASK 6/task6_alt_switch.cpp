// Task 6 Alternative: one Vehicle class with a type code and a switch in charge()
#include <chrono>
#include <iostream>
#include <string>
using namespace std;

enum Kind { BICYCLE, TWOWHEELER, CAR, ELECTRIC };

struct VehicleOne {
    Kind kind; string regNo; double dailyRate;
    int level, seats; double batteryKWh;           // unused for some types
    double charge(int days, double used) const {
        switch (kind) {
            case BICYCLE:    return days * dailyRate;
            case TWOWHEELER:
            case CAR:        return days * dailyRate + used * 110;
            case ELECTRIC:   return days * dailyRate + used * 12;
        }
        return 0;
    }
};   // a new type means editing this enum AND this switch (and every other switch)

struct VBase { string regNo; double dailyRate; virtual double charge(int, double) const = 0; virtual ~VBase() {} };
struct VCar : VBase { double charge(int d, double u) const override { return d * dailyRate + u * 110; } };

int main() {
    cout << "sizeof(VehicleOne) = " << sizeof(VehicleOne) << " (every object)\n";
    cout << "sizeof(VCar)       = " << sizeof(VCar) << " (includes the vtable pointer)\n";
    const int N = 20000000;
    VehicleOne s{CAR, "X", 1500, 60, 5, 0};
    VCar c; c.dailyRate = 1500; VBase* b = &c;
    volatile double sink = 0;
    auto t1 = chrono::steady_clock::now();
    for (int i = 0; i < N; ++i) sink = s.charge(2, 10);
    auto t2 = chrono::steady_clock::now();
    for (int i = 0; i < N; ++i) sink = b->charge(2, 10);
    auto t3 = chrono::steady_clock::now();
    cout << N << " calls, switch  : " << chrono::duration<double, milli>(t2 - t1).count() << " ms\n";
    cout << N << " calls, virtual : " << chrono::duration<double, milli>(t3 - t2).count() << " ms\n";
    cout << "result check: " << sink << "\n";   // uses sink so the loops are not removed
}
