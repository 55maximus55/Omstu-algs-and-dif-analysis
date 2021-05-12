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

/* Текущий узел N в корне дерева. В этом случае, он перекрашивается в чёрный цвет чтобы оставить верным Свойство 2 (Корень — чёрный).
     * Так как это действие добавляет один чёрный узел в каждый путь,
     * Свойство 5 (Все пути от любого данного узла до листовых узлов содержат одинаковое число чёрных узлов) не нарушается.  */
void RBTree::insertCase1(RBTree::Node *node) {
    if (node->parent == nullptr)
        node->color = BLACK;
    else
        insertCase2(node);
}
/* Предок P текущего узла чёрный, то есть Свойство 4 (Оба потомка каждого красного узла — чёрные) не нарушается.
 * В этом случае дерево остаётся корректным.
 * Свойство 5 (Все пути от любого данного узла до листовых узлов содержат одинаковое число чёрных узлов) не нарушается,
 * потому что текущий узел N имеет двух чёрных листовых потомков, но так как N является красным,
 * путь до каждого из этих потомков содержит такое же число чёрных узлов, что и путь до чёрного листа,
 * который был заменен текущим узлом, так что свойство остается верным.  */
void RBTree::insertCase2(RBTree::Node *node) {
    if (node->parent->color == BLACK)
        return; /* Tree is still valid */
    else
        insertCase3(node);
}
/* Если и родитель P, и дядя U — красные, то они оба могут быть перекрашены в чёрный, и дедушка G станет красным
 * (для сохранения свойства 5 (Все пути от любого данного узла до листовых узлов содержат одинаковое число чёрных узлов)).
 * Теперь у текущего красного узла N чёрный родитель. Так как любой путь через родителя или дядю должен проходить через дедушку,
 * число чёрных узлов в этих путях не изменится. Однако, дедушка G теперь может нарушить свойства 2 (Корень — чёрный)
 * или 4 (Оба потомка каждого красного узла — чёрные) (свойство 4 может быть нарушено, так как родитель G может быть красным).
 * Чтобы это исправить, вся процедура рекурсивно выполняется на G из случая 1. */
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
/* Родитель P является красным, но дядя U — чёрный. Также, текущий узел N — правый потомок P, а P в свою очередь — левый потомок своего предка G.
 * В этом случае может быть произведен поворот дерева, который меняет роли текущего узла N и его предка P.
 * Тогда, для бывшего родительского узла P в обновленной структуре используем случай 5,
 * потому что Свойство 4 (Оба потомка любого красного узла — чёрные) все ещё нарушено.
 * Вращение приводит к тому, что некоторые пути (в поддереве, обозначенном «1» на схеме) проходят через узел N,
 * чего не было до этого. Это также приводит к тому, что некоторые пути (в поддереве, обозначенном «3») не проходят через узел P.
 * Однако, оба эти узла являются красными, так что Свойство 5 (Все пути от любого данного узла до листовых узлов содержат одинаковое число чёрных узлов)
 * не нарушается при вращении. Однако Свойство 4 всё ещё нарушается, но теперь задача сводится к Случаю 5.  */
void RBTree::insertCase4(RBTree::Node *node) {
    Node *grandparent = getGrandparent(node);

    if ((node == node->parent->right) && (node->parent == grandparent->left)) {
        rotateLeft(node->parent);
        node = node->left;
    } else if ((node == node->parent->left) && (node->parent == grandparent->right)) {
        rotateRight(node->parent);
        node = node->right;
    }
    insertCase5(node);
}
/* Родитель P является красным, но дядя U — чёрный, текущий узел N — левый потомок P и P — левый потомок G.
 * В этом случае выполняется поворот дерева на G. В результате получается дерево,
 * в котором бывший родитель P теперь является родителем и текущего узла N и бывшего дедушки G.
 * Известно, что G — чёрный, так как его бывший потомок P не мог бы в противном случае быть красным (без нарушения Свойства 4).
 * Тогда цвета P и G меняются и в результате дерево удовлетворяет Свойству 4 (Оба потомка любого красного узла — чёрные).
 * Свойство 5 (Все пути от любого данного узла до листовых узлов содержат одинаковое число чёрных узлов) также остается верным,
 * так как все пути, которые проходят через любой из этих трех узлов, ранее проходили через G, поэтому теперь они все проходят через P.
 * В каждом случае, из этих трёх узлов только один окрашен в чёрный. */
void RBTree::insertCase5(RBTree::Node *node) {
    Node *grandparent = getGrandparent(node);

    node->parent->color = BLACK;
    grandparent->color = RED;
    if ((node == node->parent->left) && (node->parent == grandparent->left)) {
        rotateRight(grandparent);
    } else {
        rotateLeft(grandparent);
    }
}
