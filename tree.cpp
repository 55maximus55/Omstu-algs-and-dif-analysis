#include <iostream>
#include <bitset>
#include <vector>
#include <tuple>

using namespace std;

template<typename value_type>
class Tree {
private:
    struct Node {
        value_type value;
        Node *left = nullptr, *right = nullptr;
        Node *parent = nullptr;

        explicit Node(value_type value) : value(value) {
        }
    };

    Node *head;
    vector<value_type> sorted;

    template<typename Iterator>
    void makeTree(Iterator begin, Iterator end) {
        ++begin;
        for (; begin != end; ++begin) {
            push(*begin);
        }
    }

    // удаление одного узла
    void deleteNode(Node *node) {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
        }

    }

    // чтение дерева из запись в sorted
    void readTree(Node *Head){
        if (Head->left != nullptr) readTree(Head->left);
        sorted.push_back(Head->value);
        if (Head->right != nullptr) readTree(Head->right);
    }

    // удаление всей ветки
    void deleteBranch(Node *node) {
        if (node->left != nullptr) deleteBranch(node->left);
        if (node->right != nullptr) deleteBranch(node->right);
        delete node;
    }


public:
    template<typename Iterator>
    Tree(Iterator begin, Iterator end) {
        if (begin != end) {
            head = new Node(*begin);
            makeTree(begin, end);
            readTree(head);
        }
    }

    Tree(const vector<value_type> vec) : Tree(vec.begin(), vec.end()) {}

    // удаление по значению
    bool deleteByValue(value_type value) {
        Node *target = findNode(value);

        if (target != nullptr) {
            //удаление, если нет потомков / голова
            if(target->left == nullptr && target->right == nullptr){
                if(target->parent != nullptr){
                    target = target->parent;
                    if(target->left->value == value){
                        delete target->left;
                        target->left = nullptr;
                    }
                    else{
                        delete target->right;
                        target->right = nullptr;
                    }
                }
                else{
                    delete head;
                    head = nullptr;
                }
            }
                //удаление, если есть оба потомка
            else if (target->left != nullptr && target->right != nullptr) {
                /*

                  target->value = findLeaf->value;
                  Node *findLeaf = target->right;
                while (findLeaf->left != nullptr)
                    if (findLeaf->left != nullptr)
                        findLeaf = findLeaf->left;


                  if (findLeaf->parent->right == findLeaf)
                      findLeaf->parent->right = findLeaf->left;
                  if (findLeaf->parent->left == findLeaf)
                      findLeaf->parent->left = findLeaf->right;
                  delete findLeaf;*/

                Node* current = target->right,
                        *lastL = target->right;
                while(current != nullptr){
                    if(current->left != nullptr)
                        lastL = current;
                    current = current->left;
                }
                if(lastL == target->right)
                    lastL->parent->right = lastL->right;
                else
                    lastL->parent->left = lastL->right;
                target->value = lastL->value;
                delete lastL;


            }
            else{
                auto prev = target->parent;
                // удаление, когда один потомок (не голова)
                if(prev != nullptr){
                    if(target->value < prev->value){
                        prev->left = target->left != nullptr ? target->left: target->right;
                        delete target;
                    }
                }
                    //удаление, когда один потомок у головы
                else{
                    head = target->left != nullptr? target->left : target->right;
                    delete target;
                }
            }
            return true;
        }

        return false;
    }

    // нахождение по значению
    auto findNode(value_type value) {
        auto current = head;
        while (current != nullptr && current->value != value) {
            current = (value < current->value ? current->left : current->right);
        }
        if(current == nullptr) throw logic_error("curent nullptr");
        return current;
    }

    // добавление узла
    void push(value_type value) {
        Node *current = head;
        while ((value < current->value ? current->left : current->right) != nullptr) {
            current = value < current->value ? current->left : current->right;
        }

        if (value < current->value)
        {
            current->left = new Node(value);
            current->left->parent = current;
        }
        else
        {
            current->right = new Node(value);
            current->right->parent = current;
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

    ~Tree() {
        deleteBranch(head);
    }
};



