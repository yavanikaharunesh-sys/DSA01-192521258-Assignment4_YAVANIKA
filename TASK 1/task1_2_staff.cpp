// Task 1.2 - Repaired design: one base class, three derived classes
#include <iostream>
#include <string>
using namespace std;

const double DA_RATE = 0.42;              // no more magic number

class Staff {                             // abstract base: common data + common rule
protected:
    string name;
    int id;
public:
    Staff(const string& n, int i) : name(n), id(i) {}
    virtual double pay() const = 0;       // each category pays differently
    void show() const { cout << id << " " << name << " -> Rs. " << pay() << "\n"; }
    virtual ~Staff() {}
};

class Professor : public Staff {
    double basic, research;
public:
    Professor(const string& n, int i, double b, double r) : Staff(n, i), basic(b), research(r) {}
    double pay() const override { return basic + basic * DA_RATE + research; }
};

class LabAssistant : public Staff {
    double basic;
public:
    LabAssistant(const string& n, int i, double b) : Staff(n, i), basic(b) {}
    double pay() const override { return basic + basic * DA_RATE; }
};

class GuestFaculty : public Staff {
    double hours, rate;
public:
    GuestFaculty(const string& n, int i, double h, double r) : Staff(n, i), hours(h), rate(r) {}
    double pay() const override { return hours * rate; }
};

int main() {
    Staff* list[3] = { new Professor("Meena", 1, 50000, 5000),
                       new LabAssistant("Ravi", 2, 20000),
                       new GuestFaculty("Anu", 3, 10, 1500) };
    for (Staff* s : list) s->show();      // one loop for all staff
    for (Staff* s : list) delete s;
}
