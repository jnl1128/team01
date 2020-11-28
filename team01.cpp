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

void exchange_image(ObjectPtr object, int count) {
	string number = "images/숫자/" + to_string(count) + ".png";
	object->setImage(number);
}

class Count {
public:
	static int count;
};
int Count::count = 0;


class Up : public Object, public Count
{
protected:
	ObjectPtr temp;
	Up(const string& image, ScenePtr scene, int x, int y, bool shown, ObjectPtr linked_object) : Object(image, scene, x, y, shown) {
		temp = linked_object;
	}

public:

	static ObjectPtr create(const string& image, ScenePtr scene = nullptr, int x = 0, int y = 0, bool shown = true, ObjectPtr linked_object = nullptr) {
		auto object = ObjectPtr(new Up(image, scene, x, y, shown, linked_object));
		Object::add(object);
		return object;
	}


	virtual bool onMouse(int x, int y, MouseAction action) {
		if (count < 9) {
			count++;
			exchange_image(temp, count);
		}

		return true;
	}
};

class Down :public Object, public Count
{
protected:
	ObjectPtr temp;
	Down(const string& image, ScenePtr scene, int x, int y, bool shown, ObjectPtr linked_object) : Object(image, scene, x, y, shown) {
		temp = linked_object;
	}

public:
	static ObjectPtr create(const string& image, ScenePtr scene = nullptr, int x = 0, int y = 0, bool shown = true, ObjectPtr linked_object = nullptr) {
		auto object = ObjectPtr(new Down(image, scene, x, y, shown, linked_object));
		Object::add(object);
		return object;
	}

	virtual bool onMouse(int x, int y, MouseAction action) {
		if (count > 0) {
			count--;
			exchange_image(temp, count);
		}

		return true;

	}

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


	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

	/*Scene 선언부*/
	auto scene_main = Scene::create("", "images/메인화면.png");
	auto scene_select = Scene::create("", "images/난이도선택.png");
	auto scene_game = Scene::create("", "images/게임화면.png");

	/*
	auto B100 = Object::create("images/100won.png", scene_main,500, 500);
	auto buzzer = Object::create("images/buzzer.png", scene_main, 600, 500);
	bool done = false;
	int money = 0;
	*/

	/*scene_main*/
	auto button_start = Object::create("images/게임시작.png", scene_main, 200, 310);
	button_start->setScale(0.8f);
	auto button_guide = Object::create("images/게임설명.png", scene_main, 500, 310);
	button_guide->setScale(0.8f);
	auto button_end = Object::create("images/게임종료.png", scene_main, 800, 310);
	button_end->setScale(0.8f);


	button_start->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene_select->enter();
		return true;
		});


	/*scene_select*/

	auto easy_select = Object::create("images/easy.png", scene_select, 400, 400);
	easy_select->setScale(1.5f);
	auto normal_select = Object::create("images/normal.png", scene_select, 400, 250);
	normal_select->setScale(1.5f);
	auto hard_select = Object::create("images/hard.png", scene_select, 400, 100);
	hard_select->setScale(1.5f);

	int selected_num;

	easy_select->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		selected_num = 0;
		scene_game->enter();
		return true;
		});

	normal_select->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		selected_num = 1;
		return true;
		scene_game->enter();
		});

	hard_select->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		selected_num = 2;
		scene_game->enter();
		return true;
		});


	/*scene_game*/


	auto count_for_5000 = Object::create("images/숫자/0.png", scene_game, 830, 630);
	auto count_for_1000 = Object::create("images/숫자/0.png", scene_game, 950, 630);
	auto count_for_500 = Object::create("images/숫자/0.png", scene_game, 1080, 630);
	auto count_for_100 = Object::create("images/숫자/0.png", scene_game, 1195, 630);

	auto up_for_5000 = Up::create("images/증가버튼1.png", scene_game, 1038, 318, true, count_for_5000);
	auto down_for_5000 = Down::create("images/감소버튼1.png", scene_game, 1038, 298, true, count_for_5000);
	auto up_for_1000 = Up::create("images/증가버튼1.png", scene_game, 1038, 273, true, count_for_1000);
	auto down_for_1000 = Down::create("images/감소버튼1.png", scene_game, 1038, 253, true, count_for_1000);
	auto up_for_100 = Up::create("images/증가버튼2.png", scene_game, 1090, 293, true, count_for_100);
	auto down_for_100 = Down::create("images/감소버튼2.png", scene_game, 1090, 280, true, count_for_100);
	auto up_for_500 = Up::create("images/증가버튼2.png", scene_game, 1090, 238, true, count_for_500);
	auto down_for_500 = Down::create("images/감소버튼2.png", scene_game, 1090, 224, true, count_for_500);




	/*
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
				order[k][i].bread = Object::create(which_bread, scene_main, 100, 100, false);
				order[k][i].name = "bread0";
				order[k][i].cost = 500;
				break;
			case 1:
				order[k][i].bread = Object::create(which_bread, scene_main, 100, 200, false);
				order[k][i].name = "bread1";
				order[k][i].cost = 700;
				break;
			case 2:
				order[k][i].bread = Object::create(which_bread, scene_main, 100, 300, false);
				order[k][i].name = "bread2";
				order[k][i].cost = 1000;
				break;
			case 3:
				order[k][i].bread = Object::create(which_bread, scene_main, 100, 400, false);
				order[k][i].name = "bread3";
				order[k][i].cost = 1200;
				break;
			case 4:
				order[k][i].bread = Object::create(which_bread, scene_main, 100, 500, false);
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
	*/



	startGame(scene_main);
	return 0;
}
