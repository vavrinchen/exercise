#include <iostream>
#include <string>

/*
預想會有的類別
IngredientFactory
(Concrete Factory) NYIngredientFactory
(Concrete Factory) ChicagoIngredientFactory
Dough
Clam
Cheese
ThickDough
ThinDough
MozzarellaCheese
ReggianoCheese
FreshClam
FrozenClam
PizzaFactory
(Concrete Factory) NYPizzaFactory
(Concrete Factory) ChicagiPizzaFactory
Pizza
NYCheesePizza
ChicagoCheesePizza
NYVeggiePizza
ChicagoClamPizza

實際執行成果
This is NYCheesePizza
This is base Dough
This is ThickDough
NYIngredientFactory use dough
*/

class Dough {
    public:
      Dough(){
          std::cout << "This is base Dough" << std::endl;
      }
};

class ThickDough: public Dough {
    public:
      ThickDough() {
          std::cout << "This is ThickDough" << std::endl;
      }
};


class IngredientFactory
{
  public:
    Dough* dough;
    virtual Dough* setDough(Dough* dough)=0;

};



class NYIngredientFactory:public IngredientFactory {
public:
  Dough* setDough(Dough* dough);
};

Dough* NYIngredientFactory::setDough(Dough *dough)
{
    this->dough = dough;
    std::cout << "NYIngredientFactory use dough" << std::endl;
    return dough;
}

class Pizza {
    public:
        Dough* dough;

        void bake();
        void wrap();
};

void Pizza::bake(){
    std::cout << "bake pizza" << std::endl;
}

void Pizza::wrap()
{
    std::cout << "wrap pizza" << std::endl;
}

class NYCheesePizza : public Pizza {
    public:
      NYCheesePizza(){
          std::cout << "This is NYCheesePizza" << std::endl;
      }
};

class PizzaFactory
{
  public:
    virtual Pizza *createPizza(std::string type) = 0;

};

class NYPizzaFactory : public PizzaFactory {
    public:
      Pizza* createPizza(std::string type);
};

Pizza* NYPizzaFactory::createPizza(std::string type) {
    Pizza* pizza;
    if (type == "cheese")
    {
        pizza = new NYCheesePizza();
        /* 
        原版的寫法是不建立 NYCheesePizza class, 而是 Chiacgo 和 NY 共用 CheesePizza class,
        然後 CheesePizza 的建構式中傳入參數 Ingredient class
        */
    }
    IngredientFactory *nyIngredientFactory = new NYIngredientFactory();
    pizza->dough = nyIngredientFactory->setDough(new ThickDough);
    

    return pizza;
}

int main() {
    PizzaFactory *nyPizzaFactory = new NYPizzaFactory();
    nyPizzaFactory->createPizza("cheese");
}