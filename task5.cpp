#include <iostream>
#include <cstdlib>
#include "RedBlackTree.cpp"
using namespace std;

/*
 * КРАСНО-ЧЕРНЫЕ ДЕРЕВЬЯ
 * Необходимо реализовать создание дерева,
 * добавление нового элемента,
 * удаление элемента,
 * вывод дерева послойно (начиная с листьев)
 * */

int main() {
    auto tree = RBTree<int, int>();
    tree.insert(0, 0);
    tree.insert(1, 0);
    tree.insert(2, 0);
    tree.insert(3, 0);
    tree.insert(4, 0);
    tree.insert(5, 0);
    return EXIT_SUCCESS;
}