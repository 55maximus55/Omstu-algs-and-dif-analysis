template<typename key_type, typename value_type>
class AVLtree {
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
public:
    AVLtree() = default;
    void push(key_type key, value_type value);
    void remove(key_type key);
    value_type get(key_type key);
    bool contains(key_type key);
};