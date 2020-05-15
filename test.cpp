#include <iostream>
#include <string>

using namespace std;

int main() {
    setlocale(LC_ALL, "C");
    wstring foo = L"中文消失了";
    wcout << foo;

    return 0;
}