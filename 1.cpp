#include <cassert>
#include <cctype>
#include <iostream>

using namespace std;
int abs(int a) { return a > 0 ? a : -a; }

class Fraction {
   private:
    int num, den;
    int gcd(int a, int b) {
        assert(a > 0 && b > 0);
        if (a > b)
            return (a % b == 0 ? b : gcd(b, a % b));
        else
            return (b % a == 0 ? a : gcd(a, b % a));
    }

   public:
    Fraction(int a, int b, int c) {
        int positive = (abs(a) / a) * (abs(b) / b) * (abs(c) / c);
        a = abs(a);
        b = abs(b);
        c = abs(c);
        int g = gcd(b, c);
        b /= g;
        c /= g;
        num = (b + a * c) * positive;
        den = c;
    }
    Fraction(int b, int c = 1) {
        if (b == 0) {
            num = b;
            den = abs(c);
            return;
        }
        int positive = (abs(b) / b) * (abs(c) / c);
        b = abs(b);
        c = abs(c);
        int g = gcd(b, c);
        b /= g;
        c /= g;
        num = b * positive;
        den = c;
    }
    friend ostream& operator<<(ostream& o, Fraction const& f);
    friend istream& operator>>(ostream& i, Fraction& f);
    friend Fraction operator+(Fraction const& f1, Fraction const& f2);
    friend Fraction operator-(Fraction const& f1, Fraction const& f2);
    friend Fraction operator*(Fraction const& f1, Fraction const& f2);
    friend Fraction operator/(Fraction const& f1, Fraction const& f2);
    friend Fraction& operator+=(Fraction& f1, Fraction const& f2);
    friend Fraction& operator-=(Fraction& f1, Fraction const& f2);
    friend Fraction& operator*=(Fraction& f1, Fraction const& f2);
    friend Fraction& operator/=(Fraction& f1, Fraction const& f2);
    friend Fraction operator-(Fraction const& f1);
    friend bool operator<(Fraction const& f1, Fraction const& f2);
    friend bool operator==(Fraction const& f1, Fraction const& f2);
    friend bool operator>(Fraction const& f1, Fraction const& f2);
    friend Fraction& operator++(Fraction& f1);
    friend Fraction& operator++(Fraction& f1, int a);
    friend Fraction& operator--(Fraction& f1);
    friend Fraction& operator--(Fraction& f1, int a);
};

ostream& operator<<(ostream& o, Fraction const& f) {
    return o << f.num << "/" << f.den;
}
istream& operator>>(istream& i, Fraction& f) {
    int num, den;
    scanf("%d/%d", &num, &den);
    Fraction temp(num, den);
    f = temp;
    return i;
}

Fraction operator+(Fraction const& f1, Fraction const& f2) {
    int num = f1.num * f2.den + f2.num * f1.den,
        den = f1.den * f2.den;
    return Fraction(num, den);
}
Fraction operator-(Fraction const& f1, Fraction const& f2) {
    int num = f1.num * f2.den + (-f2.num) * f1.den,
        den = f1.den * f2.den;
    return Fraction(num, den);
}
Fraction operator*(Fraction const& f1, Fraction const& f2) {
    int num = f1.num * f2.num,
        den = f1.den * f2.den;
    return Fraction(num, den);
}
Fraction operator/(Fraction const& f1, Fraction const& f2) {
    int num = f1.num * f2.den,
        den = f1.den * f2.num;
    return Fraction(num, den);
}
Fraction& operator+=(Fraction& f1, Fraction const& f2) {
    f1 = f1 + f2;
    return f1;
}
Fraction& operator-=(Fraction& f1, Fraction const& f2) {
    f1 = f1 - f2;
    return f1;
}
Fraction& operator*=(Fraction& f1, Fraction const& f2) {
    f1 = f1 * f2;
    return f1;
}
Fraction& operator/=(Fraction& f1, Fraction const& f2) {
    f1 = f1 / f2;
    return f1;
}
Fraction operator-(Fraction const& f1) {
    return Fraction(-f1.num, f1.den);
}
bool operator<(Fraction const& f1, Fraction const& f2) {
    return (f1 - f2).num < 0;
}
bool operator==(Fraction const& f1, Fraction const& f2) {
    return (f1 - f2).num == 0;
}
bool operator>(Fraction const& f1, Fraction const& f2) {
    return (f1 - f2).num > 0;
}
Fraction& operator++(Fraction& f1) {
    f1.num += (f1.num >= 0 ? 1 : -1) * f1.den;
    return f1;
}
Fraction& operator++(Fraction& f1, int a) {
    Fraction* f2 = new Fraction((f1.num >= 0 ? 1 : -1) * f1.den, f1.den);
    f1.num += (f1.num >= 0 ? 1 : -1) * f1.den;
    return *f2;
}
Fraction& operator--(Fraction& f1) {
    f1.num -= (f1.num >= 0 ? 1 : -1) * f1.den;
    return f1;
}
Fraction& operator--(Fraction& f1, int a) {
    Fraction* f2 = new Fraction((f1.num >= 0 ? 1 : -1) * f1.den, f1.den);
    f1.num -= (f1.num >= 0 ? 1 : -1) * f1.den;
    return *f2;
}

int main() {
    Fraction a(2, 5), b(-1, 3, 2), c(20, -12);
    cout << "> a= " << a << " , b = " << b << " , c = " << c << endl;
    cout << ">2 + a*-b - c*b/2 = " << 2 + a * -b - c * b / 2 << "\n\n";

    a += b -= c + 2;
    cout << "> a += b -= c + 2: \n"
         << " a = " << a << " , b = " << b << " , c = " << c << "\n\n";

    Fraction d(0, 1);
    for (Fraction d(0, 1); d < 5; ++d) cout << d << " ";
    cout << "\n\n";

    cout << "> 輸入 分字/分母 形式： ";
    cin >> a;
    cout << "> 輸出： " << a << endl;
    return 0;
}