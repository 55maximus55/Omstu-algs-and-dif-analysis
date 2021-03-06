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
    tree.push(1, 0);
    tree.push(2, 0);
    tree.push(3, 0);
    tree.push(4, 0);
    tree.push(5, 0);
    tree.push(6, 0);
    tree.remove(2);
    return EXIT_SUCCESS;
}