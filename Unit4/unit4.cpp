#include <iostream>

using namespace std;

template <typename T>
T abs(T a) { return a > 0 ? a : -a; }

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
    Fraction() {
        Fraction(0);
    }
    double val() const { return (double)num / (double)den; }
    friend ostream& operator<<(ostream& o, Fraction const& f);
    friend Fraction operator+(Fraction const& f1, Fraction const& f2);
    friend Fraction operator-(Fraction const& f1, Fraction const& f2);
    friend Fraction operator*(Fraction const& f1, Fraction const& f2);
    friend Fraction operator/(Fraction const& f1, Fraction const& f2);
    friend Fraction operator-(Fraction const& f1);
    friend bool operator>(Fraction const& f1, Fraction const& f2);
    friend bool operator>(Fraction const& f1, double const& d2);
    void debug() { cout << "num: " << num << ", den: " << den << endl; }
};

Fraction f(const Fraction& x) { return x * x - Fraction(3, 4); }
Fraction df(const Fraction& x) { return 2 * x; }
ostream& operator<<(ostream& o, Fraction const& f) { return o << f.num << "/" << f.den; }
Fraction operator+(Fraction const& f1, Fraction const& f2) { return Fraction(f1.num * f2.den + f2.num * f1.den, f1.den * f2.den); }
Fraction operator-(Fraction const& f1, Fraction const& f2) { return Fraction(f1.num * f2.den + (-f2.num) * f1.den, f1.den * f2.den); }
Fraction operator*(Fraction const& f1, Fraction const& f2) { return Fraction(f1.num * f2.num, f1.den * f2.den); }
Fraction operator/(Fraction const& f1, Fraction const& f2) { return Fraction(f1.num * f2.den, f1.den * f2.num); }
Fraction operator-(Fraction const& f1) { return Fraction(-f1.num, f1.den); }
bool operator>(Fraction const& f1, Fraction const& f2) { return (f1 - f2).val() > 0; }
bool operator>(Fraction const& f1, double const& d2) { return f1.val() - d2 > 0; }

template <typename T>
T Newton_Iteration(T x0) {
    T x1, dx = 1;
    while (dx > (double)0.0001) {
        x1 = x0 - f(x0) / df(x0);
        dx = abs(x1 - x0);
        x0 = x1;
    }
    return x0;
}

int main() {
    Fraction x(1);

    Fraction sol = Newton_Iteration<Fraction>(x);

    cout << sol << " = " << sol.val() << endl;
    return 0;
}