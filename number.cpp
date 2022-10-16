#include "number.hpp"

std::regex seinventor::base2::mFormat {"^0b[0]*(1[0-1]{0,63}){0,1}$"};
std::regex seinventor::base10::mFormat {"^[0]*([1-9][0-9]{0,18}){0,1}$"};
std::regex seinventor::base16::mFormat {"^0x[0]*([1-9A-Fa-f][0-9A-Fa-f]{0,15}){0,1}$"};