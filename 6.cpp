#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <vector>

using namespace std;

int ch2int(wchar_t wct) { return wct - L'A'; }
wchar_t int2ch(int i) { return i + L'A'; }
bool compare(int& i1, int& i2) {
    return i1 < i2;
}

class WeekNode {
   private:
    wchar_t name;
    vector<int> data;

   public:
    WeekNode(wchar_t name, vector<int> data) : name(name), data(data) {
        sort(WeekNode::data.begin(), WeekNode::data.end(), compare);
    }
    friend bool operator<(WeekNode const& wn1, WeekNode const& wn2) {
        if (wn1.data.size() != wn2.data.size()) return wn1.data.size() < wn2.data.size();
        for (int i = 0; i < wn1.data.size(); ++i) {
            if (wn1.data[i] != wn2.data[i]) return wn1.data[i] > wn2.data[i];
        }
        return false;
    }
    friend wostream& operator<<(wostream& wout, WeekNode const& wn) {
        wout << wn.name << L" [" << setw(2) << wn.data.size() << L"]";
        for (auto el : wn.data) {
            wout << L" " << int2ch(el);
        }
        return wout;
    }
};

map<wchar_t, vector<int> > week;
priority_queue<WeekNode> answer;

int main() {
    setlocale(LC_ALL, "zh_TW.UTF-8");
    wifstream wifs("./wkdates.dat");
    wifs.imbue(locale("zh_TW.UTF-8"));
    wcout.imbue(locale("zh_TW.UTF-8"));

    wstring ws;
    wchar_t wct, garbage;
    while (getline(wifs, ws)) {
        if (ws.back() == L'\r') ws.resize(ws.size() - 1);
        vector<int> temp;
        wstringstream wss(ws);
        wss >> wct >> garbage >> ws;
        for (auto el : ws) {
            week[el].push_back(ch2int(wct));
        }
    }

    for (auto el : week) {
        answer.push(WeekNode(el.first, el.second));
    }

    for (; !answer.empty(); answer.pop()) {
        wcout << answer.top() << endl;
    }

    return 0;
}