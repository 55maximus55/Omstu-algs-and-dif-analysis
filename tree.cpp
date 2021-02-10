#include <vector>
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
    Node *head = nullptr;
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
    void readTree(Node *Head) {
        if(Head != nullptr){
            if (Head->left != nullptr) readTree(Head->left);
            sorted.push_back(Head->value);
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
                // заменяем value у target на найденный лист, и удаляем лист
                target->value = leaf->value;
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
    // нахождение по значению
    auto findNode(value_type value) {
        auto current = head;
        while (current != nullptr && current->value != value) {
            current = (value < current->value ? current->left :
                       current->right);
        }
        return current;
    }
    // добавление узла
    void push(value_type value) {
        Node *current = head;
        while ((value < current->value ? current->left : current->right) !=
               nullptr) {
            current = value < current->value ? current->left :
                      current->right;
        }
        if (value < current->value) {
            current->left = new Node(value);
            current->left->parent = current;
        } else {
            current->right = new Node(value);
            current->right->parent = current;
        }
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