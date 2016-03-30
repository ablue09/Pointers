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

void sneaky(int& temp);
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

#pragma region //Array pointer
	int* pA;
	int a[10];
	int index;

	for (index = 0; index < 10; index++)
		a[index] = index;

	pA = a;

	for (index = 0; index < 10; index++)
		cout << pA[index] << " ";
	cout << endl;

	for (index = 0; index < 10; index++)
		pA[index] = pA[index] + 1;

	for (index = 0; index < 10; index++)
		cout << a[index] << " ";
	cout << endl;
#pragma endregion

#pragma region //Reference Parameter in a Function
    // Initialize a variable
    int v = 77;

    cout << "Before call to function v == " << v << endl;

    sneaky(v);

    cout << "After call to function v == " << v << endl;
#pragma endregion

#pragma region //Dynamic Allocation (cont...). Memory Leaks
// Initialize two pointers
    int *p1c, *p2c;

    // Dynamically allocate one integer
    p1c = new int;

    // Initialize value of dynamically allocated integer
    *p1c = 42;

    // Set the other pointer to point to this variable as well
    p2c = p1c;

    cout << "*p1c == " << *p1c << endl;
    cout << "*p2c == " << *p2c << endl;

    // Change value of dynamically allocated variable
    *p2c = 53;

    cout << "*p1c == " << *p1c << endl;
    cout << "*p2c == " << *p2c << endl;

    // Allocate another variable dynamically
    p1c = new int;

    // Initialize value of second dynamically allocated variable
    *p1c = 88;

    cout << "*p1c == " << *p1c << endl;
    cout << "*p2c == " << *p2c << endl;

    // Free up dynamically allocated variables, to avoid a memory leak
    delete p1c;
    delete p2c;

    cout << "Hope you got the point of this example!\n";

	//int* pM;
	//new int(9);
	//*pM = 10;
#pragma endregion

	//system("pause");

#pragma region //Display Memory Leak warning
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
#pragma endregion

	return 0;
}

/* sneaky()
 *
 * Demonstrates how referencess can be used to change a parameter's value.
 *
 * Requires: A reference to an initialized integer.
 * Modifies: The value of the parameter.
 */
void sneaky(int& temp)
{
    temp = 99;
    cout << "Inside function call temp == "
         << temp << endl;
}

void output()
{
	static int i = 0; //Static variables are initialized only once & persists in memory until program ends
	cout << i << " ";
	i++;
}