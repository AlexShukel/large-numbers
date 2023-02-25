//
// Created by alexs on 2023-02-25.
//

#ifndef ND1_COEFFICIENTSITERATOR_H
#define ND1_COEFFICIENTSITERATOR_H

#include <iterator>

// Source: https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp
template<class T>
class CoefficientsIterator {
public:
    explicit CoefficientsIterator(T *initialPointer, size_t size);

    T operator*() const;

    T *operator->() const;

    // Prefix increment
    CoefficientsIterator<T> &operator++();

    bool operator==(const CoefficientsIterator<T> &another);

    bool operator!=(const CoefficientsIterator<T> &another);

private:
    T *currentPointer;
    size_t size;
    size_t currentIndex = 0;

};

#endif //ND1_COEFFICIENTSITERATOR_H
