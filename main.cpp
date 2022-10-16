#include <iostream>
#include <tuple>
#include "base.hpp"

int main() {



    std::tuple<int64_t, int64_t> a{-9223372036854775808, -9223372036854775808};

    std::cout << INTMAX_MIN << std::endl;


//    try{
//        seinventor::number<seinventor::base10> number5 {"020110011"};
//    }catch (seinventor::exception::AllowableDigitPolicy& e){
//        std::cout << e.what() << std::endl;
//    }



    return 0;
}
