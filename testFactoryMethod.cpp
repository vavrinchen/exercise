/*
Creator(PizzaFactory), 
Product(Pizza)
Concrete Creator(NYPizzaFactory, ChicagoPizzaFactory), 
Concrete Product(NYCheesePizza, ChicagoCheesePizza)
在 main 中抽換 factory 即可改變 pizza 
This NYCheesePizza
bake pizza
wrap pizza
This ChicagoClamPizza
bake pizza
wrap pizza
*/
#include<iostream>
#include<string>

class Pizza {
    public: 
    void bake();
    void wrap();
};

void Pizza::bake() {
    std::cout << "bake pizza" << std::endl;
}

void Pizza::wrap()
{
    std::cout << "wrap pizza" << std::endl;
}

class NYCheesePizza : public Pizza {
    public:
      NYCheesePizza(){
          std::cout << "This NYCheesePizza" << std::endl;
      }
};

class NYVeggiePizza : public Pizza
{
  public:
    NYVeggiePizza(){
        std::cout << "This NYVeggiePizza" << std::endl;
    }
};

class ChicagoCheesePizza : public Pizza {
    public:
      ChicagoCheesePizza(){
          std::cout << "This ChicagoCheesePizza" << std::endl;
      }
};

class ChicagoClamPizza : public Pizza
{
  public:
    ChicagoClamPizza()
    {
        std::cout << "This ChicagoClamPizza" << std::endl;
    }
};

class PizzaFactory {
    public: 
        virtual Pizza* createPizza(std::string type)= 0;
};

class NYPizzaFactory : public PizzaFactory {
    public:
      Pizza* createPizza(std::string type);
};

Pizza* NYPizzaFactory::createPizza(std::string type) {
    Pizza* pizza;
    if(type=="cheese") {
        pizza = new NYCheesePizza();
    } else {
        pizza = new NYVeggiePizza();
    }
    return pizza;
}


class ChicagoPizzaFactory : public PizzaFactory {
    Pizza* createPizza(std::string type);
};

Pizza* ChicagoPizzaFactory::createPizza(std::string type) {
    Pizza *pizza;
    if (type == "cheese"){
        pizza = new ChicagoCheesePizza();
    }
    else
    {
        pizza = new ChicagoClamPizza();
    }
        return pizza;
 }


int main(){
    PizzaFactory *pizzaFactory = new NYPizzaFactory();
    Pizza* pizza;
    pizza = pizzaFactory->createPizza("cheese");
    pizza->bake();
    pizza->wrap();
    pizzaFactory = new ChicagoPizzaFactory();
    pizza = pizzaFactory->createPizza("clam");
    pizza->bake();
    pizza->wrap();
}