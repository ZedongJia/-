#include <iostream>
#include <map>
using namespace std;
map<int, int> cnt;

int main()
{
    int n;
    int maxCount = -1;
    int maxNumber = -1;
    cin >> n;
    while (n--)
    {
        int number;
        cin >> number;
        if (cnt.find(number) == cnt.end())
        {
            cnt[number] = 0;
        }
        cnt[number]++;
        if ((cnt[number] > maxCount) | (cnt[number] == maxCount && number > maxNumber))
        {
            maxCount = cnt[number];
            maxNumber = number;
        }
    }
    printf("%d", maxNumber);
}