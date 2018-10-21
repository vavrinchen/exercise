#include <iostream>

class Singleton
{
public:
    static Singleton& Get()
    {
        static Singleton instance;
        return instance;
    }
    void Hello() 
    {
        std::cout << "Hello" << std::endl;
    }
};

void Function()
{
    static int i = 0;
    i++;
    std::cout << i << std::endl;
}

int main()
{
    Singleton::Get().Hello();
    
    Function();
    Function();
    Function();
    Function();
    Function();
}
