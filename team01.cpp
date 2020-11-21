#include <bangtal>
#include <iostream>
using namespace bangtal;
using namespace std;

class Product {
public:
	ObjectPtr bread;
	string name;
	int cost;
	Product() : cost(0), name(""){};
};

int Sum(Product* arr) {
	Product* p = nullptr;
	int sum = 0;

	for (p = arr; p < &arr[3]; p++) {
		sum += p->cost;
	}
	cout << "total: " << sum << endl;
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
	auto scene = Scene::create("easy mode", "images/background");

	Product order[3];
	int type = rand() % 3 + 1; // 빵 개수 1~3개 중 하나
	cout << "type: " << type << endl;
	for (int i = 0; i < type; i++) {
		int which = rand() % 5;// 빵 종류 5개
		string which_bread = "images/bread" + to_string(which) + ".png";
		switch (which) {
		case 0:
			order[i].bread = Object::create(which_bread, scene, 0, 0, false);
			order[i].name = "bread0";
			order[i].cost = 500;
			//order.push_back(Product{ which_bread, 500 });	
			break;
		case 1:
			order[i].bread = Object::create(which_bread, scene, 0, 0, false);
			order[i].name = "bread1";
			order[i].cost = 700;
			//order.push_back(Product{ which_bread, 700 });
			break;
		case 2:
			order[i].bread = Object::create(which_bread, scene, 0, 0, false);
			order[i].name = "bread2";
			order[i].cost = 1000;
			//order.push_back(Product{ which_bread, 1000 });
			break;
		case 3:
			order[i].bread = Object::create(which_bread, scene, 0, 0, false);
			order[i].name = "bread3";
			order[i].cost = 1200;
			//order.push_back(Product{ which_bread, 1200 });
			break;
		case 4:
			order[i].bread = Object::create(which_bread, scene, 0, 0, false);
			order[i].name = "bread4";
			order[i].cost = 1500;
			//order.push_back(Product{ which_bread, 1500 });
			break;
		}
	}
	
	Sum(order);
	showOrder(order);
	return 0;
}