#include <iostream>

//exercise Stratgy Pattern
//所有鴨子都會有飛和叫的行為, 但實作方式可能不同, 所有鴨子都會 show 出自己是什麼鴨子
/*
I'm city duck
fly like turtle
Set FlyBehavior to: 0x7fe1c1c032c0
fly like jet
I'm mountain duck
fly like jet
Set FlyBehavior to: 0x7fe1c1c032f0
fly like turtle
*/
class IFlybehavior
{
  public:
    virtual void fly() = 0;
};

class Duck
{
  public:
    IFlybehavior *flyBehavior;
    //IQuackBehavior *quackBehavior;
    void setFlyBehavior(IFlybehavior *flyBehavior);
    void performFly();
    virtual void display() = 0;
    
};

void Duck::setFlyBehavior(IFlybehavior *flyBehavior) {
    this->flyBehavior = flyBehavior;
    std::cout << "Set FlyBehavior to: " << flyBehavior << std::endl;
}

void Duck::performFly()
{
    this->flyBehavior->fly();
}

class JetFly : public IFlybehavior
{
  public:
        void fly() {
            std::cout << "fly like jet" << std::endl;
        }
};

class SlowFly : public IFlybehavior
{
    public:
        void fly() {
            std::cout << "fly like turtle" << std::endl;
        }
};

class CityDuck: public Duck {
    public:
        CityDuck() {
            flyBehavior = new SlowFly();    
        }
        void display()
        {
            std::cout << "I'm city duck" << std::endl;
        }
};

class MountainDuck: public Duck {
    public:
        MountainDuck() {
            flyBehavior = new JetFly();
        }

        void display() {
            std::cout << "I'm mountain duck" << std::endl;
        }
};

int main() {
    Duck *cityDuck = new CityDuck();
    cityDuck->display();
    cityDuck->performFly();
    cityDuck->setFlyBehavior(new JetFly());
    cityDuck->performFly();
    Duck *mountainDuck = new MountainDuck();
    mountainDuck->display();
    mountainDuck->performFly();
    mountainDuck->setFlyBehavior(new SlowFly());
    mountainDuck->performFly();
}