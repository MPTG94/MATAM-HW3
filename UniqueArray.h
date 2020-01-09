#ifndef MTMPARKINGLOT_UNIQUEARRAY_H
#define MTMPARKINGLOT_UNIQUEARRAY_H

template<class Element, class Compare = std::equal_to<Element>>
class UniqueArray {

private:
    const unsigned int size;
    Element **array;
    int *histogram;

public:

    /**
     * Creates a UniqueArray object of the provided Class with the specified
     * size
     * @param size The size of the UniqueArray
     */
    explicit UniqueArray(unsigned int size);

    /**
     * Copies an instance of UniqueArray to a new UniqueArray object
     * @param other The UniqueArray to copy
     */
    UniqueArray(const UniqueArray &other);

    /**
     * Deletes an instance of UniqueArray
     */
    ~UniqueArray();

    UniqueArray &operator=(const UniqueArray &) = delete;

    /**
     * Inserts a new object to the UniqueArray if it doesn't already exist
     * @param element The object to insert to the UniqueArray
     * @return The index of the object in the UniqueArray
     */
    unsigned int insert(const Element &element);

    void insertAtIndex(unsigned int index, const Element &element);

    /**
     * Checks if an element exists in the UniqueArray and returns it's index
     * @param element The element to get it's stored index
     * @param index An index reference to store the index the Object is stored
     * in, inside the UniqueArray
     * @return true if the object exists in the UniqueArray, false otherwise
     */
    bool getIndex(const Element &element, unsigned int &index) const;

    /**
     * Returns a pointer to an object from the UniqueArray
     * @param element The object to return from the UniqueArray
     * @return A pointer to the input Object, nullptr if the object does not
     * exist
     */
    const Element *operator[](const Element &element) const;

    /**
     * Removes an element from the UniqueArray
     * @param element The object to remove from the UniqueArray
     * @return true if the object was removed, false otherwise
     */
    bool remove(const Element &element);

    /**
     * Returns the number of stored objects in the UniqueArray
     * @return The number of stored objects in the UniqueArray
     */
    unsigned int getCount() const;

    /**
     * Returns the size of the UniqueArray
     * @return The size of the UniqueArray
     */
    unsigned int getSize() const;

    /**
     * Checks if an object exists in the UniqueArray
     * @param element The object to check if it is in the UniqueArray
     * @return true if the object is in the UniqueArray, false otherwise
     */
    const int contains(const Element &element) const;

    int getHistogramValueAtIndex(int index);

    /**
     * Returns a pointer of an object in the UniqueArray by it's index
     * @param index The index of the object in the UniqueArray
     * @return A pointer of the object at the input index
     */
    Element *getElementByIndex(int index) const;

    class Filter {
    public:
        virtual bool operator()(const Element &) const = 0;
    };

    /**
     * Creates a new instance of UniqueArray according to the provided filter
     * @param f A filter class instance to create a new UniqueArray with
     * @return A UniqueArray containing only the objects which passed filtering,
     * object will be in the same place they were in the original UniqueArray
     */
    UniqueArray filter(const Filter &f) const;

    class UniqueArrayIsFullException {
    };

};

#include "UniqueArrayImp.h"

#endif //MTMPARKINGLOT_UNIQUEARRAY_H
