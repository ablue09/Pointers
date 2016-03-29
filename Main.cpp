#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>

using namespace std;

void output();

int main()
{
	//_CrtSetBreakAlloc(214);
#pragma region //Pointers

	int *p; //a pointer of type int
	int n = 5;

	p = &n; //value of p = address of n
	cout << "Value of variable n: " << n << endl; 
	cout << "Address of variable n: " << &n << endl; //& = address of operator
	cout << "p is a pointer. Value of p is address of n: " << p << endl;

	*p = 22; /**Dereference pointer p gives back value of n. 
			 Change value of n to 22*/
	cout << "Change value of n through pointer p. New value of n: " << *p << endl;
	cout << "Value of n: " << n << endl;

	double d = 10.0;
	double *pDbl; //a pointer of type double

	pDbl = &d;
	cout << "Value of variable d: " << d << endl;
#pragma endregion

#pragma region //Static vs Dynamic variables. Memory Leaks
	for(int j = 0; j < 10; j++)
	{
		output();
	}

	cout << endl;

	int *pDyn = new int(5); /**Dynamic variables have no name. 
							Creates a dynamic variable (on the heap) of type int w. value 5*/
	cout << "Value of dynamic variable: " << *pDyn << endl;

	*pDyn = 10;
	cout << "Change value of dynamic variable through a pointer *pDyn = " << *pDyn << endl;
	delete pDyn; //Delete memory on the heap that pDyn points to

	pDyn = new int;
	*pDyn = 20;
	cout << "Assign another dynamic variable to pDyn pointer: " << *pDyn << endl;
	delete pDyn;

	cout << "Value of pointer before assigning to NULL: " << pDyn << endl;
	pDyn = NULL; /**NULL pointer points to nothing & has value of 0
				 pDyn = nullptr;
				 pDyn = 0;*/
	cout << "The value of pointer after it is assigned to NULL: " << pDyn << endl;

	if(pDyn != NULL) /** if pointer is not pointing to nothing
					 if(pDyn) succeeds if pointer is Not Null (pointing to smt)
					 if(!pDyn) succeeds if pointer is Null (not pointing to smt)*/
	{
		*pDyn = 10;
	}

#pragma endregion

	//system("pause");

	if(_CrtDumpMemoryLeaks())
	{	
		cout << "--------------------------------" << endl;
		cout << "------- HAS memory leak! -------" << endl;
		cout << "--------------------------------" << endl;
	}
	else
	{
		cout << "--------------------------------" << endl;
		cout << "------- NO memory leaks! -------" << endl;
		cout << "--------------------------------" << endl;
	}

	return 0;
}

void output()
{
	static int i = 0; //Static variables are initialized only once & persists in memory until program ends
	cout << i << " ";
	i++;
}