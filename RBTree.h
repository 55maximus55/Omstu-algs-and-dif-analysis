#pragma once

#include <iostream>
#include <string>

class RBTree {
    typedef enum {
        BLACK, RED
    } NodeColor;

    struct Node {

        int key;

        NodeColor color = BLACK;

        Node *parent = nullptr;
        Node *left = nullptr;
        Node *right = nullptr;

        Node(int key, NodeColor color, Node *left, Node *right) : key(key), color(color), left(left), right(right) {}

    };

    Node *head = nullptr;

    Node *getGrandparent(Node *node);
    Node *getUncle(Node *node);
    Node *getBrother(Node *node);

    void rotateLeft(Node *node);
    void rotateRight(Node *node);

public:

    void pr(std::string t, Node *node) {
        if (node != nullptr) {
            std::string col;
            if (node->color == BLACK)
                col = "black";
            else
                col = "red";

            std::cout << t << " " << node->key << " (" << col << ")" << ": ";
            std::cout << "p("; if (node->parent != nullptr) std::cout << node->parent->key; else std::cout << "null"; std::cout << "),";
            std::cout << "l("; if (node->left != nullptr) std::cout << node->left->key; else std::cout << "null"; std::cout << "),";
            std::cout << "r("; if (node->right != nullptr) std::cout << node->right->key; else std::cout << "null"; std::cout << ")";
            std::cout << "\n";

            pr(t + "l", node->left);
            pr(t + "r", node->right);
        }
    }
    void printTree() {
        pr("", head);
    }

    void insert(int key);
    void insertFix(Node *node);

    void remove(int key);
    void removeFix(Node *node);

};