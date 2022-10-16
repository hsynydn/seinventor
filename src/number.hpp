#ifndef SEINVERTOR_NUMBER_HPP
#define SEINVERTOR_NUMBER_HPP

#include <string>
#include <array>
#include <utility>
#include <memory>
#include <vector>
#include <iostream>
#include <tuple>
#include <regex>

namespace {

    typedef std::tuple<int, int> range;
    typedef std::tuple<uint64_t, uint64_t> range_l;

    constexpr int kRangeMin {0};
    constexpr int kRangeMax {1};
    constexpr int kExceptionMax {128};
    constexpr int kChar_0 {48};
    constexpr int kChar_1 {49};
    constexpr int kChar_9 {57};
    constexpr int kChar_A {65};
    constexpr int kChar_F {70};
    constexpr int kChar_a {97};
    constexpr int kChar_f {102};

    class Unsigned{
    public:
        static constexpr std::array<range_l, 1> kNumberRange {range_l{0, UINTMAX_MAX}};
    };

    class Signed{
    public:
        static constexpr std::array<range_l, 1> kNumberRange {range_l{INTMAX_MIN, INTMAX_MAX}};
    };

    template<typename T, typename K>
    class Policy {
    public:
        virtual bool validate(const T &) const = 0;
    };

    template <typename Base>
    class FormattingPolicy : public Policy<std::string, Base>{
    public:
        static FormattingPolicy& getInstance(){
            static FormattingPolicy<Base> instance;
            return instance;
        }

        [[nodiscard]] bool validate(const std::string& input) const override {
            if (std::regex_match(input, Base::mFormat)){
                return true;
            }
            return false;
        }

    private:
        FormattingPolicy() = default;
        FormattingPolicy(FormattingPolicy&) = default;
        FormattingPolicy(FormattingPolicy&&)  noexcept = default;
    };
}

namespace seinventor{

    class base10{
    public:
        static constexpr int mIndex {0};
        static constexpr int mBase {10};
        static std::regex mFormat;
        static constexpr std::array<range, 1> kDigitRange {range{kChar_0, kChar_9}};
    };

    class base2{
    public:
        static constexpr int mIndex {2};
        static constexpr int mBase {2};
        static std::regex mFormat;
        static constexpr std::array<range, 1> kDigitRange {range{kChar_0, kChar_1}};
    };

    class base16{
    public:
        static constexpr int mIndex {0};
        static constexpr int mBase {16};
        static std::regex mFormat;
        static constexpr std::array<range, 3> kDigitRange {range{kChar_0, kChar_9}, range{kChar_A, kChar_F}, range{kChar_a, kChar_f}};
    };

    namespace exception{
        class InputFormatException : std::exception{
        public:
            [[nodiscard]] const char* what() const noexcept override {
                return msg_;
            }
        private:
            static constexpr char msg_ [kExceptionMax]  {"Violation of Input Format"};
        };
    }

    template <typename Base>
    class number{
    public:

        static constexpr int kMaxBuffer = 64;

        explicit number(std::string  data) : mData(std::move(data)){
            if (!FormattingPolicy<Base>::getInstance().validate(mData)){
                throw seinventor::exception::InputFormatException();
            }

            mNum = std::strtoull(mData.c_str() + Base::mIndex, 0, Base::mBase);
        };

        uint64_t getNumber(){
            return mNum;
        }

    private:
        std::string mData;
        uint64_t mNum;
    };

}

#endif // SEINVERTOR_NUMBER_HPP
