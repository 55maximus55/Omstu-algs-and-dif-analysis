/* MD5 */

#include <iostream>
#include "md5.h"

int main() {
    std::string kek = "Test";
    std::cout << kek << ": " << md5("Test") << std::endl;
    std::cout << "Test: 0cbc6611f5540bd0809a388dc95a615b";
}

