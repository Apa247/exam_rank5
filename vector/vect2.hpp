#include <iostream>
#include <string>

class vect2 {
    private:
        int x, y;
    public:
        vect2() : x(0), y(0) {}
        vect2(int a, int b) : x(a), y(b) {}
        ~vect2() {}

        friend std::ostream& operator<<(std::ostream& os, const vect2& vec) {
            os << "{" << vec.x << ", " << vec.y << "}";
            return os;
        }

        int& operator[](int n) {
            return n == 0 ? x : y;
        }
        int operator[](int n) const {
            return n == 0 ? x : y;
        }

        vect2 operator*(int n) const {
            return vect2(x * n, y * n);
        }
        vect2& operator*=(int n) {
            x *= n;
            y *= n;
            return *this;
        }

        vect2 operator+(const vect2& vec) const {
            return vect2(x + vec.x, y + vec.y);
        }
        vect2& operator+=(const vect2& vec) {
            x += vec.x;
            y += vec.y;
            return *this;
        }

        vect2 operator-(const vect2& vec) const {
            return vect2(x - vec.x, y - vec.y);
        }
        vect2& operator-=(const vect2& vec) {
            x -= vec.x;
            y -= vec.y;
            return *this;
        }

        bool operator==(const vect2& vec) const {
            return x == vec.x && y == vec.y;
        }
        bool operator!=(const vect2& vec) const {
            return x != vec.x || y != vec.y;
        }

        vect2 operator-() const {
            return vect2(-x, -y);
        }

        vect2 operator++(int) {
            vect2 temp(*this);
            x++;
            y++;
            return temp;
        }
        vect2& operator++() {
            x++;
            y++;
            return *this;
        }
        vect2 operator--(int) {
            vect2 temp(*this);
            x--;
            y--;
            return temp;
        }
        vect2& operator--() {
            x--;
            y--;
            return *this;
        }

        friend vect2 operator*(int n, const vect2& vec) {
            return vect2(vec.x * n, vec.y * n);
        }
};