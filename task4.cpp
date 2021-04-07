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
    tree.push(2, 4);
    tree.kek();

    tree.push(4, 6);
    tree.kek();

    tree.push(6, 3);
    tree.kek();

    tree.push(7, 5);
    tree.kek();

    tree.push(5, 1);
    tree.kek();

    tree.push(12, 0);
//    tree.kek();

//    tree.remove(4);
//    tree.remove(2);

    tree.kek();

    return EXIT_SUCCESS;
}