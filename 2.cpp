#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    string str, temp;
    double d = 0;
    while (cout << "輸入> " && getline(cin, str)) {
        double ans = 0;
        stringstream ss(str);
        cout << "輸出> sum of ";
        while (ss >> temp) {
            stringstream ss2(temp);
            ss2 >> d;
            if (ss2.fail() || !ss2.eof()) {
                continue;
            }
            ans += d;
            cout << temp << " ";
        }
        cout << "= " << ans << endl;
    }
    return 0;
}