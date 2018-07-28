#include <vector>
#include <iostream>
#include <string>
//composite 好處, 讓 "leaf" 和 "非 leaf" 能統一處理
//composite 的概念是原本的正餐菜單要讓甜點也可以用, 原有的正餐菜單框架要多有甜點菜單框架 (Component) 下面要有料理名和甜點名 (Leaf)
//所以之前的 iterator pattern 中的 Iterable Iterface Menu(Concrete Iterable 像是 PancakeMenu) 就會變成 composite pattern 中的 Component (Todolist), 
//之前的 Iterable 要有 getIterator() 的方法, 現在的 Composite 則是要有 addItem(), removeItem(), 可以想成必須有新增刪除 tree node 的方法
//但在這個 pattern 中我們就直接把 Iterator pattern 中的 Menu 改叫成 MenuComponent, 然後這邊的 Concrete 菜單就可以叫做 Menu 了
//然後想擴充的甜點菜單框架就是 composite pattern 中的 Composite (Project),
//iterator pattern 中的 MenuItem (負責 getName 的那個 class) 就會變成 composite pattern 中的 Leaf (Todo)
//MenuItem 就是負責料理名和甜點名

//Component of composite pattern
class MenuComponent {
  public:
    virtual void addItem(MenuComponent *pMenuComponent) { }
    virtual std::string getName() { }
    virtual void print() { }
};

//Composite of composite pattern, should implement MenuComponent
class Menu : public MenuComponent {
  public:
    Menu(std::string setName)
    {
        name = setName;
    }
    //Iterator pattern 的 add 是加 MenuItem, 但 Composite pattern 是加 MenuComponent
    void addItem(MenuComponent *pMenuComponent){
        pMenuComponents.push_back(pMenuComponent);
    }

    std::string getName() {
        return name;
    }

    void print()
    {
        std::cout << getName() << std::endl;
        std::vector<MenuComponent *>::iterator iter = pMenuComponents.begin();
        while (iter != pMenuComponents.end())
        {
            MenuComponent *pMenuComponent = *iter;
            pMenuComponent->print();
            ++iter;
        }
    }

  private:
    std::vector<MenuComponent*> pMenuComponents; //Composite has a Component
    std::string name;
};

//Leaf of composite pattern, should implement MenuComponent
class MenuItem : public MenuComponent {
  public:
    MenuItem(std::string setName) {
        name = setName;
    }
    std::string getName() {
        return name;
    }
    void print() {
        std::cout << "	(Leaf)" << getName() << std::endl;
    }

  private:
    std::string name;
};

//Client has a Component
class Waitress {
    public:
      Waitress(MenuComponent *setAllMenus) {
          allMenus = setAllMenus;
      }
      void printMenu() {
          allMenus->print();
      }
    private:
      MenuComponent *allMenus; //Client has a Component
};

int main() {
    
    MenuComponent *pancakeHouseMenu = new Menu("Pancake MENU");
    MenuComponent *dinerMenu = new Menu("Diner MENU");
    MenuComponent *dessertMenu = new Menu("DESSERT MENU");

    MenuComponent *allMenus = new Menu("ALL Menus");

    allMenus->addItem(pancakeHouseMenu);
    allMenus->addItem(dinerMenu);
    dinerMenu->addItem(new MenuItem("Diner Pasta"));

    dinerMenu->addItem(dessertMenu);
    dessertMenu->addItem(new MenuItem("Apple Pie"));
    Waitress *waitress = new Waitress(allMenus);
    waitress->printMenu();
    return 0;
}