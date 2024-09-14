#include <iostream>

int main()
{
    std::string str;
    std::cin >> str;
    int k;
    std::cin >> k;
    int tmpk = k;
    int startIndex = 0;
    std::string newStr;
    while (startIndex < str.length())
    {
        int newIndex = startIndex;
        for (int i = startIndex + 1; i <= startIndex + tmpk; i++)
        {
            if (str[newIndex] > str[i])
                newIndex = i;
        }
        newStr += str[newIndex];
        tmpk -= newIndex - startIndex;
        startIndex = newIndex + 1;
        if (newStr.length() + k == str.length())
            break;
    }
    while (newStr.size() != 1 && newStr[0] == '0')
    {
        newStr.erase(newStr.begin());
    }
    std::cout << newStr;
}