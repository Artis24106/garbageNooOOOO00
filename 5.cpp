#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>

using namespace std;

bool compare(int a, int b) { return a > b; }
bool isValidDate(int month, int day) {
    // wcout << month << L" " << day << endl;
    switch (month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if (day >= 1 && day <= 31) return true;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            if (day >= 1 && day <= 30) return true;
            break;
        case 2:
            if (day >= 1 && day <= 29) return true;
            break;
    }
    return false;
}
struct Date {
    wstring name;

    deque<int> days;
    deque<int> notValidDays;

    friend bool operator>(Date const& c1, Date const& c2) {
        for (int i = 0; i < min(c1.days.size(), c2.days.size()); ++i) {
            if (c1.days[i] != c2.days[i]) return c1.days[i] < c2.days[i];
        }
        return c1.days.size() < c2.days.size();
    }
    friend wistream& operator>>(wistream& in, Date& c) {
        wstring temp;
        in >> c.name;
        int a, b;
        wchar_t wct;
        while (in >> a >> wct >> b) {
            if (isValidDate(a, b))
                c.days.push_back(a * 100 + b);
            else {
                c.notValidDays.push_back(a * 100 + b);
            }
        };
        sort(c.days.begin(), c.days.end(), compare);
        sort(c.notValidDays.begin(), c.notValidDays.end(), compare);
        return in;
    }
    friend wostream& operator<<(wostream& out, Date const& c) {
        out << c.name << L" [ ";
        for (auto el : c.days) out << el / 100 << L"/" << el % 100 << L" ";
        out << L"] ";
        if (!c.notValidDays.empty()) {
            out << L"{ ";
            for (auto el : c.notValidDays) out << el / 100 << L"/" << el % 100 << L" ";
            out << L"} ";
        }
        return out;
    }
    void clear() {
        days.clear();
        notValidDays.clear();
    }
};

int main() {
    setlocale(LC_ALL, "zh_TW.UTF-8");
    wifstream infile("./date.dat");
    infile.imbue(locale("zh_TW.UTF-8"));
    wcout.imbue(locale("zh_TW.UTF-8"));
    wstring line;
    Date x;

    priority_queue<Date, deque<Date>, greater<Date> > courses;

    while (getline(infile, line)) {
        wistringstream istr(line);
        istr >> x;
        courses.push(x);
        x.clear();
    }

    while (!courses.empty()) {
        wcout << courses.top() << endl;
        courses.pop();
    }

    return 0;
}