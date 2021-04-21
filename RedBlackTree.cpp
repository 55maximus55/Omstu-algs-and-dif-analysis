template<typename key_type, typename value_type>
class RBTree {
    typedef enum {
        BLACK, RED
    } NodeColor;

    struct Node {
        struct Node *left;
        struct Node *right;
        struct Node *parent;
        NodeColor color;

        key_type key;
        value_type value;

        Node(key_type key, value_type value, NodeColor color, Node *left, Node *right) : key(key),
                                                                                         value(value), color(color),
                                                                                         left(left), right(right) {
            parent = nullptr;
        }
    };

    Node *head = nullptr;

    // TODO: поворот
    void *rightRotate(Node *p) {
    }
    void *leftRotate(Node *q) {
    }

    void fixInsertion(Node *t) {
        if (t == head) {
            t->color = BLACK;
            return;
        }
        while (t->parent->color == RED) {
            Node *parent = t->parent;
            Node *grandfather = parent->parent;
            if (parent == grandfather->left) { // "отец" — левый ребенок
                Node *uncle = grandfather->right;
                if (uncle) {
                    if (uncle->color == RED) {
                        parent->color = BLACK;
                        uncle->color = BLACK;
                        grandfather->color = RED;
                        t = grandfather;
                    }
                } else {
                    // случай, когда нет "дяди"
                    if (t == parent->right) {
                        t = parent;
                        leftRotate(t);
                    }
                    parent->color = BLACK;
                    grandfather->color = RED;
                    rightRotate(grandfather);
                }
            } else { // "отец" — правый ребенок
                Node *uncle = grandfather->left;
                if (uncle) {
                    if (uncle->color == RED) {
                        parent->color = BLACK;
                        uncle->color = BLACK;
                        grandfather->color = RED;
                        t = grandfather;
                    }
                } else { // нет "дяди"
                    if (t == parent->left) {
                        t = parent;
                        rightRotate(t);
                    }
                    parent->color = BLACK;
                    grandfather->color = RED;
                    leftRotate(grandfather);
                }
            }
        }
        head->color = BLACK; // восстанавливаем свойство корня
    }

public:
    void insert(key_type key, value_type value) {
        Node *t = new Node(key, value, RED, nullptr, nullptr);
        if (!head) {
            t->parent = nullptr;
            head = t;
        } else {
            Node *p = head;
            Node *q = nullptr;
            // спускаемся вниз, пока не дойдем до подходящего листа
            while (p) {
                q = p;
                if (p->key < t->key)
                    p = p->right;
                else
                    p = p->left;
            }
            t->parent = q;
            // добавляем новый элемент красного цвета
            if (q->key < t->key)
                q->right = t;
            else
                q->left = t;
        }
        // проверяем, не нарушены ли свойства красно-черного дерева
        fixInsertion(t);
    }

};