// Tasks 5.1 and 5.2 - four ways to reach an object, this pointer, array of pointers
#include <iostream>
#include <string>
using namespace std;

class Cart {
    string owner; double amount;
public:
    Cart(const string& owner, double amount = 0) : owner(owner), amount(amount) {}
    Cart& add(double amount) { this->amount += amount; return *this; }  // this-> and *this
    double total() const { return amount; }
    const string& who() const { return owner; }
};

int main() {
    Cart a("Asha");
    a.add(50).add(30);                          // (a) directly by name, chained
    cout << "(a) name      : " << a.total() << "\n";

    Cart* p = &a;
    p->add(10);                                 // (b) pointer with ->
    cout << "(b) pointer   : " << p->total() << "\n";

    Cart& r = a;
    r.add(5);                                   // (c) reference
    cout << "(c) reference : " << r.total() << "\n";

    Cart* h = new Cart("Ravi");                 // (d) new ... delete
    h->add(200);
    cout << "(d) new       : " << h->total() << "\n";
    delete h;

    // Task 5.2 - array of pointers, find the highest total
    Cart* carts[4] = { new Cart("Asha", 95), new Cart("Ravi", 310), new Cart("Meena", 120), new Cart("Kiran", 250) };
    Cart** best = carts;
    for (Cart** q = carts + 1; q < carts + 4; ++q)      // pointer arithmetic
        if ((*q)->total() > (*best)->total()) best = q;
    cout << "Highest cart: " << (*best)->who() << " = " << (*best)->total() << "\n";
    for (Cart* c : carts) delete c;
}
