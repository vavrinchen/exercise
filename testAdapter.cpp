#include <iostream>
#include <string>

class Duck {
    public:
        virtual void fly() = 0;
        virtual void quack() = 0;
};

class CityDuck : public Duck {
    public:
        void fly(){
            std::cout << "CityDuck Fly" << std::endl;
        }
        void quack(){
            std::cout << "CityDuck Quack" << std::endl;
        }
};

class TurkeyAdapterInterface {
    public:
        virtual void turkeyFly() = 0;
        virtual void gobble() = 0;
};

class Turkey {
    public:
        void turkeyFly() {
            std::cout << "This is turkeyFly" << std::endl;
        }
        void gobble() {
            std::cout << "This is turkey gobble" << std::endl;
        }

};

class TurkeyAdapter : public Duck {
    public:
        Turkey *turkey;
        void fly() {
            turkey->turkeyFly();
        }
        void quack() {
            turkey->gobble();
        }
};

int main() {
    Duck *fake_is_a_turkey = new TurkeyAdapter();
    fake_is_a_turkey->fly();
    fake_is_a_turkey->quack();
    return 0;
}
