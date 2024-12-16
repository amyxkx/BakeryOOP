//
// Created by amalia on 12/16/2024.
//

#ifndef EROARECLIENT_H
#define EROARECLIENT_H

#include <exception>


class EroareInput : public std::exception {
public:
    // Pure virtual function
    [[nodiscard]] const char* what() const noexcept override = 0;

    // Virtual destructor (best practice for polymorphic classes)
    ~EroareInput() override = default;
};

#endif //EROARECLIENT_H
