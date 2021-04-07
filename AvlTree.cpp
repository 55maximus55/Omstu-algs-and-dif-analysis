#include <string>
#include <iostream>

using namespace std;

template<typename key_type, typename value_type>
class AvlTree {
private:
    /* Узел */
    struct Node {
        key_type key;
        value_type value;
        int height;
        Node *left;
        Node *right;

        Node(key_type key, value_type value) : key(key), value(value) {
            left = nullptr;
            right = nullptr;
            height = 1;
        }
    };
    Node *head = nullptr;

    unsigned char nodeHeight(Node *p) {
        return p ? p->height : 0;
    }
    int balanceFactor(Node *p) {
        return nodeHeight(p->right) - nodeHeight(p->left);
    }
    void fixHeight(Node *p) {
        unsigned char hl = nodeHeight(p->left);
        unsigned char hr = nodeHeight(p->right);
        p->height = (hl > hr ? hl : hr) + 1;
    }
    Node *rotateRight(Node *p) { // правый поворот вокруг p
        Node *q = p->left;
        p->left = q->right;
        q->right = p;
        fixHeight(p);
        fixHeight(q);
        return q;
    }
    Node *rotateLeft(Node *q) {// левый поворот вокруг q
        Node *p = q->right;
        q->right = p->left;
        p->left = q;
        fixHeight(q);
        fixHeight(p);
        return p;
    }
    Node *balanceNode(Node *p) { // балансировка узла p
        fixHeight(p);
        if (balanceFactor(p) == 2) {
            if (balanceFactor(p->right) < 0)
                p->right = rotateRight(p->right);
            return rotateLeft(p);
        }
        if (balanceFactor(p) == -2) {
            if (balanceFactor(p->left) > 0)
                p->left = rotateLeft(p->left);
            return rotateRight(p);
        }
        return p; // балансировка не нужна
    }
    Node *insertNode(Node *p, key_type key, value_type value) { // вставка ключа key в дерево с корнем p
        if (!p) return new Node(key, value);
        if (key < p->key)
            p->left = insertNode(p->left, key, value);
        else
            p->right = insertNode(p->right, key, value);
        return balanceNode(p);
    }
    Node *findMinNode(Node *p) { // поиск узла с минимальным ключом в дереве p
        return p->left ? findMinNode(p->left) : p;
    }
    Node *removeMinNode(Node *p) { // удаление узла с минимальным ключом из дерева p
        if (p->left == 0)
            return p->right;
        p->left = removeMinNode(p->left);
        return balanceNode(p);
    }
    Node *removeNode(Node *p, key_type k) { // удаление ключа k из дерева p
        if (!p) return 0;
        if (k < p->key)
            p->left = removeNode(p->left, k);
        else if (k > p->key)
            p->right = removeNode(p->right, k);
        else //  k == p->key
        {
            Node *q = p->left;
            Node *r = p->right;
            delete p;
            if (!r) return q;
            Node *min = findMinNode(r);
            min->right = removeMinNode(r);
            min->left = q;
            return balanceNode(min);
        }
        return balanceNode(p);
    }

public:
    AvlTree() = default;

    void push(key_type key, value_type value) {
        if (!head) head = new Node(key, value);
        else head = insertNode(head, key, value);
    }
    void remove(key_type key) {
        head = removeNode(head, key);
    }
    value_type get(key_type key) {
        Node *node = getNode(head, key);
        if (node)
            return node->value;
    }
    value_type operator[](key_type key) {
        return get(key);
    }
    bool contains(key_type key) {
        return getNode(head, key) != nullptr;
    }


    void kekf(Node *node, string k) {
        if (node) {
            cout << node->key << " " << k << endl;
            kekf(node->left, k + "l");
            kekf(node->right, k + "r");
        }
    }
    void kek() {
        kekf(head, "");
        cout << endl;
    }
};