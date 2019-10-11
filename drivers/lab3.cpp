#include "Queue.h"
#include "Queue.h"
#include <iostream>
#include <cassert>
#include <cstring>
#include <ctime>
#include <cstdlib>

#define QUEUE_SIZE 5

using namespace std;

//########        FOR TESTING PURPOSES        #########
class Test{
public:
    int num;
    char let;
    Test(): num(0), let('a'){}
    Test(int a, char b): num(a), let(b){}
    friend ostream& operator<<(ostream& os, const Test& dt);
};
ostream& operator<<(ostream& os, const Test& dt){
    os << "{let: " << dt.let << ", num: " << dt.num <<"} ";
    return os;
}
//######################################################

int main(){
    srand(time(NULL));
#ifndef TEST1
{
    cerr << "\n\tTEST #1: Test add 1 element to a Queue" << endl;

    Queue<int> queue(QUEUE_SIZE);
    assert(queue.enqueue(5));
    assert(5 == queue.dequeue());

    cerr << "\n\t========================PASS========================\n" << endl;
}
#endif
#ifndef TEST2
{
    cerr << "\n\tTEST #2: Test fill a char Queue" << endl;

    Queue<char> char_queue(QUEUE_SIZE);
    assert(char_queue.enqueue('a'));
    assert(char_queue.enqueue('b'));
    assert(char_queue.enqueue('c'));
    assert(char_queue.enqueue('d'));
    assert(char_queue.enqueue('e'));
    assert(!char_queue.enqueue('f'));
    char let = char_queue.dequeue();
    assert(let == 'a');
    assert(char_queue.empty() == false);
    let = char_queue.dequeue();
    assert(let == 'b');
    assert(char_queue.empty() == false);
    let = char_queue.dequeue();
    assert(let == 'c');
    assert(char_queue.empty() == false);
    let = char_queue.dequeue();
    assert(let == 'd');
    assert(char_queue.empty() == false);
    let = char_queue.dequeue();
    assert(let == 'e');
    assert(char_queue.empty());
    cerr << "\n\t========================PASS========================\n" << endl;
}
#endif
#ifndef TEST3
{
    cerr << "\n\tTEST #3: Test Queue Order" << endl;
    Queue<char> char_queue(QUEUE_SIZE);
    char_queue.enqueue('a');
    char_queue.enqueue('b');
    char_queue.enqueue('z');
    char_queue.enqueue('y');
    char letd = char_queue.dequeue();
    assert(letd == 'a');
    char_queue.enqueue('x');
    char lete = char_queue.dequeue();
    assert(lete == 'b');
    char_queue.enqueue('w');
    char letz = char_queue.dequeue();
    assert(letz == 'z');
    char lety = char_queue.dequeue();
    assert(lety == 'y');
    char letx = char_queue.dequeue();
    assert(letx == 'x');
    char letw = char_queue.dequeue();
    assert(letw == 'w');
    assert(char_queue.empty());
    cerr << "\n\t========================PASS========================\n" << endl;
}
#endif
#ifndef TEST4
{
    cerr << "\n\tTEST #4: Test Copy Constructor" << endl;
    Queue<Test *> test_queue(QUEUE_SIZE);
    for(int i = 0; i < QUEUE_SIZE; i++)
        test_queue.enqueue(new Test(i, char('a'+i)));
    Queue<Test *> test_queue2(test_queue);
    for(int i = 0; i < QUEUE_SIZE; i++)
        delete test_queue2.dequeue();
}
#endif
#ifndef TEST5
{
    cerr << "\n\tTEST #5: Test Peek and Clear" << endl;
    Queue<Test> test_queue(QUEUE_SIZE);
    assert(test_queue.empty());
    test_queue.enqueue(Test(1, 'x'));
    test_queue.enqueue(Test(2, 'y'));
    test_queue.enqueue(Test(3, 'z'));
    Test obj = test_queue.peek();
    assert(obj.let == 'x');
    Test obj2 = test_queue.dequeue();
    assert(obj2.let == 'x');
    test_queue.clear();
    assert(test_queue.empty());
    cerr << "\n\t========================PASS========================\n" << endl;

}
#endif
#ifndef TEST6
{
    cerr << "\n\tTEST #6: Operator Overloading" << endl;
    Queue<Test> test_queue(QUEUE_SIZE);
    test_queue += Test(1, 'x');
    test_queue += Test(2, 'y');
    test_queue += Test(3, 'z');
    Test obj = test_queue.dequeue();
    assert(obj.let == 'x');
    obj = test_queue.dequeue();
    assert(obj.num == 2);
    obj = test_queue.dequeue();
    assert(obj.let == 'z');
    assert(test_queue.empty());
    cerr << "\n\t========================PASS========================\n" << endl;
    cerr << "\n\tDon't forget to run with Valgrind and commit to Github!\n" << endl;
}
#endif
    return 0;
}
