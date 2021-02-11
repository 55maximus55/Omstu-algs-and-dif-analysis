#include <vector>
#include <iostream>
using namespace std;

template<typename key_type, typename value_type>
class Tree {
private:
    struct Node {
        key_type key;
        value_type value;

        Node *left = nullptr, *right = nullptr;
        Node *parent = nullptr;
        explicit Node(pair<key_type,value_type> p) : key(p.first), value(p.second) {
        }
    };

    Node *head = nullptr;

    vector<value_type*> sorted;


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
    void readTree(Node *Head) {
        if(Head != nullptr){
            if (Head->left != nullptr) readTree(Head->left);
            sorted.push_back(&Head->value);
            if (Head->right != nullptr) readTree(Head->right);
        }
    }
    // удаление всей ветки
    void deleteBranch(Node *node) {
        if (node->left != nullptr) deleteBranch(node->left);
        if (node->right != nullptr) deleteBranch(node->right);
        delete node;
    }

public:
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
    Node& operator[](key_type key){
        auto node = findNode(key);
        if(node == nullptr){
            node = push({key, *new value_type()});
        }
        return *node;
    }

public:
    template<typename Iterator>
    Tree(Iterator begin, Iterator end) {
        if (begin != end) {
            head = new Node(*begin);
            makeTree(begin, end);
        }
    }
    Tree(const vector<pair<key_type, value_type>> vec) : Tree(vec.begin(), vec.end()) {}


    // добавление узла
    auto push(pair<key_type,value_type> newNode) {
        Node* check = findNode(newNode.first);
        if(check != nullptr){
            check->value = newNode.second;
        }
        else
        {
            Node *current = head;
            while ((newNode.first < current->key ? current->left : current->right) !=
                   nullptr) {
                current = newNode.first < current->key ? current->left :
                          current->right;
            }
            if (newNode.first < current->key) {
                current->left = new Node(newNode);
                current->left->parent = current;
                return current->left;
            } else {
                current->right = new Node(newNode);
                current->right->parent = current;
                return current->right;
            }

        }

    }
    // удаление по значению ключа
    bool pop(key_type key) {
        Node *target = findNode(key);
        if (target != nullptr) {

            //нет потомков
            if (target->left == nullptr && target->right == nullptr) {
                auto parrot = target->parent;
                // не голова
                if(parrot != nullptr){
                    if(parrot->left == target){
                        parrot->left = nullptr;
                    }
                    else{
                        parrot->right = nullptr;
                    }
                }
                    //голова
                else{
                    head = nullptr;
                }
                delete target;
            }
                // один левый потомок
            else if (target->left != nullptr && target->right == nullptr) {
                auto parent = target->parent;
                // не голова
                if(parent != nullptr){
                    if(parent->left == target){
                        parent->left = target->left;
                    }
                    else{
                        parent->right = target->left;
                    }
                    target->left->parent = parent;
                }
                    // голова
                else{
                    target->left->parent = nullptr;
                    head = target->left;
                }
                delete target;
            }
                // один правый потомок
            else if (target->left == nullptr && target->right != nullptr){
                auto parent = target->parent;
                // не голова
                if (parent != nullptr) {
                    if (parent->right == target) {
                        parent->right = target->right;
                    }
                    else {
                        parent->left = target->right;
                    }
                    target->right->parent = parent;
                }
                    // голова
                else {
                    target->right->parent = nullptr;
                    head = target->right;
                }
                delete target;
            }
                // два потомка
            else {
                // ищем заменяемую Node
                Node *leaf = target->left;
                while (leaf->right != nullptr) {
                    leaf = leaf->right;
                }
                // заменяем key у target на найденный лист, и удаляем лист
                target->key = leaf->key;
                target->value = target->value;
                if (leaf->parent->right == leaf) {
                    leaf->parent->right = nullptr;
                    delete leaf;
                } else if (leaf->parent->left == leaf) {
                    leaf->parent->left = nullptr;
                    delete leaf;
                }
            }
        }
        return false;
    }

    auto begin() {
        sorted.clear();
        readTree(head);
        return sorted.begin();
    }
    auto end() {
        return sorted.end();
    }

    ~Tree() {
        if(head != nullptr)
            deleteBranch(head);
    }
};
