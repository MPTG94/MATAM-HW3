//
// Created by sivan on 06/01/2020.
//

#ifndef HW3_UNIQUEARRAYIMP_H
#define HW3_UNIQUEARRAYIMP_H

template<class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(unsigned int size) :
        size(size),
        array(new Element*[size]),
        histogram(new int[size]) {
    for (int i = 0; i < size; i++) {
        this->histogram[i] = 0;
    }
}

template<class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(const UniqueArray &other) :
        size(other->size),
        array(new Element*[other->size]),
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
    return false;
}

template<class Element, class Compare>
const Element *UniqueArray<Element, Compare>::operator[](const Element &element) const {
    return nullptr;
}

template<class Element, class Compare>
bool UniqueArray<Element, Compare>::remove(const Element &element) {
    return false;
}

template<class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::getCount() const {
    return 0;
}

template<class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::getSize() const {
    return 0;
}

template<class Element, class Compare>
UniqueArray UniqueArray<Element, Compare>::filter(const UniqueArray::Filter &f) const {
    return UniqueArray(0);
}

#endif //HW3_UNIQUEARRAYIMP_H