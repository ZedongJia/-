#include <algorithm>
#include <iostream>
#include <string>
using namespace std;
int main()
{
    string s = "abcdefghijk";
    // 翻转 d 到 g
    printf("%s\n", s.c_str());
    reverse(&s[3], &s[8]);
    printf("%s", s.c_str());
}