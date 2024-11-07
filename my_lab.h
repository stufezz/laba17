#include <iostream>
#include <stdexcept>
#include <algorithm>
using namespace std;

template <typename T>
class Set {
public:
    Set();
    Set(const Set& other);
    Set& operator=(const Set& other);
    ~Set();

    void insert(const T& value);
    bool find(const T& value) const;
    size_t size() const;
    Set unionWith(const Set& s) const;

    template <typename U>
    friend ostream& operator<<(ostream& os, const Set<U>& set);

private:
    T* elements;
    size_t count;
    size_t capacity;

    void resize();
};

template <typename T>
Set<T>::Set() : elements(nullptr), count(0), capacity(0) {}

template <typename T>
Set<T>::Set(const Set& other) : count(other.count), capacity(other.capacity) {
    elements = new T[capacity];
    for (size_t i = 0; i < count; i++) {
        elements[i] = other.elements[i];
    }
}

template <typename T>
Set<T>& Set<T>::operator=(const Set& other) {
    if (this == &other) return *this;

    delete[] elements;

    count = other.count;
    capacity = other.capacity;
    elements = new T[capacity];
    for (size_t i = 0; i < count; i++) {
        elements[i] = other.elements[i];
    }

    return *this;
}

template <typename T>
Set<T>::~Set() {
    delete[] elements;
}

template <typename T>
void Set<T>::insert(const T& value) {
    if (find(value)) return;

    if (count == capacity) resize();

    elements[count++] = value;
    sort(elements, elements + count);
}

template <typename T>
bool Set<T>::find(const T& value) const {
    return binary_search(elements, elements + count, value);
}

template <typename T>
size_t Set<T>::size() const {
    return count;
}

template <typename T>
Set<T> Set<T>::unionWith(const Set& s) const {
    Set result = *this;
    for (size_t i = 0; i < s.size(); ++i) {
        result.insert(s.elements[i]);
    }
    return result;
}

template <typename T>
void Set<T>::resize() {
    capacity = (capacity == 0) ? 1 : capacity * 2;
    T* newElements = new T[capacity];
    for (int i = 0; i < count; i++){
        newElements[i] = elements[i];
    }
    delete[] elements;
    elements = newElements;
}

template <typename T>
ostream& operator<<(ostream& os, const Set<T>& set) {
    os << "{ ";
    for (size_t i = 0; i < set.size(); ++i) {
        os << set.elements[i] << (i < set.size() - 1 ? ", " : " ");
    }
    os << "}";
    return os;
}
