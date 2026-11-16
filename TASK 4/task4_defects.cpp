// Task 4.1 / 4.2 - the BUGGY program with print statements added to the destructors
#include <iostream>
using namespace std;

class Account {
public:
    double rate() const { return 3.5; }            // not virtual  -> defect 1
    ~Account() { cout << "~Account\n"; }           // not virtual  -> defect 2
};
class SeniorAccount : public Account {
    double* history = new double[100];
public:
    double rate() const { return 4.0; }            // hides, does not override
    ~SeniorAccount() { cout << "~SeniorAccount (history freed)\n"; delete[] history; }
};

int main() {
    Account* accounts[2] = { new Account, new SeniorAccount };
    for (Account* a : accounts) cout << a->rate() << "\n";   // prints 3.5 and 3.5
    for (Account* a : accounts) delete a;                    // SeniorAccount dtor never runs
    Account copy = SeniorAccount();                          // slicing: Account part only
    cout << "copy.rate() = " << copy.rate() << "\n";
}
