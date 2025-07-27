#include <iostream>
#include <string>

using namespace std;

// Helper functions that distinguish between lvalues and rvalues
void process_value(int& val) {
    std::cout << "Processing lvalue: " << val << std::endl;
}

void process_value(int&& val) {
    std::cout << "Processing rvalue: " << val << std::endl;
}

// A wrapper function designed to forward its argument
template<typename T>
void wrapper(T&& arg) { // 'arg' here is a "forwarding reference" (or "universal reference")
    process_value(forward<T>(arg)); // Problem: 'arg' inside 'wrapper' is always an lvalue!
    process_value(forward<int>(arg));
    process_value(forward<int&>(arg));
}

int main() {
    int a = 10;
    cout << "============== left value input ==============\n";
    wrapper(a);      // Call with an lvalue (variable 'a')
    
    cout << "\n============== right value input ==============\n";
    wrapper(20);     // Call with an rvalue (literal '20')
}