#include "BSTree.h"
#include "BSTree.h"
#include <iostream>
#include <string>
#include <ctime>
#include <cassert>
#include <cstdlib>
#include <vector>

using namespace std;

#define NUM_VALUES 12

void testList(vector<int> &list, vector<int> &compare){
    assert(list.size() == compare.size());
    for(unsigned int i = 0; i < list.size(); i++){
        cerr << " [" << list[i] << "] ";
        assert(list.at(i) == compare.at(i));
    }
    cerr << endl;
}

int main(int argv, char * argc[]){
    srand(time(NULL));

#ifndef TEST1
{
    cerr << "\n\tTEST #1: Create an empty tree" << endl;
    BSTree<int> tree;
    assert(tree.empty());

    cerr << "\n\t========================PASS========================\n" << endl;
}
#endif
#ifndef TEST2
{
    cerr << "\n\tTEST #2: Insert values into the Tree" << endl;

    int array[] = {5,3,10,8,2,1,7,9,6,12,11,13};
    BSTree<int> tree;
    for(int i = 0; i < NUM_VALUES; i++){
        tree.insert(array[i]);
        assert(!tree.empty());
    }
    cerr << "\n\t========================PASS========================\n" << endl;
}
#endif
#ifndef TEST3
{
    cerr << "\n\tTEST #3: Cannot insert duplicate values into the Tree" << endl;
    int array[] = {5,3,10,8,2,1,7,9,6,12,11,13};
    BSTree<int> tree;
    for(int i = 0; i < NUM_VALUES; i++){
        tree.insert(array[i]);
        assert(!tree.empty());
    }
    for(int i = 0; i < NUM_VALUES; i++){
        assert(!tree.insert(array[i]));
    }
    cerr << "\n\t========================PASS========================\n" << endl;
}
#endif
#ifndef TEST4
{
    cerr << "\n\tTEST #4: Insert 1000 Values into the Tree" << endl;

    BSTree<int> tree;
    for(int i = 0; i < 1000; i++)
    tree.insert(rand() % 10000);

    cerr << "\n\t========================PASS========================\n" << endl;
}
#endif
#ifndef TEST5
{
    cerr << "\n\tTEST #5: Find values in the tree" << endl;
    int array[] = {5,3,10,8,2,1,7,9,6,12,11,13};
    BSTree<int> tree;
    for(int i = 0; i < NUM_VALUES; i++) tree.insert(array[i]);
    for(int i = 1; i <= NUM_VALUES; i++){
        if(i != 4)
        assert(tree.find(i));
        else
        assert(!tree.find(i));
    }

    cerr << "\n\t========================PASS========================\n" << endl;
}
#endif
#ifndef TEST6
{
    cerr << "\n\tTEST #6: Find doesn't segfault on empty tree" << endl;

    BSTree<int> tree;
    assert(!tree.find(1));

    cerr << "\n\t========================PASS========================\n" << endl;
}
#endif
#ifndef TEST7
{
    cerr << "\n\tTEST #7: Cannot remove node that is not in the tree" << endl;
    int array[] = {5,3,10,8,2,1,7,9,6,12,11,13};
    BSTree<int> tree;
    for(int i = 0; i < NUM_VALUES; i++){
        tree.insert(array[i]);
        assert(!tree.empty());
    }
    assert(!tree.remove(25));
    vector<int> test;
    tree.sortedArray(test);
    vector<int> compare = {1,2,3,5,6,7,8,9,10,11,12,13};
    testList(test, compare);
    test.clear();

    cerr << "\n\t========================PASS========================\n" << endl;
}
#endif
#ifndef TEST8
{
    cerr << "\n\tTEST #8: Remove a leaf node" << endl;
    int array[] = {5,3,10,8,2,1,7,9,6,12,11,13};
    BSTree<int> tree;
    for(unsigned int i = 0; i < sizeof(array)/sizeof(int); i++)
    tree.insert(array[i]);
    assert(tree.remove(1));
    vector<int> test;
    tree.sortedArray(test);
    vector<int> compare = {2,3,5,6,7,8,9,10,11,12,13};
    testList(test, compare);
    test.clear();

    cerr << "\n\t========================PASS========================\n" << endl;
}
#endif
#ifndef TEST9
{
    cerr << "\n\tTEST #9: Remove single branch using the Short Circuit algorithm" << endl;
    int array[] = {5,3,10,8,2,7,9,6,12,11,13};
    BSTree<int> tree;
    for(unsigned int i = 0; i < sizeof(array)/sizeof(int); i++)
    tree.insert(array[i]);
    assert(tree.remove(7));
    vector<int> test;
    tree.sortedArray(test);
    vector<int> compare = {2,3,5,6,8,9,10,11,12,13};
    testList(test, compare);
    test.clear();

    cerr << "\n\t========================PASS========================\n" << endl;
}
#endif
#ifndef TEST10
{
    cerr << "\n\tTest #10: Remove two branch node promoting a leaf node" << endl;
    int array[] = {5,3,10,8,2,9,6,12,11,13};
    BSTree<int> tree;
    for(unsigned int i = 0; i < sizeof(array)/sizeof(int); i++)
    tree.insert(array[i]);
    assert(tree.remove(10));
    vector<int> test;
    tree.sortedArray(test);
    vector<int> compare = {2,3,5,6,8,9,11,12,13};
    testList(test, compare);
    test.clear();

    cerr << "\n\t========================PASS========================\n" << endl;
}
#endif
#ifndef TEST11
{
    cerr << "\n\tTEST #11: Remove two branch node promoting a 1 branch node using Short Circuit" << endl;
    int array[] = {5,3,8,2,9,6,12,11,13};
    BSTree<int> tree;
    for(unsigned int i = 0; i < sizeof(array)/sizeof(int); i++)
    tree.insert(array[i]);
    assert(tree.remove(11));
    vector<int> test;
    tree.sortedArray(test);
    vector<int> compare = {2,3,5,6,8,9,12,13};
    testList(test, compare);
    test.clear();

    cerr << "\n\t========================PASS========================\n" << endl;
}
#endif
#ifndef TEST12
{
    cerr << "\n\tTEST #12: Remove root with two branches" << endl;
    int array[] = {5,3,8,2,9,6,12,13};
    BSTree<int> tree;
    for(unsigned int i = 0; i < sizeof(array)/sizeof(int); i++)
    tree.insert(array[i]);
    assert(tree.remove(5));
    vector<int> test;
    tree.sortedArray(test);
    vector<int> compare = {2,3,6,8,9,12,13};
    testList(test, compare);
    test.clear();

    cerr << "\n\t========================PASS========================\n" << endl;
}
#endif
#ifndef TEST13
{
    cerr << "\n\tTEST #13: Remove root with one branch" << endl;
    int array[] = {3,8,2,9,6,12,13};
    BSTree<int> tree;
    for(unsigned int i = 0; i < sizeof(array)/sizeof(int); i++)
    tree.insert(array[i]);
    assert(tree.remove(3));
    assert(tree.remove(2));
    assert(tree.remove(6));
    vector<int> test;
    tree.sortedArray(test);
    vector<int> compare = {8,9,12,13};
    testList(test, compare);
    test.clear();

    cerr << "\n\t========================PASS========================\n" << endl;
}
#endif
#ifndef TEST14
{
    cerr << "\n\tTEST #14: Remove root as leaf" << endl;
    int array[] = {8,9,12,13};
    BSTree<int> tree;
    for(unsigned int i = 0; i < sizeof(array)/sizeof(int); i++)
    tree.insert(array[i]);
    assert(tree.remove(9));
    assert(tree.remove(8));
    assert(tree.remove(13));
    assert(tree.remove(12));
    vector<int> test;
    tree.sortedArray(test);
    assert(test.size() == 0);

    cerr << "\n\t========================PASS========================\n" << endl;
}
#endif
#ifndef TEST15
{
    cerr << "\n\tTEST #15: Deep copy for a tree of 100 random values" << endl;
    BSTree<int> tree;
    for(int i = 0; i < 100; i++){
        int value = rand() % 1000;
        tree.insert(value);
    }

    BSTree<int> copyTree(tree);
    vector<int> testCopy;
    vector<int> test;
    tree.sortedArray(test);
    copyTree.sortedArray(testCopy);
    assert(testCopy == test);

    cerr << "\n\t========================PASS========================\n" << endl;
}
#endif
#ifndef TEST16
{
    cerr << "\n\tTEST #16: Test deletion and Destructor" << endl;
    BSTree<int> * tree = new BSTree<int>();
    for(int i = 0; i < 100; i++) tree->insert(rand() % 1000);
    for(int i = 0; i < 1000; i++) tree->remove(i);
    assert(tree->empty());
    delete tree;
    cerr << "\n\t========================PASS========================\n" << endl;
}
#endif
#ifdef EXTRA
{
    cerr << "\n\tTEST #17: Test Balancing Tree" << endl;

    BSTree<int> unbalancedTree;
    unbalancedTree.balance();
    assert(unbalancedTree.empty());

    for(int i = 0; i < NUM_VALUES; i++){
        unbalancedTree.insert(i);
    }
    assert(unbalancedTree.height() == 11);
    unbalancedTree.balance();
    assert(unbalancedTree.height() == 3);

    cerr << "\n\t========================PASS========================\n" << endl;
}
#endif
    cerr << "\n\tAll Tests Passed.\nDon't forget to run with Valgrind and submit to Blackboard!\n" << endl;

    return 0;
}
