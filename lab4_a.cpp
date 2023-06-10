#include <crtdbg.h>
#include <iostream>  
#include <fstream>  
#include <string>  
#include <vector>  
#include <sstream>  
#include <algorithm>
using namespace std;
struct Leaks { //структура leaks, которая вызывает функцию при завершении программы для поиска утечек памяти
    ~Leaks() { _CrtDumpMemoryLeaks(); }
}_l;

class Employee {
private:
    const string _name; //поля класса
    const int _yearOfBirth;
    const string _position;
    int _groupNumber;
public:
    Employee(const string& n, const int& y, const  string& p, const int& g) : _name(n), _yearOfBirth(y), _position(p), _groupNumber(g) {}

    int getBirthYear() const {
        return _yearOfBirth;
    }
     string getPosition() const {
        return _position;
    }
    void printInfo() const {
         cout << _name << ", " << _yearOfBirth << ", " << _position << ", " << "группа " << _groupNumber <<  endl;
         cout <<  endl;
    }
};

class Database { //класс, который представляет базу данных сотрудников
private:
     vector<Employee*> employees; // вектор указателей на объекты класса
public:
    void addEmployee(Employee* e) {
        employees.push_back(e);
    }

    void printAllEmployees() const {
        for (const auto& employee : employees) {
            employee->printInfo();
        }
    }

    void printAllEngineers() const {
         for_each(employees.begin(), employees.end(), [](const Employee* e) {
            if (e->getPosition() == "инженер") {
                e->printInfo();
            }
            });
    }
    void printAllNonPresidents() const {
         vector<Employee*> nonPresidents;
        for (const auto& employee : employees) {
            if (employee->getPosition() != "председатель") {
                nonPresidents.push_back(employee);
            }
        }
         sort(nonPresidents.begin(), nonPresidents.end(), [](const Employee* a, const Employee* b) {
            return a->getBirthYear() < b->getBirthYear();
            });

        for (const auto& employee : nonPresidents) {
            employee->printInfo();
        }
    }
    ~Database() {
        for (const auto& employee : employees) {
            delete employee;
        }
    }
};
int main() {
    setlocale(LC_ALL, "RUS");
    Database db; //объект класса
     string _name, _position, _group;
    int _yearOfBirth, _groupNumber;
     string path = "baza_dan.txt";
     ifstream file;
    file.open(path);
    if (!file.is_open()) {
         cout << "Error" <<  endl;
    }
    else
    {
         cout << "Open!" <<  endl; //вывод о успешном открытии файла
         string line;
        while (getline(file, line)) {
             stringstream ss(line);
            getline(ss, _name, ',');
            ss >> _yearOfBirth >>  ws;
            getline(ss, _position, ',');
            ss >> _group >>  ws;
            ss >> _groupNumber;
            Employee* e = new Employee(_name, _yearOfBirth, _position, _groupNumber); //создание объекта класса employee на основе прочитанных данных
            db.addEmployee(e); //добавление объекта в базу данных
        }
        file.close();
    }
     cout << "Общая база данных:" <<  endl; //вывод заголовка раздела информации о всех сотрудниках
     cout << "----" <<  endl;
    db.printAllEmployees(); //вызов метода класса database для вывода информации обо всех сотрудниках
     cout << "----" <<  endl;
     cout << "Информация об инженерах:" <<  endl;
     cout <<  endl;
     cout << "---" <<  endl;
    db.printAllEngineers(); //вывод информации о всех инженерх
     cout << "-----" <<  endl;
     cout << "Информация о всех не председателях:" <<  endl;
     cout <<  endl;
     cout << "-----" <<  endl;
    db.printAllNonPresidents(); // вывод информации обо всех сотрудниках, кроме председателей
    return 0;
}