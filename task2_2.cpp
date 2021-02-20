#include <cstdlib>
#include <memory>

/*
 *
 * Оператор мобильной связи организовал базу данных абонентов,
 * содержащую сведения о телефонах, их владельцах и используемых тарифах, в виде бинарного дерева.
 *
 * Разработать программу, которая:
 * обеспечивает начальное формирование базы данных в виде бинарного дерева;
 * производит вывод всей базы данных;
 * производит поиск владельца по номеру телефона;
 * выводит наиболее востребованный тариф (по наибольшему числу абонентов).
 *
 * */

#include <bitset>
#include <vector>
#include <tuple>
#include <iostream>
#include "treeMap.cpp"
using namespace std;



class Person {
public:
    string firstName = "";
    string secondName = "";
    int tariffID = 0;

    Person(const string &firstName, const string &secondName, int tariffId) : firstName(firstName),
                                                                              secondName(secondName),
                                                                              tariffID(tariffId) {}

};

ostream &operator<<(ostream &stream, Person person) {
    stream << person.tariffID << " " << person.firstName << " " << person.secondName;
    return stream;
}


int main() {
    auto personsMap = TreeMap<long long, Person>();
    auto tariffCountMap = TreeMap<int, int>();

    personsMap.push(88005553535, Person("Igor", "Nikolaev", 0));
    personsMap.push(88005553536, Person("Kolya", "Nikolaev", 1));
    personsMap.push(88005553537, Person("Denis", "Nikolaev", 2));
    personsMap.push(88005553538, Person("Igor", "Nikolaev", 1));
    personsMap.push(88005553539, Person("Igor", "Nikolaev", 0));
    personsMap.push(88005553510, Person("Igor", "Nikolaev", 3));
    personsMap.push(88005553511, Person("Igor", "Nikolaev", 0));
    personsMap.push(88005553512, Person("Igor", "Nikolaev", 3));
    personsMap.push(88005553513, Person("Igor", "Nikolaev", 3));
    personsMap.push(88005553514, Person("Igor", "Nikolaev", 3));

    for (auto item : personsMap) {
        cout << item << endl;

        auto tariffID = item.second->tariffID;
        if (tariffCountMap.isContains(tariffID)) {
            tariffCountMap.findNode(tariffID)->value++;
        } else {
            tariffCountMap.push(tariffID, 1);
        }
    }
    cout << endl;

    auto t = tariffCountMap.begin();
    auto max = make_pair(t->first, t->second);
    for (auto item : tariffCountMap) {
        if (max.second < item.second) {
            max.first = item.first;
            max.second = item.second;
        }
    }
    cout << "Most popular tariff: " << max.first << endl;

    return EXIT_SUCCESS;
}