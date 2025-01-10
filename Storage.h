#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <iostream>

int updateStock(int stock);
std::string changeState(const std::string& state);

template <typename T>
class Storage {
    T value;

public:
    explicit Storage(T val);

    T getValue() const;

    void setValue(T val);

    template <typename Func>
    void applyTransformation(Func transformation);

    void display() const;
};

template <typename T>
    Storage<T>::Storage(T val) : value(val) {}

template <typename T>
    T Storage<T>::getValue() const {
    return value;
}

template <typename T>
    void Storage<T>::setValue(T val) {
    value = val;
}

template <typename T>
template <typename Func>
    void Storage<T>::applyTransformation(Func transformation) {
    value = transformation(value);
}


template <typename T>
    void Storage<T>::display() const {
    std::cout << "Ingrediente in stoc curent: " << value << std::endl;
}


#endif // STORAGE_H