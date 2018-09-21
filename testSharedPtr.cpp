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

	void Print() {}
};

int main(int argc, char* argv[])
{
	{
		shared_ptr<Entity> e0;
		{
			shared_ptr<Entity> sharedEntity = make_shared<Entity>();
			e0 = sharedEntity;
		}
	}
	cin.get();

	system("pause");
	return 0;
}
