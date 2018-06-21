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
CheesePizza
VeggiePizza
ClamPizza

實際執行成果
This is CheesePizza
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
    virtual Dough* prepareDough() = 0;
};



class NYIngredientFactory:public IngredientFactory {
public:
  Dough* prepareDough();
};

Dough *NYIngredientFactory::prepareDough()
{
    this->dough = new ThickDough();
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

class CheesePizza : public Pizza {
    public:
      CheesePizza(IngredientFactory *ingredientFactory)
      {
          std::cout << "This is CheesePizza" << std::endl;
          ingredientFactory->prepareDough();
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
    IngredientFactory *nyIngredientFactory = new NYIngredientFactory();
    if (type == "cheese")
    {
        pizza = new CheesePizza(nyIngredientFactory);
        /* 
        原版的寫法是不建立 NYCheesePizza class, 而是 Chiacgo 和 NY 共用 CheesePizza class,
        然後 CheesePizza 的建構式中傳入參數 Ingredient class
        然後綁死 NYIngredient factory 只能產生 Thick 麵團
        */
    }
    
    

    return pizza;
}

int main() {
    PizzaFactory *nyPizzaFactory = new NYPizzaFactory();
    nyPizzaFactory->createPizza("cheese");
}