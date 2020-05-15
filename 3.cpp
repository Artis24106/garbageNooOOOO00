#include <algorithm>
#include <iostream>

using namespace std;

template <typename T>
T abs(T a) { return a > 0 ? a : -a; };

class Fraction {
   private:
    int a, b;
    int gcd(int a, int b) {
        if (b == 0) return a;
        if (a < b) swap(a, b);
        return gcd(b, a - b);
    }

   public:
    Fraction(int a, int b) {
        int g = gcd(a, b);
        Fraction::a = a / g;
        Fraction::b = b / g;
    }
    Fraction() { a = b = 1; }
    friend ostream& operator<<(ostream& out, Fraction const& f);
    friend istream& operator>>(istream& in, Fraction& f);
    friend Fraction operator+(Fraction const& f1, Fraction const& f2);
    friend Fraction operator-(Fraction const& f1, Fraction const& f2);
    friend Fraction operator*(Fraction const& f1, Fraction const& f2);
    friend Fraction operator/(Fraction const& f1, Fraction const& f2);
};

ostream& operator<<(ostream& out, Fraction const& f) { return out << f.a << "/" << f.b; }
istream& operator>>(istream& in, Fraction& f) {
    char c;
    int a, b;
    in >> a >> c >> b;
    f = Fraction(a, b);
    return in;
}
Fraction operator+(Fraction const& f1, Fraction const& f2) { return Fraction(f1.a * f2.b + f1.b * f2.a, f1.b * f2.b); }
Fraction operator-(Fraction const& f1, Fraction const& f2) { return Fraction(f1.a * f2.b - f1.b * f2.a, f1.b * f2.b); }
Fraction operator*(Fraction const& f1, Fraction const& f2) { return Fraction(f1.a * f2.a, f1.b * f2.b); }
Fraction operator/(Fraction const& f1, Fraction const& f2) { return Fraction(f1.a * f2.b, f1.b * f2.a); }

template <typename T>
class Math_Exp {
   private:
    T a, b;   // 兩個運算元
    char op;  // 運算子符號
   public:
    template <typename U>
    friend ostream& operator<<(ostream& out, Math_Exp<U> const& t);
    template <typename U>
    friend istream& operator>>(istream& in, Math_Exp<U>& t);
};

template <typename U>
ostream& operator<<(ostream& out, Math_Exp<U> const& t) {
    U ans;
    switch (t.op) {
        case '+':
            ans = t.a + t.b;
            break;
        case '-':
            ans = t.a - t.b;
            break;
        case '*':
            ans = t.a * t.b;
            break;
        case '/':
            ans = t.a / t.b;
            break;
    }
    return out << ans;
}

template <typename U>
istream& operator>>(istream& in, Math_Exp<U>& t) { return in >> t.a >> t.op >> t.b; }

int main() {
    Math_Exp<int> iexp;
    for (int i = 0; i < 4; ++i) {
        cout << "i> ";
        cin >> iexp;
        cout << "= " << iexp << endl;
    }

    Math_Exp<Fraction> fexp;
    for (int i = 0; i < 4; ++i) {
        cout << "f> ";
        cin >> fexp;
        cout << "= " << fexp << endl;
    }
    return 0;
}