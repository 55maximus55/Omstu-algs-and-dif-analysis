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

using namespace std;

template<typename key_type, typename value_type>
class TreeMap {
private:
    struct Node {
        key_type key;
        value_type value;

        Node *left = nullptr, *right = nullptr;

        explicit Node(key_type key, value_type value) : key(key), value(value) {
        }
    };


    Node *head = nullptr;

    template<typename Iterator>
    void makeTree(Iterator begin, Iterator end) {
        ++begin;
        for (; begin != end; ++begin) {
            push(*begin);
        }
    }

    // удаление всей ветки
    void deleteBranch(Node *node) {
        if (node != nullptr) {
            if (node->left != nullptr) deleteBranch(node->left);
            if (node->right != nullptr) deleteBranch(node->right);
            delete node;
        }
    }


public:
    TreeMap() {

    }

    // нахождение по значению
    auto findNode(key_type key) {
        auto current = head;
        while (current != nullptr && current->key != key) {
            current = (key < current->key ? current->left :
                       current->right);
        }
        return current;
    }

    //// VALUE обязан иметь конструктор по умолчанию
    Node &operator[](key_type key) {
        auto node = findNode(key);
        if (node == nullptr) {
            node = push({key, *new value_type()});
        }
        return *node;
    }

    // добавление узла
    void push(key_type key, value_type value) {
        if (head == nullptr) {
            head = new Node(key, value);
        } else {
            Node *current = head;
            while ((key < current->key ? current->left : current->right) != nullptr) {
                current = key < current->key ? current->left : current->right;
            }

            if (key < current->key) {
                current->left = new Node(key, value);
            } else {
                current->right = new Node(key, value);
            }
        }
    }

    bool isContains(key_type key) {
        return findNode(key) != nullptr;
    }


    vector<pair<key_type, shared_ptr<value_type>>> container;

    void containerUpdate(const Node current) {
        if (current.left != nullptr) containerUpdate(*current.left);
        container.push_back(make_pair(current.key, make_shared<value_type>(current.value)));
        if (current.right != nullptr) containerUpdate(*current.right);
    }

    auto begin() {
        container.clear();
        containerUpdate(*head);
        return container.begin();
    }

    auto end() {
        return container.end();
    }

    ~TreeMap() {
        deleteBranch(head);
    }
};

class Person {
public:
    string firstName = "";
    string secondName = "";
    int tariffID = 0;

    Person(const string &firstName, const string &secondName, int tariffId) : firstName(firstName),
                                                                              secondName(secondName),
                                                                              tariffID(tariffId) {}

};

template<typename type1, typename type2>
ostream &operator<<(ostream &stream, pair<type1, type2> p) {
    stream << p.first << " " << *p.second;
    return stream;
}

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