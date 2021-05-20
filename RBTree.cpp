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
RBTree::Node *RBTree::getBrother(RBTree::Node *node) {
    if (node->parent == nullptr) return nullptr;
    if (node->parent->left == node) return node->parent->right;
    else return node->parent->left;
}

void RBTree::insert(int key) {
    Node *node = new Node(key, RED, nullptr, nullptr);
    if (head == nullptr) {
        head = node;
    } else {
        Node *p = head;
        Node *q = nullptr;
        while (p != nullptr) {// спускаемся вниз, пока не дойдем до подходящего листа
            q = p;
            if (p->key < node->key)
                p = p->right;
            else
                p = p->left;
        }
        node->parent = q;
        // добавляем новый элемент красного цвета
        if (q->key < node->key)
            q->right = node;
        else
            q->left = node;
    }
    insertFix(node); // проверяем, не нарушены ли свойства красно-черного дерева
}
void RBTree::insertFix(RBTree::Node *t) {
    if (t == head) {
        t->color = BLACK;
        return;
    }
    // далее все предки упоминаются относительно t
    while (t->parent != nullptr && t->parent->color == RED) { // нарушается свойство 3
        if (getGrandparent(t)->left == t->parent) {
            if (getUncle(t) != nullptr && getUncle(t)->color == RED) {
                t->parent->color = BLACK;
                getUncle(t)->color = BLACK;
                getGrandparent(t)->color = RED;
                t = getGrandparent(t);
            }
            else {
                if (t->parent->right == t) {
                    t = t->parent;
                    rotateLeft(t);
                }
                t->parent->color = BLACK;
                getGrandparent(t)->color = RED;
                rotateRight(getGrandparent(t));
            }
        }
        else { // "отец" — правый ребенок
            if (getUncle(t) != nullptr && getUncle(t)->color == RED) {
                t->parent->color = BLACK;
                getUncle(t)->color = BLACK;
                getGrandparent(t)->color = RED;
                t = getGrandparent(t);
            }
            else {// нет "дяди"
                if (t->parent->left == t) {
                        t = t->parent;
                        rotateRight(t);
                }
                t->parent->color = BLACK;
                getGrandparent(t)->color = RED;
                rotateLeft(getGrandparent(t));
            }
        }
    }
    head->color = BLACK; // восстанавливаем свойство корня
}

void RBTree::remove(int key) {
//    Node y = nil
//    Node q = nil

    Node *p = head;
    // находим узел с ключом key
    while (p != nullptr && p->key != key) {
        if (p->key < key)
            p = p->right;
        else
            p = p->left;
    }
    if (p == nullptr) return;
    Node *y = p->right;

    /* Нет потомков */
    if (p->left == nullptr && p->right == nullptr) {
        if (p == head)
            head = nullptr;
        else {
            if (p->parent->left == p)
                p->parent->left = nullptr;
            else
                p->parent->right = nullptr;
            delete p;
        }
        return;
    }
    /* Один потомок */
    else if (p->left == nullptr && p->right != nullptr || p->left != nullptr && p->right == nullptr) { //один ребенок
//        ссылку на у от "отца" меняем на ребенка y
        if (p->left != nullptr) {
            p->left->parent = p->parent;
            if (p->parent->right == p)
                p->parent->right = p->left;
            else
                p->parent->left = p->left;
        } else {
            p->right->parent = p->parent;
            if (p->parent->right == p)
                p->parent->right = p->right;
            else
                p->parent->left = p->right;
        }
    }
    /* два потомка */
    else {
        // вершина, со следующим значением ключа // у нее нет левого ребенка
        while (y->left != nullptr)
            y = y->left;


        Node *x = y->right;
        Node *z = y->parent;
        if (p == z) z->right = x;
        else z->left = x;
        if (x != nullptr) x->parent = z;

        y->right = p->right;
        if (y->right != nullptr) y->right->parent = y;


        y->left = p->left;
        y->left->parent = y;


        if (p == head) {
            head = y;
            y->parent = nullptr;
        } else {
            y->parent = p->parent;
            if (p->parent->left == p) p->parent->left = y;
            else p->parent->right = y;
        }
    }

    if (y != nullptr && y != p)
        y->color = p->color;
    delete p;
    // при удалении черной вершины могла быть нарушена балансировка
    if (y != nullptr && y->color == BLACK)
        removeFix(y);
}
void RBTree::removeFix(RBTree::Node *p) {
    // далее родственные связи относительно p
    while (p->color == BLACK && p != head) {
        Node *brother = getBrother(p);
        if (p->parent->left == p) {
            if (brother != nullptr && brother->color == RED) {
                brother->color = BLACK;
                p->parent->color = RED;
                rotateLeft(p->parent);
            }
            if (brother != nullptr && (brother->left->color == BLACK && brother->right->color == BLACK))             // случай 1: "брат" красный с черными детьми
                brother->color = RED;
            else {
                if (brother->right->color == BLACK) { // случай, рассматриваемый во втором подпункте:
                    brother->left->color = BLACK;         // "брат" красный с черными правым ребенком
                    brother->color = RED;
                    rotateRight(brother);
                }
                brother->color = p->parent->color;   // случай, рассматриваемый в последнем подпункте
                p->parent->color = BLACK;
                brother->right->color = BLACK;
                rotateLeft(p->parent);
                p = head;
            }
        }
        else {// p — правый ребенок
            // все случаи аналогичны тому, что рассмотрено выше
            if (brother->color == RED) {
                brother->color = BLACK;
                p->parent->color = RED;
                rotateRight(p->parent);
            }
            if (brother != nullptr && (brother->left->color == BLACK && brother->right->color == BLACK))
                brother->color = RED;
            else {
                if (brother->left->color == BLACK) {
                   brother->right->color = BLACK;
                   brother->color = RED;
                   rotateLeft(brother);
                }
                brother = p->parent;
                p->parent->color = BLACK;
                brother->left->color = BLACK;
                rotateRight(p->parent);
                p = head;
            }
        }
        p->color = BLACK;
        head->color = BLACK;
    }
}
