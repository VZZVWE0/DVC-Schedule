//COMSC 210 Module 4
//DynamicArray Header file
//Instructor solution file

#ifndef DynamicArray_h
#define DynamicArray_h
template <typename T>
class DynamicArray
{
    T* value; // T datatype CAP compasity
    int cap;
    T dummy;

public:
    DynamicArray(int = 2); // constructor // default = 2
    DynamicArray(const DynamicArray<T>&); // copy constructor
    ~DynamicArray() { delete[] value; } // destructor
    DynamicArray<T>& operator=(const DynamicArray<T>&); // assignment operator
    int capacity() const { return cap; }
    void capacity(int); // setter
    T operator[ ] (int) const; // getter
    T& operator[ ] (int); // setter
};

template <typename T>
DynamicArray<T>::DynamicArray(int cap) // consturctor
{
    this->cap = cap;
    value = new T[cap];

    for (int i = 0; i < cap; i++)
        value[i] = T();
}

template <typename T>
T DynamicArray<T>::operator[ ] (int index) const // getter
{
    if (index < 0 || index >= cap) return dummy;
    return value[index];
}

template <typename T>
T& DynamicArray<T>::operator[ ] (int index) // setter
{
    if (index < 0) return dummy;
    if (index >= cap) capacity(2 * index);
    return value[index];
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& original)
{
    cap = original.cap; // still just a copy
    value = new T[cap]; // not a copy -- new object gets its own array
    for (int i = 0; i < cap; i++) // copy the contents of the array from the original...
        value[i] = original.value[i]; // ...to the copy
    dummy = original.dummy; // not really necessary because who cares what dummy contains?
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& original)
{
    if (this != &original) // of it's not a self copy...
    {
        // do what the destructor does
        delete[] value;

        // do what the copy constructor does
        cap = original.cap; // still just a copy
        value = new T[cap]; // not a copy -- new object gets its own array
        for (int i = 0; i < cap; i++) // copy the contents of the array from the original...
            value[i] = original.value[i]; // ...to the copy
        dummy = original.dummy; // not really necessary because who cares what dummy contains?
    }
    return *this; // return a self reference
}

template <typename T>
void DynamicArray<T>::capacity(int cap)
{
    T* temp = new T[cap];
    int limit = cap < this->cap ? cap : this->cap;

    for (int i = 0; i < limit; i++)
        temp[i] = value[i];

    for (int i = limit; i < cap; i++)
        temp[i] = T();

    delete[] value;
    value = temp;
    this->cap = cap;
}

#endif
