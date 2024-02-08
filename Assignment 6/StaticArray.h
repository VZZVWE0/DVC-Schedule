//Programmer: Anna Felipe
//Programmer ID: 1506055

#include <iostream>
using namespace std;

#ifndef LAB_EXERCISE_3
#define LAB_EXERCISE_3

template <typename T, int CAP>
class StaticArray {

private:

	T values[CAP];
	T dummy;

public:

	StaticArray();
	int capacity() const;
	T operator[](int) const; //getter
	T& operator[](int); //setter



};

template <typename T, int CAP>
StaticArray<T, CAP>::StaticArray() {

	for (int i = 0; i < CAP; i++) {

		values[i] = T();
	}
}


template <typename T, int CAP>
int StaticArray<T, CAP>::capacity() const {

	return CAP;
}


template <typename T, int CAP>
T StaticArray<T, CAP>::operator[](int index) const {

	if (index < 0 || index >= CAP) {

		cout << "Out of range." << endl;

		return T();
	}
	else {

		return values[index];
	}
}


template <typename T, int CAP>
T& StaticArray<T, CAP>::operator[](int index) {

	if (index < 0 || index >= CAP) {

		return dummy;
	}
	else {

		return values[index];
	}

}


#endif LAB_EXERCISE_3

#pragma once


