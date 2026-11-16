// Task 1 Alternative: one Staff class with a type field and a switch in pay()
#include <chrono>
#include <iostream>
#include <string>
using namespace std;

enum Type { PROF, LAB, GUEST };

class StaffOne {
public:
    Type type; string name; int id;
    double basic, research, hours, rate;      // many fields stay unused per object
    double pay() const {
        switch (type) {
            case PROF:  return basic + basic * 0.42 + research;
            case LAB:   return basic + basic * 0.42;
            case GUEST: return hours * rate;
        }
        return 0;
    }
};

// same data written as a hierarchy, only to compare sizes and speed
struct Base { string name; int id; virtual double pay() const = 0; virtual ~Base() {} };
struct Prof : Base { double basic, research; double pay() const override { return basic + basic * 0.42 + research; } };
struct Guest : Base { double hours, rate;    double pay() const override { return hours * rate; } };

int main() {
    cout << "sizeof(StaffOne) = " << sizeof(StaffOne) << " bytes (every type)\n";
    cout << "sizeof(Prof)     = " << sizeof(Prof)     << " bytes\n";
    cout << "sizeof(Guest)    = " << sizeof(Guest)    << " bytes\n";

    const int N = 20000000;
    StaffOne s{PROF, "A", 1, 50000, 5000, 0, 0};
    Prof p; p.basic = 50000; p.research = 5000;
    Base* bp = &p;
    volatile double sink = 0;

    auto t1 = chrono::steady_clock::now();
    for (int i = 0; i < N; ++i) sink = s.pay();
    auto t2 = chrono::steady_clock::now();
    for (int i = 0; i < N; ++i) sink = bp->pay();
    auto t3 = chrono::steady_clock::now();
    cout << N << " calls, switch  : " << chrono::duration<double, milli>(t2 - t1).count() << " ms\n";
    cout << N << " calls, virtual : " << chrono::duration<double, milli>(t3 - t2).count() << " ms\n";
    cout << "result check: " << sink << "\n";   // uses sink so the loops are not removed
}
