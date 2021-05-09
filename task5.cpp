#include <iostream>
#include <cstdlib>
#include "RBTree.h"

using namespace std;

/*
 * КРАСНО-ЧЕРНЫЕ ДЕРЕВЬЯ
 * Необходимо реализовать создание дерева,
 * добавление нового элемента,
 * удаление элемента,
 * вывод дерева послойно (начиная с листьев)
 * */

int main() {
    auto tree = new RBTree();
    tree->insert(8);
    tree->insert(7);
    tree->insert(4);
    tree->insert(6);
    tree->insert(5);
    tree->insert(3);
    tree->insert(2);
    tree->insert(1);

    tree->printTree();

    return EXIT_SUCCESS;
}