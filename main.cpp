#include <iostream>
#include <tuple>
#include "number.hpp"
#include <cmath>

int main() {

    seinventor::number<seinventor::base10> number1 {"1010"};
    seinventor::number<seinventor::base2> number2 {"0b01010101010101010"};
    seinventor::number<seinventor::base16> number3 {"0x0F"};
    seinventor::number<seinventor::base16> aNumber {"0x161616FF161616FF"};

    return 0;
}
