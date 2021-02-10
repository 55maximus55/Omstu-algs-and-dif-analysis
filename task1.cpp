#include <iostream>
#include <chrono>
#include <cmath>
using namespace std;
using namespace chrono;

bool isPrime(const int& n){
    for(int i = 2; i <= sqrt(n); ++i)
        if(n % i == 0) return false;
    return n > 1;
}

//// O(n ^ 1/8)
int main() {
    auto start = steady_clock::now();
    int lhs = 0,
            rhs = 152673836,
            x = pow(lhs, .25) + .5,
            y = pow(rhs, .25);
    while(x <= y){
        if(isPrime(x)){
            //cout << (int)pow(x,4) << " " << (int)pow(x, 3) << endl;
            cout << (int)pow(x,4) << endl;
        }
        ++x;
    }
    cout << "time is " << duration_cast<milliseconds>(steady_clock::now() - start).count() << endl;
    return 0;
}