#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Score {
   private:
    wstring name, dept;
    vector<int> scores;
    int total;

   public:
    Score(wstring name, wstring dept, vector<int> scores) : name(name), dept(dept), scores(scores) {
        total = compute_total(scores);
    }
    Score(){};
    int compute_total(vector<int> const& temp) {
        double total = 0;
        total += temp[0] * 30;
        total += temp[1] * 100;
        total += temp[2] * 30;
        total += temp[3] * 100;
        total /= 100;
        total += 0.5;
        return total;
    }

    friend bool operator>(Score const& s1, Score const& s2) {
        if (s1.total > s2.total) return true;
        if (s1.total == s2.total && s1.scores[0] > s2.scores[0]) return true;
        if (s1.scores[0] == s2.scores[0] && s1.scores[1] > s2.scores[1]) return true;
        if (s1.scores[1] == s2.scores[1] && s1.scores[2] > s2.scores[2]) return true;
        if (s1.scores[2] == s2.scores[2] && s1.scores[3] > s2.scores[3]) return true;
        return false;
    }

    friend wistream& operator>>(wistream& in, Score& s) {
        int temp;
        vector<int> scores;
        wstring name, dept;
        in >> name;
        in >> dept;
        while (in >> temp) scores.push_back(temp);
        s = Score(name, dept, scores);
        return in;
    }

    friend wostream& operator<<(wostream& out, Score const& s) {
        out << s.name << " " << s.dept;
        for (int el : s.scores) out << setw(4) << setfill(L' ') << el;
        return out << L" --> " << s.total;
    }
};
int main() {
    vector<Score> all;

    wifstream wifs;
    wifs.imbue(locale("zh_TW.UTF-8"));
    wcout.imbue(locale("zh_TW.UTF-8"));
    wcin.imbue(locale("zh_TW.UTF-8"));

    wifs.open("./MA101.dat");
    wstring wstr;
    wstring name, dept;
    while (getline(wifs, wstr)) {
        if (wstr == L"" || wstr[0] == L'#' || wstr[0] == L'配') continue;
        wstring name, dept;
        Score s;
        wstringstream wss(wstr);
        wss >> s;
        all.push_back(s);
    }
    sort(all.begin(), all.end(), greater<Score>());
    for (int i = 0; i < all.size(); ++i) wcout << setw(2) << (i + 1) << L" " << all[i] << endl;

    return 0;
}