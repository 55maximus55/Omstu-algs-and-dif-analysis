#ifndef TEST_TESTER_H
#define TEST_TESTER_H

#include <chrono>
#include <iostream>
#include <vector>

using namespace std;
using namespace chrono;

template<typename type>
void Swap(type &lhs, type &rhs) {
    type temp = std::move(lhs);
    lhs = std::move(rhs);
    rhs = std::move(temp);
}


#define AssertWithTime(function, lhs, rhs) \
{\
Tester test; \
cout << #function << ": " << (function(lhs)== rhs? "true" : "false")\
}

#define Assert(function, lhs, rhs) \
cout << #function << ": " << (function(lhs)== rhs? "true" : "false") << endl

template<typename type>
std::ostream &operator<<(std::ostream &stream, const std::vector<type> &vec) {
    for (const type &one : vec) {
        stream << one << " ";
    }
    return stream;
}

class Tester {
    const steady_clock::time_point start;
public:
    Tester() : start(steady_clock::now()) {}

    ~Tester() {
        cerr << duration_cast<chrono::milliseconds>(steady_clock::now() - start).count() << " ms";
    }
};


#endif //TEST_TESTER_H
