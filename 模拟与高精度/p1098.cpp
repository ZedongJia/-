#include <iostream>
#include <string>
using namespace std;
bool isNumber(char ch)
{
    return ch >= '0' && ch <= '9';
}
bool isChar(char ch)
{
    return ch >= 'a' && ch <= 'z';
}
string padding(char start, char end, int p1, int p2, int p3)
{
    if (end <= start || !(isNumber(start) && isNumber(end) || isChar(start) && isChar(end)))
        return "-";
    if (start + 1 == end)
        return "";
    string pad = "";
    int delta = 1;
    if (p3 == 2)
    {
        delta = -1;
        swap(start, end);
    }
    for (char ch = start + delta; ch != end; ch += delta)
    {
        char pdch = ch;
        if (!isNumber(ch))
        {
            if (p1 == 2)
                pdch = ch - 32;
            else
                pdch = ch;
        }
        if (p1 == 3)
            pdch = '*';
        for (int i = 0; i < p2; i++)
            pad += pdch;
    }
    return pad;
}
int main()
{
    int p1, p2, p3;
    string str;
    cin >> p1 >> p2 >> p3 >> str;
    cout << str[0];
    for (int i = 1; i < str.length() - 1; i++)
    {
        if (str[i] == '-')
            cout << padding(str[i - 1], str[i + 1], p1, p2, p3);
        else
            cout << str[i];
    }
    cout << str[str.length() - 1];
}