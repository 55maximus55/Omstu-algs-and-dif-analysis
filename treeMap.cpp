//
// Created by p_rev on 20.02.2021.
//

#include <iostream>
#include <memory>
#include <vector>

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
template<typename type1, typename type2>
ostream &operator<<(ostream &stream, pair<type1, type2> p) {
    stream << p.first << " " << *p.second;
    return stream;
}