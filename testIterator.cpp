#include <iostream>
#include <string>
#include <list>

class MenuItem {
    public:
        std::string getName() {
            return name;
        }
         MenuItem(std::string set_name){
             name = set_name;
         }
    private:
        std::string name;
};

class Iterator {
    public:
        virtual bool hasNext() = 0;
        virtual MenuItem next() = 0;
};

class Menu {
    public: 
        virtual Iterator* createIterator() = 0;
};

class PancakeIterator : public Iterator { //Pancake use list to store menu
    public:
        PancakeIterator(std::list<MenuItem> item){
            items = item;
            iter = items.begin();
        }
        bool hasNext(){
            if(iter != items.end()){
                return true;
            } else {
                return false;
            }
        }
        MenuItem next(){
            MenuItem menuItem = *iter;
            ++iter;
            return menuItem;
        }
    private:
        std::list<MenuItem> items;
        std::list<MenuItem>::iterator iter;
};

class PancakeMenu : public Menu {
    public:
        PancakeMenu(){
            addItem("K&B'S Breakfase");
        }
        Iterator* createIterator(){
            return new PancakeIterator(item);
        }
        void addItem(std::string name){
            MenuItem menuItem(name);
            item.push_back(name);
        }
    private:
        std::list<MenuItem> item;
};

class Waitress{
    public:
        void printMenu(){
            pancakeIter = pancakeMenu->createIterator();
            if(pancakeIter->hasNext()){
                std::cout << pancakeIter->next().getName() << std::endl;
            }
        }
    private:
        Menu* pancakeMenu = new PancakeMenu();
        Iterator *pancakeIter;
};

int main() {
    Waitress *waitress = new Waitress();
    waitress->printMenu();
    return 0;
}