#include <string>  
#include <iostream>
#include <vector>

using namespace std;


class Tool {
    public:
        virtual void draw() = 0;
};

class Pencil : public Tool {
    public:
        void draw() {
            cout << "Pencil Draw" << endl;
        }

};

class Brush : public Tool
{
  public:
    void draw()
    {
        cout << "Brush Draw" << endl;
    }
};

class Panel {
    public:
        void addTool(Tool *tool) {
            toolList.push_back(tool);
        }

        void paint() {
            for (auto tool: toolList) {
                tool->draw();
            }
        }

    private:
        vector<Tool*> toolList;

};

int main(int argc, char* argv[])
{
    Panel *panel = new Panel(); 
    Tool *brush = new Brush();
	Tool *pencil = new Pencil();
    
    panel->addTool(pencil);
    panel->addTool(brush);
    panel->paint();

	return 0;
}
