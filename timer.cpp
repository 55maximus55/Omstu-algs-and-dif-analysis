#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;

#define timer() auto TIMER = Timer()

class Timer{
public:
    std::chrono::time_point<std::chrono::steady_clock> start;
    Timer(): start(steady_clock::now()){
    }
    ~Timer(){
        cout << "time is: " << duration_cast<milliseconds>(steady_clock::now() - start).count() << " ms" << endl;
    }
};
