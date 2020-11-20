#include <bangtal>
#include <iostream>
#include <vector>
using namespace bangtal;
using namespace std;

class Product {
public:
	ObjectPtr bread;
	int cost;
	int many;
	Product() : cost(0), many(0) {};
};

int main() {
	//vector<Product> order;
	auto scene = Scene::create("easy mode", "images/background");

	Product order[4];
	int type = rand() % 3 + 1; // 빵 개수 1~3개 중 하나

	for (int i = 0; i < type+1; i++) {
		int which = rand() % 5;// 빵 종류 5개
		string which_bread = "images/bread" + to_string(which) + ".png";
		switch (which) {
		case 0:
			order[i].bread = Object::create(which_bread, scene, 0, 0, false);
			order[i].cost = 500;
			order[i].many += 1;
			//order.push_back(Product{ which_bread, 500 });	
			break;
		case 1:
			order[i].bread = Object::create(which_bread, scene, 0, 0, false);
			order[i].cost = 700;
			order[i].many += 1;
			//order.push_back(Product{ which_bread, 700 });
			break;
		case 2:
			order[i].bread = Object::create(which_bread, scene, 0, 0, false);
			order[i].cost = 1000;
			order[i].many += 1;
			//order.push_back(Product{ which_bread, 1000 });
			break;
		case 3:
			order[i].bread = Object::create(which_bread, scene, 0, 0, false);
			order[i].cost = 1200;
			order[i].many += 1;
			//order.push_back(Product{ which_bread, 1200 });
			break;
		case 4:
			order[i].bread = Object::create(which_bread, scene, 0, 0, false);
			order[i].cost = 1500;
			order[i].many += 1;
			//order.push_back(Product{ which_bread, 1500 });
			break;
		
		}
		}
	
	return 0;
}