
#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

class bigint {
private:
    std::string digits; // dígitos en orden inverso (0 = unidades)

    void remove_leading_zeros() {
        while (digits.size() > 1 && digits.back() == '0')
            digits.pop_back();
    }

public:
    // Constructores
    bigint() : digits("0") {}
    bigint(unsigned long long n) {
        if (n == 0) digits = "0";
        else {
            while (n > 0) {
                digits.push_back('0' + n % 10);
                n /= 10;
            }
        }
    }
    bigint(const bigint& other) : digits(other.digits) {}
    bigint& operator=(const bigint& other) {
    if (this != &other) {
        digits = other.digits;
    }
    return *this;
}

    // Suma
    bigint operator+(const bigint& other) const {
        std::string res;
        size_t n = std::max(digits.size(), other.digits.size());
        int carry = 0;
        for (size_t i = 0; i < n || carry; ++i) {
            int d1 = i < digits.size() ? digits[i] - '0' : 0;
            int d2 = i < other.digits.size() ? other.digits[i] - '0' : 0;
            int sum = d1 + d2 + carry;
            res.push_back('0' + (sum % 10));
            carry = sum / 10;
        }
        while (res.size() > 1 && res.back() == '0')
            res.pop_back();
        bigint result;
        result.digits = res;
        return result;
    }

    // Operador +=
    bigint& operator+=(const bigint& other) {
        *this = *this + other;
        return *this;
    }

    // Comparación
    bool operator==(const bigint& other) const {
        return digits == other.digits;
    }
    bool operator!=(const bigint& other) const {
        return !(*this == other);
    }
    
    bool operator<(const bigint& other) const {
        if (digits.size() != other.digits.size())
            return digits.size() < other.digits.size();
        for (size_t i = digits.size(); i-- > 0;) {
            if (digits[i] != other.digits[i])
                return digits[i] < other.digits[i];
        }
        return false;
    }
    bool operator>(const bigint& other) const {
        return other < *this;
    }
    bool operator<=(const bigint& other) const {
        return !(other < *this);
    }
    bool operator>=(const bigint& other) const {
        return !(*this < other);
    }

    // Desplazamiento de dígitos (base 10)
    bigint operator<<(int shift) const {
        if (*this == bigint(0)) return *this;
        bigint res = *this;
        res.digits.insert(res.digits.begin(), shift, '0');
        return res;
    }
    bigint operator>>(int shift) const {
        if (digits.size() <= (size_t)shift)
            return bigint(0);
        bigint res = *this;
        res.digits.erase(res.digits.begin(), res.digits.begin() + shift);
        res.remove_leading_zeros();
        return res;
    }
    // Operador <<=
    bigint& operator<<=(int shift) {
        if (*this == bigint(0)) return *this;
        digits.insert(digits.begin(), shift, '0');
        return *this;
    }
    // Operador >>=
    bigint& operator>>=(int shift) {
        if (digits.size() <= (size_t)shift) {
            digits = "0";
        } else {
            digits.erase(digits.begin(), digits.begin() + shift);
        }
        remove_leading_zeros();
        return *this;
    }
    // Operador ++ prefijo
    bigint& operator++() {
        *this += bigint(1);
        return *this;
    }
    // Operador ++ sufijo
    bigint operator++(int) {
        bigint temp = *this;
        *this += bigint(1);
        return temp;
    }
    // Operador >>=(bigint)
    bigint& operator>>=(const bigint& other) {
        int shift = 0;
        for (size_t i = 0; i < other.digits.size(); ++i)
            shift += (other.digits[i] - '0') * static_cast<int>(std::pow(10, i));
        return (*this >>= shift);
    }

    // Output
    friend std::ostream& operator<<(std::ostream& os, const bigint& b) {
        for (size_t i = b.digits.size(); i-- > 0;)
            os << b.digits[i];
        return os;
    }
};

