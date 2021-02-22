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

        explicit Node() = default;

        void setValue(const value_type &value) {
            this->value = value;
        }
    };

public:
    Node *head;

    //проверка на количество скобок
    bool checkValidate(const string &line) {
        int counter = 0;
        for (const auto &item: line) {
            if (item == '(') counter++;
            if (item == ')') counter--;
        }
        return counter == 0;
    }

    string removeAllSpaces(const string &line) {
        string result;
        for (const auto &item: line) {
            if (item != ' ') result.push_back(item);
        }
        return result;
    }

    //удаление боковых ненужных скобок
    bool trimBrackets(string &line) {
        if (line.front() == '(') {
            size_t counter = 0;
            for (int i = 0; i < line.length(); ++i) {
                if (line[i] == '(') counter++;
                else if (line[i] == ')') counter--;
                if (counter == 0 && i != line.length() - 1) return false;
            }
            line = string(line.begin() + 1, line.end() - 1);
            return true;
        }
        return false;

    }

    //деление строки и создание узла
    void makeNode(string line, Node *current) {
        //удаление всех ненужных скобок
        while (trimBrackets(line));
        // pos - позиция операции
        // bCounter - счетчик скобок
        int pos = string::npos,
                bCouter = 0;
        for (int i = 0; i < line.length(); i++) {
            if (line[i] == '(') bCouter++;
            else if (line[i] == ')') bCouter--;
            if (bCouter == 0) {
                if (line[i] == '+' || line[i] == '-') pos = i;
                else if ((pos == string::npos || (line[pos] == '*' || line[pos] == '/')) &&
                         (line[i] == '*' || line[i] == '/'))
                    pos = i;
            }
        }
        line;

        char onPos = line[pos];
        if (pos != string::npos) {
            //если в строке есть оператор

            //присваиваем оператор value
            current->setValue(string{line[pos]});

            // отправляем левую часть на обработку
            if (!line.substr(0, pos).empty()) {
                current->left = new Node();
                string temp = line.substr(0, pos);
                makeNode(line.substr(0, pos), current->left);
            }
            //правую часть на обработку
            if (!line.substr(pos + 1, string::npos).empty()) {
                current->right = new Node();
                string temp = line.substr(pos + 1, string::npos);
                makeNode(line.substr(pos + 1, string::npos), current->right);
            }

        } else {
            //если в строке нет оператора
            current->setValue(line);
        }

    }

    Tree(string line) {
        head = new Node();
        if (!checkValidate(line)) throw logic_error("wrong number of brackets");
        makeNode(removeAllSpaces(line), head);
    }

    void printNode(Node *node) {
        if (node->left != nullptr) printNode(node->left);
        if (node->right != nullptr) printNode(node->right);
        cout << " " << node->value << " ";
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
    auto t = Tree<string>(
            "-(12 + 13) * 14 / (-74 + 2)"
    );

    //шоб нормально подсвечивался конструктор
    t.printNode(t.head);
    cout << endl << t.calculateNode(t.head) << endl;

    return EXIT_SUCCESS;
}