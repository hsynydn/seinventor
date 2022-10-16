#ifndef SEINVERTOR_BASE_HPP
#define SEINVERTOR_BASE_HPP

#include <array>
#include <tuple>
#include <string>
#include <utility>
#include <memory>
#include <vector>

namespace seinventor{

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

    class base10{
    public:
        static constexpr std::array<range, 1> kDigitRange {range{kChar_0, kChar_9}};
    };

    class base2{
    public:
        static constexpr std::array<range, 1> kDigitRange {range{kChar_0, kChar_1}};
    };

    class base16{
    public:
        static constexpr std::array<range, 3> kDigitRange {range{kChar_0, kChar_9}, range{kChar_A, kChar_F}, range{kChar_a, kChar_f}};
    };

    namespace exception{
        class AllowableDigitPolicy : std::exception{
        public:
            [[nodiscard]] const char* what() const noexcept override {
                return msg_;
            }
        private:
            static constexpr char msg_ [kExceptionMax]  {"Violation of Allowable Digit Policy"};
        };
    }

    template <typename T, typename K>
    class ConversionPolicy{
    public:
        virtual bool validate(const T&) const = 0;
    };

    template <typename Base>
    class AllowableDigitPolicy : public ConversionPolicy<uint8_t, Base>{
    public:
        static AllowableDigitPolicy& getInstance(){
            static AllowableDigitPolicy<Base> instance;
            return instance;
        }

        [[nodiscard]] bool validate(const uint8_t& digit) const override {
            for (auto range: Base::kDigitRange) {
                if (digit <= std::get<kRangeMax>(range) && digit >= std::get<kRangeMin>(range)) {
                    return true;
                }
            }
            return false;
        }

    private:
        AllowableDigitPolicy() = default;
        AllowableDigitPolicy(AllowableDigitPolicy&) = default;
        AllowableDigitPolicy(AllowableDigitPolicy&&)  noexcept = default;
    };

    class Convertable{
    public:
    };

    template <typename Base>
    class number{
    public:

        static constexpr int kMaxBuffer = 64;

        explicit number(std::string data){
            for (auto c : data) {
                if (!AllowableDigitPolicy<Base>::getInstance().validate(c)){
                    throw seinventor::exception::AllowableDigitPolicy();
                }
            }
        };
    private:
        std::array<uint8_t, kMaxBuffer> buffer;
    };

}

#endif // SEINVERTOR_BASE_HPP
