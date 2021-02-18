#include <cstdlib>
#include <iostream>

/*
 * Дана последовательность числовых значений.
 * Признак окончания последовательности введенный ноль.
 * Требуется написать программу, которая на основе частотного анализа числовой последовательности формирует таблицу,
 * в первом столбце стоят значения элементов, во втором столбце частота появления соответствующего числа.
 * Данные должны выдаваться в порядке возрастания числовых значений.
 * Оценить сложность алгоритма и время выполнения.
 *
 * */

#include <bitset>
#include <vector>
#include <tuple>

using namespace std;

template<typename value_type>
class TreeMap {
private:
    struct Node {
        value_type key;
        int count = 1;

        Node *left = nullptr, *right = nullptr;

        explicit Node(value_type value) : key(value) {
        }
    };

    Node *head = nullptr;
    vector<pair<value_type, int>> sorted;

    template<typename Iterator>
    void makeTree(Iterator begin, Iterator end) {
        ++begin;
        for (; begin != end; ++begin) {
            push(*begin);
        }
    }

    // чтение дерева из запись в sorted
    void readTree(Node *Head){
        if (Head->left != nullptr) readTree(Head->left);
        sorted.template emplace_back(Head->key, Head->count);
        if (Head->right != nullptr) readTree(Head->right);
    }

    // удаление всей ветки
    void deleteBranch(Node *node) {
        if (node->left != nullptr) deleteBranch(node->left);
        if (node->right != nullptr) deleteBranch(node->right);
        delete node;
    }


public:

    TreeMap() {

    }

    // нахождение по значению
    auto findNode(value_type value) {
        auto current = head;
        while (current != nullptr && current->key != value) {
            current = (value < current->key ? current->left : current->right);
        }
//        if(current == nullptr) throw logic_error("curent nullptr");
        return current;
    }

    // добавление узла
    void push(value_type value) {
        auto kek = findNode(value);
        if (kek != nullptr) {
            kek->count++;
        } else {
            if (head == nullptr) {
                head = new Node(value);
            } else {
                Node *current = head;
                while ((value < current->key ? current->left : current->right) != nullptr) {
                    current = value < current->key ? current->left : current->right;
                }

                if (value < current->key) {
                    current->left = new Node(value);
                } else {
                    current->right = new Node(value);
                }
            }
        }
    }

    auto begin() const {
        sorted.clear();
        readTree(head);
        return sorted.begin(); }

    auto end() const {
        return sorted.end(); }

    auto begin() {
        sorted.clear();
        readTree(head);
        return sorted.begin(); }

    auto end() {
        return sorted.end(); }

    ~TreeMap() {
        deleteBranch(head);
    }
};

int main() {
    auto tree = TreeMap<int>();

    while (true) {
        int t;
        cin >> t;
        if (t == 0)
            break;
        else
            tree.push(t);
    }

    for (auto item : tree) {
        cout << item.first << "\t" << item.second << endl;
    }

    return EXIT_SUCCESS;
}