#include <iostream>
#include <string>
using namespace std;
string str;
string pattern;
int next_arr[1000000];

void getNext()
{
    int pre = 0, curr = 1;
    next_arr[0] = -1;
    next_arr[1] = 0;
    while (curr < pattern.length())
    {
        if (pre == -1 || pattern[curr] == pattern[pre])
        {
            curr++;
            pre++;
            next_arr[curr] = pre; // curr -> pre start
        }
        else
        {
            pre = next_arr[pre];
        }
    }
}
int main()
{
    cin >> str;
    cin >> pattern;
    getNext();
    int i = 0;
    int j = 0;
    while (i < str.length() && j < pattern.length())
    {
        if (j == -1 || str[i] == pattern[j])
        {
            i++;
            j++;
        }
        else
        {
            i++;
            j = next_arr[j];
        }
    }
    if (j >= pattern.length())
    {
        printf("%d", i - j);
    }
    else
    {
        printf("%d", -1);
    }
}