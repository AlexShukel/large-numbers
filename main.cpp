#include <iostream>
#include <limits>

class AImplementation {
public:
    static const int epsilon = 42;
};

class A {
private:
    class Implementation;

    Implementation *implementation;

public:
    static const int epsilon = AImplementation::epsilon;
};

class A::Implementation {
private:
    AImplementation data;

public:

};

int main() {

    return 0;
}
