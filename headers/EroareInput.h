#ifndef EROARECLIENT_H
#define EROARECLIENT_H

#include <exception>


class EroareInput : public std::exception {
public:
    [[nodiscard]] const char* what() const noexcept override = 0;
    ~EroareInput() override = default;
};

#endif
