#ifndef EXVECTESTER_H
#define EXVECTESTER_H

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <assert.h>
#include "ezvec.h"

using namespace std;

class EzVecTester
{

private:
    void TestPushBack()
    {
        EzVec<int> ezVector;
        ezVector.push_back(1);
        ezVector.push_back(2); // 1 2
        ezVector.push_back(3); // 1 2 3
        assert(ezVector[0] == 1);
        assert(ezVector[1] == 2);
        assert(ezVector[2] == 3);
        assert(ezVector.size() == 3);
        cout << "TEST: PUSHBACK SUCCESSFUL" << endl;
    }

    void TestPushFront()
    {
        EzVec<int> ezVector;
        ezVector.push_front(1);
        ezVector.push_front(2); // 2 1
        ezVector.push_front(3); // 3 2 1
        assert(ezVector[0] == 3);
        assert(ezVector[1] == 2);
        assert(ezVector[2] == 1);
        assert(ezVector.size() == 3);
        cout << "TEST: PUSHFRONT SUCCESSFUL" << endl;
    }

    void TestPushBackAndPushFront()
    {
        EzVec<int> ezVector;
        ezVector.push_front(1); // 1
        ezVector.push_back(2); // 1 2
        ezVector.push_front(3); // 3 1 2
        ezVector.push_back(4); // 3 1 2 4 
        ezVector.push_front(5); // 5 3 1 2 4
        ezVector.push_back(6); // 5 3 1 2 4 6
        assert(ezVector[0] == 5);
        assert(ezVector[1] == 3);
        assert(ezVector[2] == 1);
        assert(ezVector[3] == 2);
        assert(ezVector[4] == 4);
        assert(ezVector[5] == 6);
        assert(ezVector.size() == 6);
        cout << "TEST: PUSHBACK PUSHFRONT SUCCESSFUL" << endl;
    }

    void TestPopBack()
    {
        EzVec<int> ezVector;
        ezVector.push_back(1);
        ezVector.push_front(2); // 2 1
        ezVector.push_back(3); // 2 1 3
        ezVector.pop_back();  // 2 1
        assert(ezVector[0] == 2);
        assert(ezVector[1] == 1);
        assert(ezVector.size() == 2);
        cout << "TEST: POPBACK SUCCESSFUL" << endl;
    }

    void TestPopFront()
    {
        EzVec<int> ezVector;
        ezVector.push_back(1);
        ezVector.push_front(2); // 2 1
        ezVector.push_back(3); // 2 1 3
        ezVector.pop_front();  // 1 3
        assert(ezVector[0] == 1);
        assert(ezVector[1] == 3);
        assert(ezVector.size() == 2);
        cout << "TEST: POPFRONT SUCCESSFUL" << endl;
    }

    void TestBack()
    {
        EzVec<int> ezVector;
        ezVector.push_back(1);
        ezVector.push_back(2); // 1 2
        ezVector.push_front(4); // 4 1 2
        ezVector.push_back(3); // 4 1 2 3
        ezVector.push_front(5); // 5 4 1 2 3
        ezVector.pop_back(); // 5 4 1 2
        ezVector.pop_front(); // 4 1 2
        assert(ezVector.back() == 2);
        cout << "TEST: BACK SUCCESSFUL" << endl;
    }

    void TestFront()
    {
        EzVec<int> ezVector;
        ezVector.push_back(1);
        ezVector.push_back(2); // 1 2
        ezVector.push_front(4); // 4 1 2
        ezVector.push_back(3); // 4 1 2 3
        ezVector.push_front(5); // 5 4 1 2 3
        ezVector.pop_back(); // 5 4 1 2
        ezVector.pop_front(); // 4 1 2
        assert(ezVector.front() == 4);
        cout << "TEST: FRONT SUCCESSFUL" << endl;
    }

    void TestResize()
    {
        EzVec<int> ezVector;
        ezVector.push_back(1);
        ezVector.push_back(2); // 1 2
        ezVector.push_front(4); // 4 1 2
        ezVector.push_back(3); // 4 1 2 3
        ezVector.push_front(5); // 5 4 1 2 3
        ezVector.pop_back(); // 5 4 1 2
        ezVector.pop_front(); // 4 1 2
        ezVector.resize(10);
        assert(ezVector.size() == 10);
        assert(ezVector.front() == 4);
        assert(ezVector.back() == 0);
        cout << "TEST: RESIZE SUCCESSFUL" << endl;
    }

    void print(const EzVec<int>& ezVector)
    {
        for (int i = 0; i < ezVector.size(); i++)
        {
            cout << ezVector[i] << " ";
        }
        cout << endl;
    }
    

public:
    void run()
    {
        // Testing functions
        TestPushBack();
        TestPushFront();
        TestPushBackAndPushFront();
        TestPopBack();
        TestPopFront();
        TestBack();
        TestFront();
        TestResize();
    }

};

#endif
