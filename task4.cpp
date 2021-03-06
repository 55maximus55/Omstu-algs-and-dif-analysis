#include <iostream>
#include <cstdlib>
#include "AvlTree.cpp"

using namespace std;

/*
 * АВЛ-деревья
 * Необходимо реализовать создание дерева,
 * добавление нового элемента,
 * удаление элемента,
 * вывод дерева послойно (начиная с листьев).
 * */

int main() {
    auto tree = AvlTree<int, int>();
    tree.push(1, 1);
    tree.push(2, 2);
    tree.push(3, 3);
    tree.push(4, 4);
    tree.push(5, 5);
    tree.push(6, 6);
    tree.remove(2);
    cout << tree.get(3);
    return EXIT_SUCCESS;
}