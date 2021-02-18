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

    Tree() {

    }
    // нахождение по значению
    auto findNode(value_type value) {
        auto current = head;
        while (current != nullptr && current->value != value) {
            current = (value < current->value ? current->left :
                       current->right);
        }
//        if(current == nullptr) throw logic_error("curent nullptr");
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

    auto begin() const {
        sorted.clear();
        readTree(head);
        return sorted.begin();
    }

    auto end() const {
        return sorted.end(); }

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