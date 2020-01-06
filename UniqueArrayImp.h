//
// Created by sivan on 06/01/2020.
//

#ifndef HW3_UNIQUEARRAYIMP_H
#define HW3_UNIQUEARRAYIMP_H

template<class Element, class Compare = std::equal_to<Element>>
UniqueArray<Element>::UniqueArray(unsigned int size) :
        size(size),
        array(new Element[size]),
        histogram(new int[size]) {
    for (int i = 0; i < size; i++) {
        this->histogram[i] = 0;
    }
}

template<class Element, class Compare = std::equal_to<Element>>
UniqueArray<Element>::UniqueArray(const UniqueArray &other) :
        size(other->size),
        array(new Element[other->size]),
        histogram(new int[other->size]) {
    for (int i = 0; i < size; i++) {
        this->histogram[i] = other->histogram[i];
        this->array[i] = other->array[i];
    }
}

template<class Element, class Compare = std::equal_to<Element>>
UniqueArray<Element>::~UniqueArray() {
    delete this->array;
    delete this->histogram;
}

template<class Element, class Compare = std::equal_to<Element>>
unsigned int UniqueArray<Element>::insert(const Element &element) {
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


#endif //HW3_UNIQUEARRAYIMP_H
