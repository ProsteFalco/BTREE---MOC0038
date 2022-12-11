#include<iostream>
#include <fstream>
#include "BTree.h"

using namespace std;

int main()
{
	BTree t(3); 
	int array[26] = { 1, 3, 7, 10, 11, 15, 90, 12, 4, 80, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 2, 45, 26, 33, 49 };

	for (int i = 0; i < 26; i++) {
		cout << "Inserting " << array[i] << ": " << endl;
		t.insert(array[i]);
		t.Printout();
		cout << endl << endl;
	}

	for (int i = 0; i < 10; i++) {
		cout << "Deleting " << array[i] << ": " << endl;
		t.remove(array[i]);
		t.Printout();
		cout << endl << endl;
	}

	cout << t.search(33) <<endl;
	cout << t.search(1000);

	return 0;
}