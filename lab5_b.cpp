#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <typeinfo>

using namespace std;

class A {
public:
    string s;

    A() {
        cout << "Конструктор по умолчанию класса A" << endl;
    }

    A(const char* a) {
        s = a;
        cout << "Пользовательский Конструктор класса A" << endl;
        cout << s << endl;
    }

    virtual ~A() {
        cout << "Деструктор класса A" << endl;
        cout << typeid(*this).name() << endl;
    }
};

class B : public A {
public:
    B() {
        cout << "Конструктор класса B" << endl;
    }

    B(const char* a) : A(a) {
        cout << "Пользовательский Конструктор класса B" << endl;
        cout << a << endl;
    }

    ~B() {
        cout << "Деструктор класса B" << endl;
        cout << typeid(*this).name() << endl;
    }
};

void del(vector<A*>& v) { //объявление функции del, которая принимает вектор указателей на объекты класса A.
    for (int i = 0; i < v.size(); i++) {
        delete v[i];
    }
    v.clear(); // Очистка вектора
}

int main() {
    list<A*> l;
    l.push_back(new A("first"));  //добавление в список указателя на объект класса A, созданный с помощью пользовательского конструктора и передачей ему строки "first".
    l.push_back(new B("second")); //добавление в список указателя на объект класса B, созданный с помощью пользовательского конструктора и передачей ему строки "second".

    vector<A*> v(l.begin(), l.end()); // Копирование из списка в вектор

    del(v); //вызов функции del для удаления объектов, на которые указывают элементы вектора, и очистки вектора.

    return 0;
}
