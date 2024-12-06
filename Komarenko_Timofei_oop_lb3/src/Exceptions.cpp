#include "Exceptions.hpp"


const char* incorrectShipPosition::what() const noexcept{
    return "Ошибка: корабли не могут пересекаться или соприкасаться!";
}

const char* noAbilities::what() const noexcept{
    return "Ошибка: нет доступных способностей!";
}
const char* outOfFieldAttack::what() const noexcept{
    return  "Ошибка: атака за пределы поля!";
}

const char* outOfFieldPosition::what() const noexcept{
    return  "Ошибка: корабль выходит за пределы карты!";
}


const char* incorrectCheckSum::what() const noexcept{
    return "Ошибка: контрольная сумма в файле не соответствует!";
}
