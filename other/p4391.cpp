#include <iostream>
std::string str;
int next[1000001];
void setNext()
{
    next[0] = -1;
    int j = 0, k = -1;
    while (j < str.length())
    {
        if (k == -1 || str[j] == str[k])
        {
            next[++j] = ++k;
        }
        else
        {
            k = next[k];
        }
    }
}
int main()
{
    int l;
    std::cin >> l;
    std::cin >> str;
    setNext();
    std::cout << str.length() - next[str.length()];
}