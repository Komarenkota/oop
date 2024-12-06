#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <iostream>

class incorrectShipPosition : public std::exception {
public:
    const char* what() const noexcept override;
};


class noAbilities : public std::exception {
public:
    const char* what() const noexcept override;
};

class outOfFieldAttack : public std::exception{
public:
    const char* what() const noexcept override;
};

class outOfFieldPosition: public std::exception {
public:
    const char* what() const noexcept override;
};

class incorrectCheckSum: public std::exception {
public:
    const char* what() const noexcept override;
};

#endif
