#include "cell.h"

Cell::Cell() : value(0) {}

int Cell::getValue() const {
    return value;
}

void Cell::setValue(int value) {
    this->value = value;
}
