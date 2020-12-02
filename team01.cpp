#include <bangtal>
#include <iostream>
#include <vector>
using namespace bangtal;
using namespace std;


void pick_client(ObjectPtr object) {
	int type = rand() % 6 + 1;
	string client = "images/손님" + to_string(type) + ".png";
	object->setImage(client);
}

int pick_cash(ObjectPtr object, int num) {
	int return_value = 0;
	vector <int> Vector_cash{ 2000, 3000, 5000, 10000, 15000, 20000 };
	for (int v_num = 0; v_num < 6; v_num++) {
		if (num > Vector_cash[v_num]) {
			continue;
		}
		else {
			return_value = Vector_cash[v_num];
			string cash_name = "images/돈/" + to_string(return_value) + "원.png";
			object->setImage(cash_name);
			cout << "cash: " << Vector_cash[v_num] << endl;
			break;
		}

	}
	object->show();
	return return_value;
}

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

void showingStatus(int num) {
	string showChange = "지금은 " + to_string(num) + "원입니다.";
	showMessage(showChange);
}


class Up : public Object
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

		return true;
	}

};


class Down : public Object
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

		return true;

	}

};


int main() {
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

	/*Scene 선언부*/
	auto scene_main = Scene::create("", "images/메인화면.png");
	auto scene_select = Scene::create("", "images/난이도선택.png");
	auto scene_game = Scene::create("", "images/game_play.png");
	auto scene_guide = Scene::create("", "images/게임설명판.png");
	auto scene_menu = Scene::create("", "images/메뉴판.png");
	

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

	button_guide->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene_guide->enter();
		return true;
		});

	/*scene_guide*/

	auto exit_guide = Object::create("images/exit.png", scene_guide, 1100, 100);

		
	exit_guide->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene_main->enter();
		return true;
		});

	/*scene_menu*/

	auto bread_menu = Object::create("images/빵메뉴판.png", scene_menu, 115, 62);

	auto bread_button = Object::create("images/빵버튼.png", scene_menu, 60, 420);
	auto sand_button = Object::create("images/샌드버튼.png", scene_menu, 60, 350);
	auto other_button = Object::create("images/기타버튼.png", scene_menu, 60, 270);
	auto menu_board = Object::create("images/메뉴팻말.png", scene_menu, 454, 534);

	bread_button ->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		bread_menu->setImage("images/빵메뉴판.png");
		return true;
		});

	sand_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		bread_menu->setImage("images/샌드위치메뉴판.png");
		return true;
		});

	other_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		bread_menu->setImage("images/기타메뉴판.png");
		return true;
		});

	auto exit_menu = Object::create("images/exit.png", scene_menu, 1100, 100);
	exit_menu->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene_game->enter();
		return true;
		});

	/*guest*/
	auto ano_guest = Object::create("images/익명.png", scene_game, 200, 600);
	auto text_ballon = Object::create("images/말풍선.png", scene_game, 500, 450);

	/*cash*/
	auto cash_image = Object::create("images/돈.png", scene_game, 500, 600);


	/*scene_select*/
	auto easy_select = Object::create("images/easy.png", scene_select, 400, 400);
	easy_select->setScale(1.5f);
	auto normal_select = Object::create("images/normal.png", scene_select, 400, 250);
	normal_select->setScale(1.5f);
	auto hard_select = Object::create("images/hard.png", scene_select, 400, 100);
	hard_select->setScale(1.5f);

	int selected_num;

	int cash = 0; //손님이 내는 돈
	int change = 0; //거스름돈
	int total = 0; //내야하는 돈(빵 값)
	vector <int> bread_price[3];
	vector <ObjectPtr> bread_image[3];

	easy_select->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		selected_num = 0;
		scene_game->enter();

		//client
		pick_client(ano_guest);

		//빵개수 랜덤
		const int iter = rand() % 3 + 1;

		//빵 15개 종류 중 랜덤하게 받은 개수만큼 vector에 넣어줌
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
		std::cout << "total: " << total << endl;

		cash = pick_cash(cash_image, total);

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

	auto menu_button = Object::create("images/메뉴확인.png", scene_game, 1150, 100);

	menu_button ->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene_menu->enter();
		return true;
		});

	auto up_for_5000 = Object::create("images/up_button.png", scene_game, 932, 273);
	auto down_for_5000 = Object::create("images/down_button.png", scene_game, 932, 238);
	auto up_for_1000 = Object::create("images/up_button.png", scene_game, 984, 273);
	auto down_for_1000 = Object::create("images/down_button.png", scene_game, 984, 238, true);
	auto up_for_500 = Object::create("images/up_button.png", scene_game, 1036, 273);
	auto down_for_500 = Object::create("images/down_button.png", scene_game, 1036, 238, true);
	auto up_for_100 = Object::create("images/up_button.png", scene_game, 1088, 273, true);
	auto down_for_100 = Object::create("images/down_button.png", scene_game, 1088, 238, true);
	auto done = Object::create("images/done.png", scene_game, 1040, 210);
	auto reset = Object::create("images/reset.png", scene_game, 930, 210);


	done->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (change == cash - total) {
			std::cout << "bingo" << endl;
		}
		else {
			std::cout << "wrong" << endl;
			std::cout << "your computation: " << change << endl;
			std::cout << "the right answer: " << total - cash << endl;
		}

		/*초기화*/
		cash_image->hide();
		cash = 0;
		change = 0;
		total = 0;
		while (!bread_image->empty()) {
			bread_image->back()->hide();
			cout << "refernce" << endl;
			bread_image->pop_back();
			cout << "pop out!" << endl;
		}

		pick_client(ano_guest);//손님 이미지 랜덤으로 보이게

		/*빵 오브젝트, 가격 저장*/
		vector <int> bread_price[3];
		const int iter = rand() % 3 + 1;
		std::cout << "iter: " << iter << endl;
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

		/*빵 가격에 맞는 돈 제시*/
		cash = pick_cash(cash_image, total);

		std::cout << "total: " << total << endl;

		return true;
		});

	up_for_100->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		change += 100;
		showingStatus(change);
		return true;
		});
	up_for_500->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		change += 500;
		showingStatus(change);
		return true;
		});
	up_for_1000->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		change += 1000;
		showingStatus(change);
		return true;
		});
	up_for_5000->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		change += 5000;
		showingStatus(change);
		return true;
		});
	down_for_100->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		change -= 100;
		showingStatus(change);
		return true;
		});
	down_for_500->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		change -= 500;
		showingStatus(change);
		return true;
		});
	down_for_1000->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		change -= 1000;
		showingStatus(change);
		return true;
		});
	down_for_5000->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		change -= 5000;
		showingStatus(change);
		return true;
		});



	startGame(scene_main);
	return 0;
}
