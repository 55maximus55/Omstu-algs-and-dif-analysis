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
        if (Distance(begin, end) < 2) return;
        else {
            int counterGrabbed = 1;
            auto mainElem = prev(end);
            auto iter = end;
            for (advance(iter, -2); iter != prev(begin); --iter) {
                if (*iter < *mainElem) ++counterGrabbed;
                else {
                    rotate(iter, counterGrabbed);
                    --mainElem;
                }
            }
            quickSort(next(mainElem), end);
            quickSort(begin, mainElem);
        }

    }

    // 1
    template<typename Iterator>
    static void mergeSort(Iterator begin, Iterator end) {
        size_t size = Distance(begin, end);
        if(size < 2) return; else {
            vector<typename iterator_traits<Iterator>::value_type>
                    vec1(begin, next(begin, size / 2)),
                    vec2(next(begin, size / 2), end),
                    mergedVec;
            mergeSort(vec1.begin(), vec1.end());
            mergeSort(vec2.begin(), vec2.end());

            Merge(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), back_inserter(mergedVec));
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
    static void iter_swap(Iterator lhs, Iterator rhs) {
        swap(*lhs, *rhs);
    }

    template<typename type>
    static void swap(type &lhs, type &rhs) {
        type temp = move(lhs);
        lhs = move(rhs);
        rhs = move(temp);
    }

    template<typename Iterator>
    static void rotate(Iterator begin, int grubbed) {
        for (int i = 0; i < grubbed; ++i) {
            iter_swap(begin, next(begin));
            ++begin;
        }
    }

    template <typename Iterator>
    static auto max(Iterator begin, Iterator end){
        typename iterator_traits<Iterator>::value_type Max = *begin;
        for(; begin != end; ++begin) {
            if(Max < *begin) Max = *begin;
        }
        return Max;
    }

    template<typename inIterator, typename destIterator>
    static auto Copy(inIterator lhs, inIterator rhs, destIterator destination) {
        for(; lhs != rhs; ++destination, ++lhs) {
            *destination = *lhs;
        }
        return destination;
    }

    template<typename fInIterator, typename sInIterator, typename destIterator>
    static void Merge(fInIterator flhs, fInIterator frhs,
                      sInIterator rlhs, sInIterator rrhs,
                      destIterator destination){
        for(;; ++destination) {
            if(flhs == frhs) {
                Copy(rlhs, rrhs, destination);
                return;
            }
            if(rlhs == rrhs) {
                Copy(flhs, frhs, destination);
                return;
            }
            if(*flhs < *rlhs){
                *destination = *flhs;
                ++flhs;
            } else {
                *destination = *rlhs;
                ++rlhs;
            }
        }
    }

    template<typename Iterator>
    static size_t Distance(Iterator begin, Iterator end) {
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

    return EXIT_SUCCESS;
}
