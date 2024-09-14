#include <iostream>
std::string str;

int count1(int preChar, int pos)
{
    if (pos == str.length() - 1)
        return 0;
    int result = 0;
    for (int ch = preChar + 1; ch <= 'z'; ch++)
        result += count1(ch, pos + 1) + 1;
    return result;
}
int count2(int preChar, int pos, int align)
{
    if (pos == str.length() - 1)
    {
        if (align)
            return str[pos] - preChar;
        else
            return 'z' - preChar;
    }
    int result = 0;
    int endChar = 'z';
    if ((pos == 0 || preChar == str[pos - 1]) && align)
    {
        endChar = str[pos];
        align = true;
    }
    else
    {
        align = false;
    }
    for (int ch = preChar + 1; ch <= endChar; ch++)
    {
        result += count2(ch, pos + 1, align && ch == str[pos]);
    }
    return result;
}

int main()
{
    std::cin >> str;
    for (int i = 0; i < str.length() - 1; i++)
        if (str[i] >= str[i + 1])
        {
            std::cout << 0;
            return 0;
        }
    std::cout << count1('a' - 1, 0) + count2('a' - 1, 0, true);
}