#include <iostream>

class Base
{
public:
    Base() { std::cout << "Constructor of Base\n" << std::endl; }
    virtual ~Base() { std::cout << "Destructor of Base\n" << std::endl; } //add virtual to prevent not calling destructor of Derived
};

class Derived : public Base
{
    
public:
    Derived() { std::cout << "Constructor of Derived\n" << std::endl; }
    ~Derived() { std::cout << "Destructor of Derived\n" << std::endl; }
};

int main()
{
    Base* base = new Base();
    delete base;
    std::cout << "-----------------------------------\n" << std::endl;

    Derived* derived = new Derived();
    delete derived;
    std::cout << "-----------------------------------\n" << std::endl;

    Base* poly = new Derived();
    delete poly;
    std::cout << "-----------------------------------\n" << std::endl;

    std::cin.get();
    system("pause");
}