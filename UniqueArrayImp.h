//
// Created by sivan on 06/01/2020.
//

#ifndef HW3_UNIQUEARRAYIMP_H
#define HW3_UNIQUEARRAYIMP_H

#include "UniqueArray.h"

template<class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(unsigned int size) :
        size(size),
        array(new Element *[size]),
        histogram(new int[size]) {
    for (int i = 0; i < size; i++) {
        this->histogram[i] = 0;
    }
}

template<class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(const UniqueArray &other) :
        size(other->size),
        array(new Element *[other->size]),
        histogram(new int[other->size]) {
    for (int i = 0; i < size; i++) {
        this->histogram[i] = other->histogram[i];
        this->array[i] = other->array[i];
    }
}

template<class Element, class Compare>
UniqueArray<Element, Compare>::~UniqueArray() {
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
    this->array[i] = &element;
    return i;
}

template<class Element, class Compare>
bool UniqueArray<Element, Compare>::getIndex(const Element &element, unsigned int &index) const {
    for (int i = 0; i < this->size; i++) {
        if (this->histogram[i] != 0) {
            if (Compare(element, this->array[i])) {
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
    for (int i = 0; i < size; i++) {
        if ((Compare(), *this->array[i]) == element) {
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

template<class Element, class Compare>
UniqueArray<Element, Compare> UniqueArray<Element, Compare>::filter(const UniqueArray::Filter &f) const {
    UniqueArray<Element, Compare> filtered = new UniqueArray<Element, Compare>(this->size);
    for (int i =0; i< this->size; i++) {
        if (f.operator()(this->array[i])) {
            filtered.insertAtIndex(i, this->array[i]);
        }
    }

    return filtered;
}

template<class Element, class Compare>
const int UniqueArray<Element, Compare>::contains(const Element &element) {
    for (int i = 0; i < this->size; i++) {
        if ((Compare(), *this->array[i]) == element) {
            return i;
        }
    }

    return -1;
}

template<class Element, class Compare>
void UniqueArray<Element, Compare>::insertAtIndex(unsigned int index, const Element &element) {
    this->array[index] = element;
    this->histogram[index] = 1;
}

#endif //HW3_UNIQUEARRAYIMP_H