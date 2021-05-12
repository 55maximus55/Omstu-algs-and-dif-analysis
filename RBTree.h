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

        Node(int key) : key(key) {}

    };

    Node *head = nullptr;

    Node *getGrandparent(Node *node);
    Node *getUncle(Node *node);

    void rotateLeft(Node *node);
    void rotateRight(Node *node);

    void insertCase1(Node *node);
    void insertCase2(Node *node);
    void insertCase3(Node *node);
    void insertCase4(Node *node);
    void insertCase5(Node *node);

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

    void insert(int key) {
        if (head == nullptr)
            head = new Node(key);
        else {
            Node *node = head;
            while (key < node->key && node->left != nullptr || key > node->key && node->right != nullptr) {
                if (key > node->key)
                    node = node->right;
                else
                    node = node->left;
            }

            Node *child = new Node(key);
            child->parent = node;
            child->color = RED;
            if (key > node->key)
                node->right = child;
            else
                node->left = child;

            insertCase1(node);
        }
    }
    void remove(int key) {

    }

};