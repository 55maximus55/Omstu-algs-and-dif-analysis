#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <deque>
#include <numeric>
#include <functional>
#include <cmath>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

class Sort {
public:
    // 1
    template<typename Iterator>
    static void quickSort(Iterator begin, Iterator end) {
        if (Distance(begin, end) < 2)
            return; // 1
        else {
            // (n-1)(2n-1) + 3
            int counterGrabbed = 1; // 1
            auto mainElem = prev(end); // 1
            auto iter = end; // 1

            // (n-1)(2n-1)
            for (advance(iter, -2); iter != prev(begin); --iter) { // (n-1)
                // 2n - 1
                if (*iter < *mainElem)
                    ++counterGrabbed; // 1
                else {
                    rotate(iter, counterGrabbed); // 2n - 2
                    --mainElem; // 1
                }
            }


            quickSort(next(mainElem), end);
            quickSort(begin, mainElem);
        }

    }

    // 1
    template<typename Iterator>
    static void mergeSort(Iterator begin, Iterator end) {
        size_t size = Distance(begin, end); // n
        if(size < 2) return; else {
            vector<typename iterator_traits<Iterator>::value_type>
                    vec1(begin, next(begin, size / 2)), // n/2
                    vec2(next(begin, size / 2), end), // n/2
                    mergedVec; // 1

            mergeSort(vec1.begin(), vec1.end());
            mergeSort(vec2.begin(), vec2.end());

            Merge(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), back_inserter(mergedVec)); //
            Copy(mergedVec.begin(), mergedVec.end(), begin);
        }
    }

    // 2
    template<typename Iterator>
    static void gnomeSort(Iterator begin, Iterator end) {
        auto current = begin;
        while (current != end) {
            if (current == begin || *current > *prev(current)) {
                ++current;
            } else if (*current < *prev(current)) {
                iter_swap(current, prev(current));
                --current;
            }
        }
    }

    // 2
    template<typename Iterator>
    static void selectionSort(Iterator begin, Iterator end){
        if(distance(begin, end) < 2) return;
        else{
            auto min = begin;
            for(auto iter = begin; iter != end; ++iter){
                if(*min > *iter) min = iter;
            }
            if(min != begin) iter_swap(begin, min);
            selectionSort(next(begin), end);
        }
    }

    // 2
    template<typename Iterator>
    static void treeSort(Iterator begin, Iterator end) {
        Tree<typename iterator_traits<Iterator>::value_type> tree(begin, end);
        Copy(tree.begin(), tree.end(), begin);
    }

    // 3
    template<typename Iterator>
    static void bucketSort(Iterator begin, Iterator end, int amount = 10) {
        typedef typename iterator_traits<Iterator>::value_type value_type;
        vector<vector<value_type>> vec(amount+1);
        amount = distance(begin, end) / amount;
        for(auto iter = begin; iter != end; ++iter) {
            vec[round(*iter/amount)].push_back(*iter);
        }
        for(auto i = 0; i<vec.size(); ++i) {

            Sort::quickSort(vec[i].begin(), vec[i].end());
        }
        for(auto i = 0; i<vec.size(); ++i) {
            for(auto j = 0; j<vec[i].size(); ++j) {
                *begin = vec[i][j];
                ++begin;
            }
        }
    }

    // 3
    template<typename Iterator>
    static void countingSort(Iterator begin, Iterator end) {
        vector<int>vec(max(begin, end)+1);
        for(auto iter = begin; iter != end; ++iter) {
            vec[*iter] = 1;
        }
        for(int i=0; i<vec.size(); ++i) {
            if(vec[i] != 0) {
                *begin = i;
                ++begin;
            }
        }
    }

    // 3 только для интов
    template<typename Iterator>
    static void radixSort(Iterator begin, Iterator end) {
        auto Max = to_string(max(begin, end)).length();

        vector<vector<typename iterator_traits<Iterator>::value_type>> buckets(10);
        for(auto i = 0; i < Max; ++i) {
            for(auto iter = begin; iter != end; ++iter) {
                buckets[ (*iter % static_cast<int>(pow(10, i + 1))) / static_cast<int>(pow(10, i ))].push_back(*iter);
            }
            auto Begin = begin;
            for(auto j = 0; j <buckets.size(); ++j){
                Begin = Copy(buckets[j].begin(), buckets[j].end(), Begin);
                buckets[j].clear();
            }
        }



    }

private:

    template<typename Iterator>
    static void print(Iterator begin, Iterator end) {
        for(;begin != end; ++begin) {
            cout << *begin << " ";
        }
        cout << endl;
    }

    template<typename Iterator>
    static void iter_swap(Iterator lhs, Iterator rhs) { // 3
        swap(*lhs, *rhs); // 3
    }

    template<typename type>
    static void swap(type &lhs, type &rhs) { // 3
        type temp = move(lhs); // 1
        lhs = move(rhs); // 1
        rhs = move(temp); // 1
    }

    template<typename Iterator>
    static void rotate(Iterator begin, int grubbed) { // 2(n-1)
        for (int i = 0; i < grubbed; ++i) { // 2n-2
            iter_swap(begin, next(begin)); // 1
            ++begin; // 1
        }
    }

    template <typename Iterator>
    static auto max(Iterator begin, Iterator end){ // n + 1
        typename iterator_traits<Iterator>::value_type Max = *begin; // 1
        for(; begin != end; ++begin) { // n
            if(Max < *begin)
                Max = *begin; // 1
        }
        return Max;
    }

    template<typename inIterator, typename destIterator>
    static auto Copy(inIterator lhs, inIterator rhs, destIterator destination) { // n
        for(; lhs != rhs; ++destination, ++lhs) { // n
            *destination = *lhs; // 1
        }
        return destination;
    }

    template<typename fInIterator, typename sInIterator, typename destIterator>
    static void Merge(fInIterator flhs, fInIterator frhs,
                      sInIterator rlhs, sInIterator rrhs,
                      destIterator destination){ // n
        for(;; ++destination) { // n
            if(flhs == frhs) {
                Copy(rlhs, rrhs, destination); // n
                return;
            } else
            if(rlhs == rrhs) { // n
                Copy(flhs, frhs, destination); // n
                return;
            } else
            if(*flhs < *rlhs){ // 2
                *destination = *flhs; // 1
                ++flhs; // 1
            } else {
                *destination = *rlhs; // 1
                ++rlhs; // 1
            }
        }
    }

    template<typename Iterator>
    static size_t Distance(Iterator begin, Iterator end) { // n
        for(size_t i = 0;;++i, ++begin) {
            if(begin == end) return i;
        }
    }

    template<typename value_type>
    class Tree
    {
    private:
        struct Node {
            const value_type value;
            Node *left = nullptr, *right = nullptr;
            explicit Node(value_type value): value(value){
            }
        };
        Node* head;
        vector<value_type> sorted;
        template<typename Iterator>
        void makeTree(Iterator begin, Iterator end){
            ++begin;
            for(; begin != end; ++begin) {
                push(*begin);
            }
        }
        void push(value_type value){
            auto current = head;
            Node* next = head;
            while(next != nullptr){
                current = next;
                next = value < current->value ? current->left : current->right;
            }

            if(value < current->value)
                current->left = new Node(value);
            else
                current->right = new Node(value);
        }
        void readTree(Node* Head) {
            if(Head->left != nullptr) readTree(Head->left);
            sorted.push_back(Head->value);
            if(Head->right != nullptr) readTree(Head->right);
        }
       void deleteNode(Node* node) {
            if(node->left != nullptr) deleteNode(node->left);
            if(node->right != nullptr) deleteNode(node->right);
            delete node;
        }
    public:
        template<typename Iterator>
        Tree(Iterator begin, Iterator end){
            if(begin != end){
                head =new Node(*begin);
                makeTree(begin, end);
                readTree(head);
            }
        }
        ~Tree() {
            deleteNode(head);
        }
        auto begin() const{ return sorted.begin();}
        auto end() const{ return sorted.end();}
        auto begin(){ return sorted.begin();}
        auto end(){ return sorted.end();}
    };

};

template<typename type>
ostream &operator<<(ostream &stream, const vector<type> &vec) {
    for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
        if (iter != vec.begin()) stream << " ";
        stream << *iter;
    }
    return stream;
}

template<typename type>
ostream &operator<<(ostream &stream, const list<type> &vec) {
    for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
        if (iter != vec.begin()) stream << " ";
        stream << *iter;
    }
    return stream;
}

template<typename type>
ostream &operator<<(ostream &stream, const deque<type> &vec) {
    for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
        if (iter != vec.begin()) stream << " ";
        stream << *iter;
    }
    return stream;
}



// тест рандомного набора символов длины 100 на различных контейнерах с bidir итераторами: vector, list, deque, array

#define create(container, function) \
{                                \
vector<int> temp(100);                     \
iota(temp.begin(), temp.end(), 1);         \
container<int> result(100), shuffled(100); \
result = {temp.begin(), temp.end()}; \
random_shuffle(temp.begin(), temp.end());  \
shuffled = {temp.begin(), temp.end()};     \
function(shuffled.begin(), shuffled.end());\
test &= shuffled == result;\
}

#define Test(function){ \
        bool test = true; \
        create(vector, function) \
        create(deque, function)  \
        create(list, function)   \
        cerr << #function << ": " << (test ? "success" : "fail") << endl;\
}


int main() {

    Test(Sort::quickSort)
    Test(Sort::gnomeSort)
    Test(Sort::selectionSort)
    Test(Sort::bucketSort)
    Test(Sort::countingSort)
    Test(Sort::mergeSort)
    Test(Sort::radixSort)
    Test(Sort::treeSort)

    return 0;
}

