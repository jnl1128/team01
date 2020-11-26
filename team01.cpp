#include <bangtal>
#include <iostream>
using namespace bangtal;
using namespace std;

class Product {
public:
    ObjectPtr bread;
    string name;
    int cost;
    Product() : cost(0), name("") {};
};

int Sum(Product* arr) {
    Product* p = nullptr;
    int sum = 0;

    for (p = arr; p < &arr[3]; p++) {
        sum += p->cost;
    }
   
    return sum;
}

void showOrder(Product* arr) {
    cout << "<order list>" << endl;
    Product* p = nullptr;
    for (p = arr; p < &arr[3]; p++) {
        cout << p->name << endl;
    }
}
int main() {
	auto scene = Scene::create("easy mode", "images/background.png");
	auto B100 = Object::create("images/100won.png", scene,500, 500);
	auto buzzer = Object::create("images/buzzer.png", scene, 600, 500);
	bool done = false;
	int money = 0;

	B100->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		money += 100;
		return true;
		});
	buzzer->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		
		return true;
		});
	int total[10] = { 0, };
	Product order[10][3];
	for (int k = 0; k < 10; k++) {
		int type = rand() % 3 + 1;
		for (int i = 0; i < type; i++) {
			int which = rand() % 5;
			string which_bread = "images/bread" + to_string(which) + ".png";
			switch (which) {
			case 0:
				order[k][i].bread = Object::create(which_bread, scene, 100, 100, false);
				order[k][i].name = "bread0";
				order[k][i].cost = 500;
				break;
			case 1:
				order[k][i].bread = Object::create(which_bread, scene, 100, 200, false);
				order[k][i].name = "bread1";
				order[k][i].cost = 700;
				break;
			case 2:
				order[k][i].bread = Object::create(which_bread, scene, 100, 300, false);
				order[k][i].name = "bread2";
				order[k][i].cost = 1000;
				break;
			case 3:
				order[k][i].bread = Object::create(which_bread, scene, 100, 400, false);
				order[k][i].name = "bread3";
				order[k][i].cost = 1200;
				break;
			case 4:
				order[k][i].bread = Object::create(which_bread, scene, 100, 500, false);
				order[k][i].name = "bread4";
				order[k][i].cost = 1500;
				break;
			}
			total[k] += order[k][i].cost / 100;
		}
		showOrder(order[k]);
		Sum(order[k]);
		cout << "-------------" << endl;

	}
	


	startGame(scene);
	return 0;
}
