// Task 3.4 - effect of 'virtual' on output and sizeof
// compile 1: g++ -std=c++17 -Wall -Wextra task3_experiment.cpp          (virtual)
// compile 2: g++ -std=c++17 -Wall -Wextra -DNOVIRTUAL task3_experiment.cpp (no virtual)
#include <iostream>
#ifdef NOVIRTUAL
  #define VIRT
#else
  #define VIRT virtual
#endif
struct Person  { int id = 0;  Person()  { std::cout << "Person "; } };
struct Student : VIRT Person { double cgpa = 0; Student() { std::cout << "Student "; } };
struct Staff   : VIRT Person { double sal = 0;  Staff()   { std::cout << "Staff "; } };
struct TeachingAssistant : Student, Staff { TeachingAssistant() { std::cout << "TA "; } };
int main() {
    TeachingAssistant t;
    std::cout << "\nsizeof(TeachingAssistant) = " << sizeof(TeachingAssistant) << '\n';
}
