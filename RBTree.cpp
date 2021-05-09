#include "RBTree.h"

void RBTree::rotateLeft(Node *node) {
    Node *pivot = node->right;

    pivot->parent = node->parent; /* при этом, возможно, pivot становится корнем дерева */
    if (node->parent != nullptr) {
        if (node->parent->left == node)
            node->parent->left = pivot;
        else
            node->parent->right = pivot;
    } else {
        head = pivot;
    }

    node->right = pivot->left;
    if (pivot->left != nullptr)
        pivot->left->parent = node;

    node->parent = pivot;
    pivot->left = node;
}

void RBTree::rotateRight(Node *node) {
    Node *pivot = node->left;

    pivot->parent = node->parent; /* при этом, возможно, pivot становится корнем дерева */
    if (node->parent != nullptr) {
        if (node->parent->left == node)
            node->parent->left = pivot;
        else
            node->parent->right = pivot;
    } else {
        head = pivot;
    }

    node->left = pivot->right;
    if (pivot->right != nullptr)
        pivot->right->parent = node;

    node->parent = pivot;
    pivot->right = node;
}

RBTree::Node *RBTree::getGrandparent(RBTree::Node *node) {
    if ((node != nullptr) && (node->parent != nullptr))
        return node->parent->parent;
    else
        return nullptr;
}

RBTree::Node *RBTree::getUncle(RBTree::Node *node) {
    Node *grandparent = getGrandparent(node);
    if (grandparent == nullptr)
        return nullptr; // No grandparent means no uncle
    if (node->parent == grandparent->left)
        return grandparent->right;
    else
        return grandparent->left;
}

void RBTree::insertCase1(RBTree::Node *node) {
    if (node->parent == nullptr)
        node->color = BLACK;
    else
        insertCase2(node);
}

void RBTree::insertCase2(RBTree::Node *node) {
    if (node->parent->color == BLACK)
        return; /* Tree is still valid */
    else
        insertCase3(node);
}

void RBTree::insertCase3(RBTree::Node *node) {
    Node *uncle = getUncle(node);
    Node *grandparent;

    if ((uncle != nullptr) && (uncle->color == RED)) {
        // && (n->parent->color == RED) Второе условие проверяется в insert_case2, то есть родитель уже является красным.
        node->parent->color = BLACK;
        uncle->color = BLACK;
        grandparent = getGrandparent(node);
        grandparent->color = RED;
        insertCase1(grandparent);
    } else {
        insertCase4(node);
    }
}

void RBTree::insertCase4(RBTree::Node *node) {
    Node *grandparent = getGrandparent(node);

    if ((node == node->parent->right) && (node->parent == grandparent->left)) {
        rotateLeft(node->parent);

        /*
         * rotate_left может быть выполнен следующим образом, учитывая что уже есть *grandparent =  grandparent(node)
         *
         * struct node *saved_p=grandparent->left, *saved_left_n=node->left;
         * grandparent->left=node;
         * node->left=saved_p;
         * saved_p->right=saved_left_n;
         *
         */

        node = node->left;
    } else if ((node == node->parent->left) && (node->parent == grandparent->right)) {
        rotateRight(node->parent);

        /*
         * rotate_right может быть выполнен следующим образом, учитывая что уже есть *grandparent =  grandparent(node)
         *
         * struct node *saved_p=grandparent->right, *saved_right_n=node->right;
         * grandparent->right=node;
         * node->right=saved_p;
         * saved_p->left=saved_right_n;
         *
         */

        node = node->right;
    }
    insertCase5(node);
}

void RBTree::insertCase5(RBTree::Node *node) {
    Node *grandparent = getGrandparent(node);

    node->parent->color = BLACK;
    grandparent->color = RED;
    if ((node == node->parent->left) && (node->parent == grandparent->left)) {
        rotateRight(grandparent);
    } else { /* (node == node->parent->right) && (node->parent == grandparent->right) */
        rotateLeft(grandparent);
    }
}
