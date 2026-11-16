// Task 2 Alternative: TA HAS-A Student and HAS-A Staff (composition)
#include <iostream>
#include <string>
using namespace std;

struct Person  { string name; int id; string phone; };
struct Student : Person { string programme; double cgpa; };
struct Staff   : Person { string dept; double salary; };

struct TA_Compose { Student s; Staff f; };           // two Person parts inside

struct VStudent : virtual Person { string programme; double cgpa; };
struct VStaff   : virtual Person { string dept; double salary; };
struct TA_Virtual : VStudent, VStaff {};             // one shared Person part

int main() {
    TA_Compose c; TA_Virtual v;
    cout << "sizeof(Person)     = " << sizeof(Person) << "\n";
    cout << "sizeof(TA_Compose) = " << sizeof(TA_Compose) << "  (two Person parts)\n";
    cout << "sizeof(TA_Virtual) = " << sizeof(TA_Virtual) << "  (one Person part + vbase pointers)\n";
    c.s.name = "Kavya"; c.f.name = "Kavya (Staff copy)";
    cout << "composition : c.s.name / c.f.name -> two different names, you must choose\n";
    v.name = "Kavya";
    cout << "virtual     : v.name -> " << v.name << "  (one name, no ambiguity)\n";
}
