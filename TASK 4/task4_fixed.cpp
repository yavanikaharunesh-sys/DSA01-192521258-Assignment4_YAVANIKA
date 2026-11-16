// Task 4.3 - repaired program: virtual functions + virtual destructor + pointers
#include <iostream>
using namespace std;

class Account {
public:
    virtual double rate() const { return 3.5; }
    virtual ~Account() { cout << "~Account\n"; }
};
class SeniorAccount : public Account {
    double* history = new double[100];
public:
    double rate() const override { return 4.0; }
    ~SeniorAccount() override { cout << "~SeniorAccount (history freed)\n"; delete[] history; }
};

int main() {
    Account* accounts[2] = { new Account, new SeniorAccount };
    for (Account* a : accounts) cout << a->rate() << "\n";   // 3.5 and 4
    for (Account* a : accounts) delete a;                    // both destructors run
    SeniorAccount s;
    Account& ref = s;                                        // reference, not a copy
    cout << "ref.rate() = " << ref.rate() << "\n";           // 4
}
