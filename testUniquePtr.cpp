#include <string>  
#include <iostream>

using namespace std;



class Entity {
public:
	Entity()
	{
		cout << "Created Entity!" << endl;
	}

	~Entity()
	{
		cout << "Destroyed Entity!" << endl;
	}
};

int main(int argc, char* argv[])
{
	{
		unique_ptr<Entity> entity(new Entity());
	}
	cin.get();

	system("pause");
	return 0;
}
