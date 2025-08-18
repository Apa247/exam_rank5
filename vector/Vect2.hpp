#include <iostream>
#include <string>

class vect2 {

    private:
        int x, y;

    public:
        vect2() : x(0), y(0) {}
        vect2(int a, int b) : x(a), y(b) {}
        ~vect2() {}

        void print(std::ostream& os) const {
            os << "{" << x << ", " << y << "}" << std::endl;
        }

        friend std::ostream& operator<<(std::ostream& os, const vect2& vec) {
            vec.print(os);
            return os;
        }
        
        int& operator[](int n) {
            return n == 0 ? x : y;
        }

        int operator[](int n) const {
            return n == 0 ? x : y;
        }

        vect2 operator*(int n) {
            vect2 v (v.x * n, v.y * n);
            return v;
        }

        vect2 operator*(const vect2& vec) {
            vect2 v(vec.x * x, vec.y *y);
            return v;
        }
        
        friend vect2 operator*(int n, const vect2& vec) {
            vect2 vecr(vec.x * n, vec.y *n);
            return vecr;
        }

        vect2 operator+(int n) {
            vect2 v (v.x + n, v.y + n);
            return v;
        }

        vect2 operator+(const vect2& vec) {
            vect2 v(vec.x + x, vec.y +y);
            return v;
        }
        
        friend vect2 operator+(int n, const vect2& vec) {
            vect2 vecr(vec.x + n, vec.y +n);
            return vecr;
        }

        bool operator==(const vect2& vec){
            return(vec.x == x && vec.y == y);
        }

        bool operator!=(const vect2& vec){
            return(vec.x != x || vec.y != y);
        }

        vect2& operator-=(int n) {
            this->x -= n;
            this->y -= n;
            return *this;
        }

        vect2 operator-=(const vect2& vec) {
            x -= vec.x;
            y -= vec.y;
            return *this;
        }
        
        vect2& operator+=(int n) {
            this->x += n;
            this->y += n;
            return *this;
        }

        vect2 operator+=(const vect2& vec) {
            x += vec.x;
            y += vec.y;
            return *this;
        }

        vect2 operator--() {
            vect2 vecr(x, y);
            x--;
            y--;
            return vecr;
        }

        vect2& operator--(int) {
            x--;
            y--;
            return *this;
        }

        vect2 operator++() {
            vect2 vecr(x, y);
            x++;
            y++;
            return vecr;
        }

        vect2& operator++(int) {
            x++;
            y++;
            return *this;
        }
};