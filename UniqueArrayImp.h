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
        array(new Element*[size]),
        histogram(new int[size]) {
    for (int i = 0; i < size; i++) {
        this->histogram[i] = 0;
        this->array[i] = nullptr;
    }
}

// FIXME: consider changing the assignment of histogram array to all zeros before assigning new values in
template<class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(const UniqueArray &other) :
        size(other.getSize()),
        array(new Element *[other.getSize()]),
        histogram(new int[other.getSize()]) {
    for (int i = 0; i < size; i++) {
        Element *temp = other.getElementByIndex(i);
        if (temp == nullptr) {
            this->histogram[i] = 0;
        } else {
            this->array[i] = new Element(*temp);
            this->histogram[i] = 1;
        }

    }
}

template<class Element, class Compare>
UniqueArray<Element, Compare>::~UniqueArray() {
    for (int i =0; i< this->size; i++) {
        if (this->array[i] != nullptr && this->histogram[i] == 1) {
            delete this->array[i];
        }
    }
    delete this->array;
    delete this->histogram;
}

template<class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::insert(const Element &element) {
    const unsigned int position = this->contains(element);
    if (position != -1) {
        return position;
    }
    int i = 0;
    while (this->histogram[i] != 0 && i < this->size) {
        i++;
    }

    if (i == this->size) {
        throw UniqueArrayIsFullException();
    }

    this->histogram[i] = 1;
    Element* temp = new Element(element);
    this->array[i] = temp;
    return i;
}

template<class Element, class Compare>
bool UniqueArray<Element, Compare>::getIndex(const Element &element, unsigned int &index) const {
    Compare compare;
    for (int i = 0; i < this->size; i++) {
        if (this->histogram[i] != 0) {
            if (compare(element, *this->array[i])) {
            //if (Compare(), element == *this->array[i]) {
                index = i;
                return true;
            }
        }
    }
    return false;
}

template<class Element, class Compare>
const Element *UniqueArray<Element, Compare>::operator[](const Element &element) const {
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
        if (compare(*this->array[i], element)) {
        //if ((Compare(), *this->array[i]) == element) {
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
        count += this->histogram[i];
    }

    return count;
}

template<class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::getSize() const {
    return this->size;
}

// TODO: replace insert at index with full copy of the existing provided unique array and removing the filtered items
template<class Element, class Compare>
UniqueArray<Element, Compare> UniqueArray<Element, Compare>::filter(const UniqueArray::Filter &f) const {
    UniqueArray<Element, Compare> *filtered = new UniqueArray<Element, Compare>(this->getSize());
    for (int i =0; i< this->size; i++) {
        if (f.operator()(*this->array[i])) {
            filtered->insertAtIndex(i, *this->array[i]);
        }
    }

    return *filtered;
}

template<class Element, class Compare>
const int UniqueArray<Element, Compare>::contains(const Element &element) const {
    Compare compare;
    for (int i = 0; i < this->size; i++) {
        if (this->array[i] == nullptr) {
            continue;
        }

        if (compare(*this->array[i], element)) {
        //if ((Compare(), *this->array[i]) == element) {
            return i;
        }
    }

    return -1;
}

template<class Element, class Compare>
void UniqueArray<Element, Compare>::insertAtIndex(unsigned int index, const Element &element) {
    Element *temp = new Element(element);
    this->array[index] = temp;
    this->histogram[index] = 1;
}

template<class Element, class Compare>
int UniqueArray<Element, Compare>::getHistogramValueAtIndex(int index) {
    return this->histogram[index];
}

template<class Element, class Compare>
Element *UniqueArray<Element, Compare>::getElementByIndex(int index) const {
    if (this->histogram[index] == 1) {
        return this->array[index];
    }
    return nullptr;
}

#endif //HW3_UNIQUEARRAYIMP_H