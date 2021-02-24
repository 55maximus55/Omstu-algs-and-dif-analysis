#include <iostream>
#include <cstdlib>

using namespace std;

/*
 * Будем считать, что формула состоит из числовых значений, круглых скобок и операций (+, *, /, -).
 * Написать программу, которая по формуле, представленной строкой, формирует формулу в постфиксной записи.
 * Оценить сложность алгоритма и время выполнения.
 *
 * */
template<typename value_type>
class Tree {
private:
    struct Node {
        value_type value;
        Node *left = nullptr, *right = nullptr;

        // 1
        explicit Node() = default;

        // 1
        void setValue(const value_type &value) {
            this->value = value; // 1
        }
    };

public:
    Node *head;

    //проверка на количество скобок
    // 2n
    bool checkValidate(const string &line) {
        int counter = 0; // 1
        // 2n
        for (const auto &item: line) { // n line.length
            if (item == '(') counter++; // 1
            if (item == ')') counter--; // 1
        }
        return counter == 0;
    }

    // n
    string removeAllSpaces(const string &line) {
        string result;// 1
        for (const auto &item: line) { // n
            if (item != ' ') result.push_back(item); // 1
        }
        return result; // 1
    }

    //удаление боковых ненужных скобок
    // 3n - 2
    bool trimBrackets(string &line) {

        if (line.front() == '(') {
            size_t counter = 0; // 1
            for (int i = 0; i < line.length(); ++i) { // 2n
                if (line[i] == '(') counter++;
                else if (line[i] == ')') counter--; // 1
                if (counter == 0 && i != line.length() - 1) return false; // 1
            }
            line = string(line.begin() + 1, line.end() - 1); // n - 2
            return true;
        } // 2n + n - 2
        return false;
    }

    //деление строки и создание узла
    // n^2 + log2 n + n
    void makeNode(string line, Node *current) {
        //удаление всех ненужных скобок
        while (trimBrackets(line));                                 // n/2 (3n - 2)
        // pos - позиция операции
        // bCounter - счетчик скобок
                                                                        // 2
        int pos = string::npos, // 1
                bCouter = 0; // 1
                                                                        // 2n
        for (int i = 0; i < line.length(); i++) { // n
            if (line[i] == '(') bCouter++;
            else if (line[i] == ')') bCouter--; // 1
            //  1
            if (bCouter == 0) {
                if (line[i] == '+' || line[i] == '-')
                    pos = i; // 1
                else if ((pos == string::npos || (line[pos] == '*' || line[pos] == '/')) &&
                         (line[i] == '*' || line[i] == '/'))
                    pos = i; // 1
            }
        }

        if (pos != string::npos) {
            //если в строке есть оператор

            //присваиваем оператор value

            // 1
            current->setValue(string{line[pos]});       // 1

            // отправляем левую часть на обработку
            if (!line.substr(0, pos).empty()) {                                 // log2 n + 2
                current->left = new Node();                     // 1
                string temp = line.substr(0, pos);         // 1
                makeNode(line.substr(0, pos), current->left); // log2 n
            }
            //правую часть на обработку
            if (!line.substr(pos + 1, string::npos).empty()) {                  // log2 n + 2
                current->right = new Node();
                string temp = line.substr(pos + 1, string::npos);
                makeNode(line.substr(pos + 1, string::npos), current->right);
            }

        } else {
            //если в строке нет оператора
            current->setValue(line); // 1
        }

    }

    // n ^ 2
    Tree(string line) {
        head = new Node(); // 1
        if (!checkValidate(line)) throw logic_error("wrong number of brackets"); // 1
        makeNode(removeAllSpaces(line), head); // n^2
    }

    // 2log2 n
    void printNode(Node *node) {

        if (node->left != nullptr) printNode(node->left); // log2 n
        if (node->right != nullptr) printNode(node->right); // log2 n
        cout << " " << node->value << " "; // 1
    }

    double calculateNode(Node *node) {
        if (node->value == "+") {
            if (!node->left && !node->right) throw logic_error("'+' is a binary operator, expects 2 values");
            if (!node->left && node->right) return calculateNode(node->right);
            return calculateNode(node->left) + calculateNode(node->right);
        }
        if (node->value == "-") {
            if (!node->left && !node->right) throw logic_error("'-' is a binary operator, expects 2 values");
            if (!node->left && node->right) return -calculateNode(node->right);
            return calculateNode(node->left) - calculateNode(node->right);
        }
        if (node->value == "*") {
            if (!node->left || !node->right) throw logic_error("'*' is a binary operator, expects 2 values");
            return calculateNode(node->left) * calculateNode(node->right);
        }
        if (node->value == "/") {
            if (!node->left || !node->right) throw logic_error("'/' is a binary operator, expects 2 values");
            return calculateNode(node->left) / calculateNode(node->right);
        }
        return stod(node->value);
    }

};


int main() {
    // n^2
    auto t = Tree<string>(
            "-(12 + 13) * 14 / (-74 + 2)"
    );

    //шоб нормально подсвечивался конструктор
    t.printNode(t.head);
    cout << endl << t.calculateNode(t.head) << endl;

    return EXIT_SUCCESS;
}