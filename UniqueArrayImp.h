//
// Created by sivan on 06/01/2020.
//

#ifndef HW3_UNIQUEARRAYLMP_H
#define HW3_UNIQUEARRAYLMP_H

template<class Element, class Compare = std::equal_to <Element>>
UniqueArray<Element>::UniqueArray(unsigned int size) :
        size(size),
        array(new Element[size]),
        histogram(new int[size]) {
    for (int i = 0; i < size; i++) {
        this->histogram[i] = 0;
    }
}

template<class Element, class Compare = std::equal_to <Element>>
UniqueArray<Element>::UniqueArray(const UniqueArray& other) :
        size(other->size),
        array(new Element[other->size]),
        histogram(new int[other->size]) {
    for (int i = 0; i < size; i++) {
        this->histogram[i] = other->histogram[i];
        this->array[i] = other->array[i];
    }
}

template<class Element, class Compare = std::equal_to <Element>>
UniqueArray<Element>::~UniqueArray() {
    delete this->array;
    delete this->histogram;
}


#endif //HW3_UNIQUEARRAYLMP_H
