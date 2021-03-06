template<typename key_type, typename value_type>
class AvlTree {
private:
    /* Узел */
    struct Node {
        key_type key;
        value_type value;
        int height;
        Node* left;
        Node* right;
        Node(key_type key, value_type value) : key(key), value(value) {
            left = nullptr;
            right = nullptr;
            height = 1;
        }
    };
    Node* head = nullptr;
    /* Получение узла по ключу */
    Node* getNode(Node* node, key_type key) {
        if (node) {
            if (node->key == key)
                return node;
            if (key < node->key)
                return getNode(node->left, key);
            if (key > node->key)
                return getNode(node->right, key);
        }
        else return nullptr;
    }

    /* Возврат высоты узла */
    int nodeHeight(Node* node) {
        return node ? node->height : 0;
    }
    /* Восстановление корректного значения высоты заданного узла */
    void fixNodeHeight(Node* node) {
        if (node) {
            int leftHeight = nodeHeight(node->left);
            int rightHeight = nodeHeight(node->right);
            node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
        }
    }
    /* Разница высот поддеревьев узла */
    int balanceFactor(Node* node) {
        if (node)
            return nodeHeight(node->left) - nodeHeight(node->right);
        else return 0;
    }

    /* Правый поворот */
    Node* rotateRight(Node* p) {
        Node* q = p->left;
        p->left = q->right;
        q->right = p;
        fixNodeHeight(p);
        fixNodeHeight(q);
        return q;
    }
    /* Левый поворот */
    Node* rotateLeft(Node* q) {
        Node* p = q->right;
        q->right = p->left;
        p->left = q;
        fixNodeHeight(q);
        fixNodeHeight(p);
        return p;
    }

    /* Балансировка узлов */
    Node* balanceNode(Node* p) {
        fixNodeHeight(p);
        if (balanceFactor(p) >= 2) {
            if (balanceFactor(p->right) < 0)
                p->right = rotateRight(p->right);
            return rotateLeft(p);
        }
        if (balanceFactor(p) <= -2) {
            if (balanceFactor(p->left) > 0)
                p->left = rotateRight(p->left);
            return rotateLeft(p);
        }
        return p;
    }
    /* Вставка узла в дерево с корнем p */
    Node* insert(Node* p, key_type key, value_type value) {
        if (!p) return new Node(key, value);
        if (key < p->key) p->left = insert(p->left, key, value);
        else p->right = insert(p->right, key, value);
        return balanceNode(p);
    }

    /* Поиск родительского узла */
    Node* getParentNode(Node* node, key_type key) {
        if (!node)
            return nullptr;
        if (node->key == key)
            return nullptr;
        if (key < node->key) {
            if (node->left) {
                if (node->left->key != key)
                    return getParentNode(node->left, key);
                else return node;
            }
            return nullptr;
        }
        if (key < node->key) {
            if (node->right) {
                if (node->right->key != key)
                    return getParentNode(node->right, key);
                else return node;
            }
            return nullptr;
        }
    }

    /* Находим левый лист поддерева */
    Node* getMinNode(Node* node) {
        return node->left ? getMinNode(node->left) : node;
    }
    /* Удаление левого листа */
    Node* removeMinNode(Node* node) {
        if(!node->left)
            return node->right;
        node->left = removeMinNode(node->left);
        return balanceNode(node);
    }
    Node* removeNode(Node* p, key_type key) {
        if (!p) return nullptr;
        if (key < p->key)
            p->left = removeNode(p->left, key);
        else if(key > p->key)
            p->right = removeNode(p->right, key);
        else {
            Node* q = p->left;
            Node* r = p->right;
            delete p;
            if (!r) return q;
            Node* min = getMinNode(r);
            min->right = removeMinNode(r);
            min->left = q;
            return balanceNode(min);
        }
        return balanceNode(p);
    }
public:
    AvlTree() = default;
    void push(key_type key, value_type value) {
        if (!head) head =  new Node(key, value);
        else {
            Node* node = getNode(head, key);
            if (node)
                node->value = value;
            else
                head = insert(head, key, value);
        }
    }
    void remove(key_type key) {
        if (contains(key)) {
            removeNode(head, key);
        }
    }
    value_type get(key_type key) {
        Node* node = getNode(head, key);
        if (node)
            return node->value;
    }
    bool contains(key_type key) {
        return getNode(head, key) != nullptr;
    }
};