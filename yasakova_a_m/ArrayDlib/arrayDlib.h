//
// Created by Пользователь on 28.02.2023.
//

#ifndef ARRAYDLIB_ARRAYDLIB_H
#define ARRAYDLIB_ARRAYDLIB_H

class arrayD {
private:
    int size;
    int capacity;
    int *arr; // pointer to the array
public:
    arrayD(); // constructor
    arrayD(int initial_size);
    arrayD(const arrayD &other); // copy constructor
    ~arrayD();
    int get_size();
    int get_capacity();
    void push_back(int element);
    void pop_back();
    int& operator[](int index);
    arrayD& operator=(const arrayD &other); // assignment operator
};


#endif //ARRAYDLIB_ARRAYDLIB_H
