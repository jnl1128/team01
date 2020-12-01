#include <bangtal>
#include <iostream>
#include <vector>
using namespace bangtal;
using namespace std;

void exchange_image(ObjectPtr object, int count) {
	string number = "images/숫자/" + to_string(count) + ".png";
	object->setImage(number);
}

void pick_client(ObjectPtr object) {
	int type = rand() % 5 + 1;
	string client = "images/손님" + to_string(type) + ".png";
	object->setImage(client);
}

class Count {
public:
	static int count;
};
int Count::count = 0;


int getPrice(int bread_type) {
	int price = 0;
	if (bread_type / 5 == 0) {
		price = 500 + bread_type * 100; // 0:500, 1:600, 2:700; 3: 800, 4:900
	}
	else if (bread_type / 5 == 1) {
		price = bread_type * 100 + 1000;// 5: 1500, 6:1600, 7: 1700, 8: 1800, 9:1900
	}
	else {
		price = bread_type * 100 + 200;//10:1200; 11: 1300; 12: 1400; 13: 1500; 14: 1600
	}
	return price;
}

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
	virtual bool onMouse(int x, int y, MouseAction action, ObjectPtr linked_object) {
		if (count < 9) {
			count++;
			exchange_image(temp, count);
		}
		return true;
	}
	
};


class Down : public Object, public Count
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

	virtual bool onMouse(int x, int y, MouseAction action, ObjectPtr linked_object) {
		if (count > 0) {
			count--;
			exchange_image(temp, count);
		}

		return true;

	}

};


int main() {
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
	
	/*Scene 선언부*/
	auto scene_main = Scene::create("", "images/메인화면.png");
	auto scene_select = Scene::create("", "images/난이도선택.png");
	auto scene_game = Scene::create("", "images/게임화면.png");

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
	

	/*guest*/
	auto ano_guest = Object::create("images/익명.png", scene_game, 100, 700);
	auto text_ballon = Object::create("images/말풍선.png", scene_game, 500, 450);
	
	
	/*scene_select*/
	auto easy_select = Object::create("images/easy.png", scene_select, 400, 400);
	easy_select->setScale(1.5f);
	auto normal_select = Object::create("images/normal.png", scene_select, 400, 250);
	normal_select->setScale(1.5f);
	auto hard_select = Object::create("images/hard.png", scene_select, 400, 100);
	hard_select->setScale(1.5f);

	int selected_num;

	int money = 0;
	int total = 0;
	vector <int> bread_price[3];
	vector <ObjectPtr> bread_image[3];
	easy_select->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		
		selected_num = 0;
		scene_game->enter();

		pick_client(ano_guest);
		int loop = 0;
		const int iter = rand() % 3 + 1;
		cout << "iter: " << iter << endl;

		for (int i = 0; i < iter; i++) {
			int type = rand() % 15;
			string name = "images/빵/bread" + to_string(type) + ".png";
			auto bread = Object::create(name, scene_game, 130 + i * 150, 200, true);
			bread_image->push_back(bread);
			bread_price->push_back(getPrice(type));
		}
		for (int i = 0; i < iter; i++) {
			total += bread_price->back();
			bread_price->pop_back();
		}
		cout << "total: " << total << endl;
		
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
	auto done = Object::create("images/done.png", scene_game, 500, 500);


	done->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (money == total) {
			cout << "bingo" << endl;
		}
		else {
			cout << "wrong" << endl;
			cout << "money: " << money << endl;
		}
		cout << "count: " << Count::count << endl;

		/*초기화*/
		money = 0;
		Count::count = 0;
		count_for_100->setImage("images/숫자/0.png");
		count_for_500->setImage("images/숫자/0.png");
		count_for_1000->setImage("images/숫자/0.png");
		count_for_5000->setImage("images/숫자/0.png");
		while (!bread_image->empty()) {
			bread_image->back()->hide();
			bread_image->pop_back();
		}

			
		pick_client(ano_guest);
		int loop = 0;
		vector <int> bread_price[3];
		const int iter = rand() % 3 + 1;
		cout << "iter: " << iter << endl;
		for (int i = 0; i < iter; i++) {
			int type = rand() % 15;
			string name = "images/빵/bread" + to_string(type) + ".png";
			auto bread = Object::create(name, scene_game, 130 + i * 150, 200, true);
			bread_price->push_back(getPrice(type));
		}
		total = 0;
		
		for (int i = 0; i < iter; i++) {
			total += bread_price->back();
			bread_price->pop_back();
		}
		cout << "total: " << total << endl;
		/*초기화*/
		money = 0;
		Count::count = 0;
		count_for_100->setImage("images/숫자/0.png");
		count_for_500->setImage("images/숫자/0.png");
		count_for_1000->setImage("images/숫자/0.png");
		count_for_5000->setImage("images/숫자/0.png");
		while (!bread_image->empty()) {
			bread_image->back()->hide();
			bread_image->pop_back();
		}
		return true;
		});

	up_for_500->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		money += 500;
		string showMoney = "지금은 " + to_string(money) + "원입니다.";
		showMessage(showMoney);
		cout << money << endl;
		return true;
		});
	down_for_500->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		money -= 500;
		string showMoney = "지금은 " + to_string(money) + "원입니다.";
		showMessage(showMoney);
		cout << money << endl;
		return true;
		});
	up_for_100->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		money += 100;
		string showMoney = "지금은 " + to_string(money) + "원입니다.";
		showMessage(showMoney);
		cout << money << endl;
		return true;
		});
	down_for_100->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		money -= 100;
		string showMoney = "지금은 " + to_string(money) + "원입니다.";
		showMessage(showMoney);
		cout << money << endl;
		return true;
		});
	startGame(scene_main);
	return 0;
}
