#include <iostream>
#include <stdlib.h>
#include "EzVec.h"
#include "EzVecTester.h"

using namespace std;


int main ()
{
	EzVecTester tester;
	tester.run();	

	// Use EzVec the same way as vector
	EzVec<int> ezVector;
	ezVector.push_back(1);
}