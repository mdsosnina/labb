#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>

struct Reference { //структура
    std::string author;
    std::string title;
    std::string year;
    std::string page;
};
bool isRussian(char ch) { //функция,проверяет является ли символ русским

    if (ch >= 0 && ch <= 127) {
        return false;
    }
    return true;
}

void printReferences(const std::vector<Reference>& references, bool withNumbers) { //определение функции, которая проверяется, является ли символ русским
    for (size_t i = 0; i < references.size(); i++) {
        if (withNumbers) {
            std::cout << i + 1 << ". ";
        }
        std::cout << references[i].author << " " << references[i].year << ". " << references[i].title << " " << references[i].page << std::endl;
    }
}

int main() { //определение функции, которая является точкой входа в программу
    setlocale(LC_ALL, "RUS");
    std::vector <Reference> references; //создание пустого вектора references, который будет хранить ссылки
    std::ifstream file("baza_dan.txt"); 
    if (!file.is_open()) { // проверка, удалось ли открыть файл
        std::cout << "Ошибка открытия файла." << std::endl;
        return 1;
    }

    std::string line;
    while (getline(file, line)) { //чтение файла построчно и обработка каждой строки
        std::string author, title, year, page; //создание переменных для хранения информации об одной ссылке
        std::istringstream iss(line); //создание строкового потока для обработки строки
        getline(iss, author, ','); //чтение автора из строки
        getline(iss, year, ','); //чтение года из строки
        getline(iss, title, ','); //чтение названия из строки
        iss >> page; //чтение страницы из строки
        Reference ref = { author, title, year, page }; //создание объекта на основе прочитанных данных
        references.push_back(ref); //добавление ссылки в вектор
    }
    file.close();


    sort(references.begin(), references.end(), [](const Reference& a, const Reference& b) { //сортировка ссылок по автору с учетом русских символов

        if (isRussian(a.author[0]) && !isRussian(b.author[0])) { 
            return true;
        }
        else if (!isRussian(a.author[0]) && isRussian(b.author[0])) {
            return false;
        }
        else {
            return a.author < b.author;
        }
        });

    std::cout << "Список литературы (с номерами):" << std::endl; //выводм заголовка списка ссылок с номерами на экран
    printReferences(references, true);

    std::cout << std::endl << "Список литературы (без номеров):" << std::endl;
    printReferences(references, false); //вывод списка ссылок без номеров на экран

    return 0;
}