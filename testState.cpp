#include <iostream>
#include <sstream>
#include <cassert>
#include <string>
class State {
  public:
    virtual void insertQuarter()  = 0;
    virtual void ejectQuarter()  = 0;
    virtual void turnCrank()  = 0;
    virtual void dispense() = 0;
    virtual std::string toString() { };
};

class GumballMachine
{
  public:
    GumballMachine(int numberGumballs);
    void insertQuarter()  {
        _state->insertQuarter();
    }
    void ejectQuarter() 
    {
        _state->ejectQuarter();
    }
    void turnCrank()  {
        _state->turnCrank();
        _state->dispense();
    }
    void setState(State *state) {
        assert(state);
        _state = state;
    }
    void releaseBall() {
        std::cout << "A gumball comes rolling out the slot..." << std::endl;
        if (_count != 0) {
            _count--;
        }
    }
    int getCount() {
        return _count;
    }
    std::string toString() {
        std::stringstream value;
        value << std::endl
              << "Inventory: " << _count << " gumball";
        if (_count > 1)
        {
            value << "s";
        }
        value << std::endl;
        value << "Machine is " << _state->toString() << std::endl;
        return value.str();
    }

    State *_soldOutState;
    State *_noQuarterState;
    State *_hasQuarterState;
    State *_soldState;
    State *_state;
    int _count;
};

class SoldOutState : public State {
  public:
    SoldOutState(GumballMachine *gumballMachine) : _gumballMachine(gumballMachine)
    {
        assert(gumballMachine);
    }
    void insertQuarter(){
        std::cout << "You can't insert a quarter, the machine is sold out" << std::endl;
    }
    void ejectQuarter(){
        std::cout << "You can't eject, you haven't inserted a quarter yet" << std::endl;
    }
    void turnCrank(){
        std::cout << "You turned, but there are no gumballs" << std::endl;
    }
    void dispense(){
        std::cout << "No gumball dispensed" << std::endl;
    }
    std::string toString(){
        return "sold out";
    }
  private:
    GumballMachine *_gumballMachine;
};

class NoQuarterState : public State {
  public:
    NoQuarterState(GumballMachine *gumballMachine) : _gumballMachine(gumballMachine)
    {
        assert(gumballMachine);
    }
    void insertQuarter() {
        std::cout << "You inserted a quarter" << std::endl;
        _gumballMachine->setState(_gumballMachine->_hasQuarterState);
    }
    void ejectQuarter() {
        std::cout << "You haven't inserted a quarter" << std::endl;
    }
    void turnCrank() {
        std::cout << "You turned, but there's no quarter" << std::endl;
    }
    void dispense() {
        std::cout << "You need to pay first" << std::endl;
    }
    std::string toString() {
        return "waiting for quarter";
    }

  private:
    GumballMachine *_gumballMachine;
};

class HasQuarterState : public State {
  public:
    HasQuarterState(GumballMachine *gumballMachine) : _gumballMachine(gumballMachine)
    {
        assert(gumballMachine);
    }
    void insertQuarter() 
    {
        std::cout << "You can't insert another quarter" << std::endl;
    }
    void ejectQuarter() 
    {
        std::cout << "Quarter returned" << std::endl;
        _gumballMachine->setState(_gumballMachine->_noQuarterState);
    }
    void turnCrank() 
    {
        std::cout << "You turned..." << std::endl;
        if (_gumballMachine->getCount() > 0) {
            _gumballMachine->setState(_gumballMachine->_soldState);
        } else {
            _gumballMachine->setState(_gumballMachine->_soldOutState);
        }
    }
    void dispense()
    {
        std::cout << "No gumball dispensed" << std::endl;
    }

  private:
    GumballMachine *_gumballMachine;
}; 

class SoldState : public State {
  public:
    SoldState(GumballMachine *gumballMachine) : _gumballMachine(gumballMachine)
    {
        assert(gumballMachine);
    }
    void insertQuarter() 
    {
        std::cout << "Please wait, we're already giving you a gumball" << std::endl;
    }
    void ejectQuarter() 
    {
        std::cout << "Sorry, you already turned the crank" << std::endl;
    }
    void turnCrank() 
    {
        std::cout << "Turning twice doesn't get you another gumball!" << std::endl;
    }
    void dispense()
    {
        _gumballMachine->releaseBall();
        if (_gumballMachine->getCount() > 0)
        {
            _gumballMachine->setState(_gumballMachine->_noQuarterState);
        }
        else
        {
            std::cout << "Oops, out of gumballs!" << std::endl;
            _gumballMachine->setState(_gumballMachine->_soldOutState);
        }
    }
  private:
    GumballMachine *_gumballMachine;
};

GumballMachine::GumballMachine(int numberGumballs) {
    _count = numberGumballs;
    assert(numberGumballs >= 0);
    _soldOutState = new SoldOutState(this);
    _noQuarterState = new NoQuarterState(this);
    _hasQuarterState = new HasQuarterState(this);
    _soldState = new SoldState(this);
    _state = _soldOutState;
     if (_count > 0)
    {
        _state = _noQuarterState;
    }
}

int main() {
    GumballMachine *gumballMachine = new GumballMachine(3);
    //std::auto_ptr<GumballMachine> gumballMachine(new GumballMachine(10));
    std::cout << gumballMachine->toString() << std::endl;

    gumballMachine->insertQuarter();
    gumballMachine->turnCrank();
    gumballMachine->insertQuarter();
    gumballMachine->turnCrank();

    std::cout << gumballMachine->toString() << std::endl;

    gumballMachine->insertQuarter();
    gumballMachine->turnCrank();
    gumballMachine->insertQuarter();
    gumballMachine->turnCrank();

    std::cout << gumballMachine->toString() << std::endl;

    gumballMachine->insertQuarter();
    gumballMachine->turnCrank();
    gumballMachine->insertQuarter();
    gumballMachine->turnCrank();

    std::cout << gumballMachine->toString() << std::endl;
    return 0;
}