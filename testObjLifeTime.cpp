#include <iostream>

class Entity
{
public:
    Entity() { std::cout << "Constructor of Entity\n" << std::endl; }
    virtual ~Entity() { std::cout << "Destructor of Entity\n" << std::endl; } 
};

class ScopedPtr
{
    
public:
    ScopedPtr(Entity* ptr) 
        : m_Ptr(ptr)
    { 
        std::cout << "Constructor of ScopedPtr\n" << std::endl; 
    }
    ~ScopedPtr() 
    { 
        delete m_Ptr;
        std::cout << "Destructor of ScopedPtr\n" << std::endl; 
    }
private:
    Entity* m_Ptr;
};

int main()
{

    {
        ScopedPtr e = new Entity(); // or write: ScopedPtr e(new Entity())
        //ScopedPtr is allocated in stack, ScopedPtr e = XXX(not itself), if ScopedPtr *s= new ScopedPtr(), then it is allocated in heap
    } //Entity will be destroyed here even it's allocated in heap, because we delete it inside ~ScopedPtr() 
    std::cout << "-----------------------------------\n" << std::endl;

    std::cin.get();
    system("pause");
}