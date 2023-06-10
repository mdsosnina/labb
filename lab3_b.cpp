#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;
class Detail
{
protected:
    Detail() = default;//конструктор по умолчанию
    virtual ~Detail() = default; //виртуальный диструктор по умолчанию
};
class Assembly : public Detail // класс assembly который наследуется от базового класса detail
{
protected: //функция fillvector как друг класса assembly чтобы она могла получать доступ к защищенным членам класса
    friend void FillVector(vector<Assembly>* vec); 
    explicit Assembly(const string& detail_info) : detail(detail_info) { //объявляет конструктор класса assembly который принимает строку detail_info и инициализирует член detail этой строкой
        cout << "Assembly constructor is called." << endl; //выводит сообщение о вызове конструктора
    }
    const string& getDetail() const { //объявляет метод getDetail который возвращает константную ссылку на член detail
        return detail;
    }
private: //объявляет член detail коасса assembly приватным
    string detail;
};
void FillVector(vector<Assembly>* vec) { //объявляет функцию fillvector которая принимает указатель на вектор vec
    for (int i = 0; i < 5; ++i)
    {
        auto a = unique_ptr<Assembly>(new Assembly("Detail #" + to_string(i))); //умный казатель а на объект класса assembly, который инициализируется строкой Detail# и номером итерации цикла
        vec->push_back(move(*a)); //добавляет объект, на который указывает умный указатель а, в конец вектора vec
    }
}
vector<Assembly> vec; //вызывает вектор vec, который содержит объекты класса assembly
int main() {
    FillVector(&vec); //вызывает функцию fillvector передавая ей адрес вектора vec
    for (auto i = vec.begin(); i != vec.end(); i++) //перебор всех элементов вектора vec
    {
        cout << i->getDetail() << endl; //
    }
    return 0;
}