//
// Created by sivan on 06/01/2020.
//

#ifndef HW3_UNIQUEARRAYIMP_H
#define HW3_UNIQUEARRAYIMP_H

#include <iostream>

using namespace std;

#include "UniqueArray.h"

template<class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(unsigned int size) :
        size(size),
        array(new Element *[size]),
        histogram(new int[size]) {
    for (int i = 0; i < size; i++) {
        this->histogram[i] = 0;
        this->array[i] = nullptr;
    }
}

template<class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(const UniqueArray &other) :
        size(other.getSize()),
        array(new Element *[other.getSize()]),
        histogram(new int[other.getSize()]) {
    for (int i = 0; i < size; i++) {
        Element *temp = other.getElementByIndex(i);
        if (temp == nullptr) {
            this->histogram[i] = 0;
            this->array[i] = nullptr;
        } else {
            this->array[i] = new Element(*temp);
            this->histogram[i] = 1;
        }

    }
}

template<class Element, class Compare>
UniqueArray<Element, Compare>::~UniqueArray() {
    for (int i = 0; i < this->size; i++) {
        if (this->histogram[i] == 1 && this->array[i] != nullptr) {
            delete this->array[i];
        }
    }
    delete[] this->array;
    delete[] this->histogram;
}

template<class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::insert(const Element &element) {
    const unsigned int position = this->contains(element);
    if (position != -1) {
        return position;
    }
    int i = 0;
    while (i < this->size && this->histogram[i] != 0) {
        i++;
    }

    if (i == this->size) {
        throw UniqueArrayIsFullException();
    }

    this->histogram[i] = 1;
    Element *temp = new Element(element);
    this->array[i] = temp;
    return i;
}

template<class Element, class Compare>
bool UniqueArray<Element, Compare>::getIndex(const Element &element,
                                             unsigned int &index) const {
    Compare compare;
    for (int i = 0; i < this->size; i++) {
        if (this->histogram[i] != 0) {
            if (compare(element, *this->array[i])) {
                index = i;
                return true;
            }
        }
    }
    return false;
}

template<class Element, class Compare>
const Element *
UniqueArray<Element, Compare>::operator[](const Element &element) const {
    const int position = this->contains(element);
    if (position != -1) {
        return this->array[position];
    }
    return nullptr;
}

template<class Element, class Compare>
bool UniqueArray<Element, Compare>::remove(const Element &element) {
    Compare compare;
    for (int i = 0; i < size; i++) {
        if ((this->histogram[i] == 1) && compare(*this->array[i], element)) {
            delete this->array[i];
            this->array[i] = nullptr;
            this->histogram[i] = 0;
            return true;
        }
    }

    return false;
}

template<class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::getCount() const {
    unsigned int count = 0;
    for (int i = 0; i < this->size; i++) {
        count = count + this->histogram[i];
    }

    return count;
}

template<class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::getSize() const {
    return this->size;
}

template<class Element, class Compare>
UniqueArray<Element, Compare>
UniqueArray<Element, Compare>::filter(const UniqueArray::Filter &f) const {
    UniqueArray<Element, Compare> filtered(*this);
    for (int i = 0; i < this->size; i++) {
        if (!f(*this->array[i])) {
            filtered.remove(*this->array[i]);
        }
    }
    return filtered;
}

template<class Element, class Compare>
const int
UniqueArray<Element, Compare>::contains(const Element &element) const {
    Compare compare;
    for (int i = 0; i < this->size; i++) {
        if (this->histogram[i] == 0) {
            continue;
        }

        if (compare(*this->array[i], element)) {
            return i;
        }
    }

    return -1;
}

template<class Element, class Compare>
Element *
UniqueArray<Element, Compare>::getElementByIndex(unsigned int index) const {
    if (this->histogram[index] == 1) {
        return this->array[index];
    }
    return nullptr;
}

#endif //HW3_UNIQUEARRAYIMP_H