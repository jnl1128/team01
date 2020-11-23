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
    auto sceneIntro = Scene::create("intro", "images/메인화면.png");  //시작화면
    auto scene = Scene::create("easy mode", "images/background");
    auto scene2 = Scene::create("medium mode", "images/background");
    auto scene3 = Scene::create("hard mode", "images/background");

    auto easyButton = Object::create("images/easyButton.png", sceneIntro, 0, 0, true);
    auto mediumButton = Object::create("images/mediumButton.png", sceneIntro, 0, 0, true);
    auto hardButton = Object::create("images/hardButton.png", sceneIntro, 0, 0, true);


    Product order[3][3];
    int type = rand() % 3 + 1; // 빵 개수 1~3개 중 하나
    cout << "type: " << type << endl;
    for (int i = 0;i < 3;i++) {
        for (int j = 0; j < type; j++) {
            int which = rand() % 5;// 빵 종류 5개
            string which_bread = "images/bread" + to_string(which) + ".png";
            switch (which) {
            case 0:
                order[i][j].bread = Object::create(which_bread, scene, 0, 0, false);
                order[i][j].name = "bread0";
                order[i][j].cost = 500;
                //order.push_back(Product{ which_bread, 500 });   
                break;
            case 1:
                order[i][j].bread = Object::create(which_bread, scene, 0, 0, false);
                order[i][j].name = "bread1";
                order[i][j].cost = 700;
                //order.push_back(Product{ which_bread, 700 });
                break;
            case 2:
                order[i][j].bread = Object::create(which_bread, scene, 0, 0, false);
                order[i][j].name = "bread2";
                order[i][j].cost = 1000;
                //order.push_back(Product{ which_bread, 1000 });
                break;
            case 3:
                order[i][j].bread = Object::create(which_bread, scene, 0, 0, false);
                order[i][j].name = "bread3";
                order[i][j].cost = 1200;
                //order.push_back(Product{ which_bread, 1200 });
                break;
            case 4:
                order[i][j].bread = Object::create(which_bread, scene, 0, 0, false);
                order[i][j].name = "bread4";
                order[i][j].cost = 1500;
                //order.push_back(Product{ which_bread, 1500 });
                break;
            }
        }
    }
    Product(*orderPtr)[3] = order;      //2차원배열을 포인터형 변수에 넣어줌

    //메인화면에서 난이도 버튼을 누르면 화면이동
    easyButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
        scene->enter();
        //Sum(order);
        //showOrder(order);
        return true;
        });
    mediumButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
        scene2->enter();
        //Sum(order);
        //showOrder(order);
        return true;
        });
    easyButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
        scene3->enter();
        //Sum(order);
        //showOrder(order);
        return true;
        });



    Sum(*order);
    showOrder(*order);
    return 0;
}