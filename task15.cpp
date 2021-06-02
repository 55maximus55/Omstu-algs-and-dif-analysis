/* SHA-1 */

#include <iostream>
#include <string>
#include "sha1.h"

int main() {
    std::string kek = "Test";
    std::cout << "Test: " << sha1(kek) << std::endl;
    std::cout << "Test: 640ab2bae07bedc4c163f679a746f7ab7fb5d1fa";
}
