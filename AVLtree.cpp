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
public:
    AVLtree() = default;
    void push(key_type key, value_type value);
    void remove(key_type key);
    value_type get(key_type key);
    bool contains(key_type key);
};