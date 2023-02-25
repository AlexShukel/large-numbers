//
// Created by alexs on 2023-02-25.
//

#include "CoefficientsIterator.h"

template<class T>
CoefficientsIterator<T>::CoefficientsIterator(T *initialPointer, size_t size): currentPointer(
        initialPointer), size(size) {}

template<class T>
T CoefficientsIterator<T>::operator*() const {
    if (currentIndex >= size) {
        return 0;
    }

    return *currentPointer;
}

template<class T>
T *CoefficientsIterator<T>::operator->() const { return currentPointer; }

template<class T>
CoefficientsIterator<T> &CoefficientsIterator<T>::operator++() {
    ++currentPointer;
    ++currentIndex;
    return *this;
}

template<class T>
bool CoefficientsIterator<T>::operator==(const CoefficientsIterator<T> &another) {
    return currentPointer == another.currentPointer;
}

template<class T>
bool CoefficientsIterator<T>::operator!=(const CoefficientsIterator<T> &another) {
    return currentPointer != another.currentPointer;
}

template
class CoefficientsIterator<uint8_t>;

template
class CoefficientsIterator<uint32_t>;
