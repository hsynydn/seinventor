#include "number.hpp"

int main(int argc, char** argv) {

    if(argc != 2){
        std::cerr << "Need arguments!\n";
        std::cerr << argv[0] << " <number-string>\n";
        exit(EXIT_FAILURE);
    }

    try {
        if(std::regex_match(argv[1], std::regex("^0x[0-9A-Fa-f]*"))){
            seinventor::number<seinventor::base16> number {argv[1]};
            std::cout << std::to_string(number.getNumber()) << std::endl;
        }else if(std::regex_match(argv[1], std::regex("^0b[0-1]*"))){
            seinventor::number<seinventor::base2> number {argv[1]};
            std::cout << std::to_string(number.getNumber()) << std::endl;
        }else{
            seinventor::number<seinventor::base10> number {argv[1]};
            std::cout << std::to_string(number.getNumber()) << std::endl;
        }
    }catch (seinventor::exception::InputFormatException& e){
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
