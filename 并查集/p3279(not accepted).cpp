#include <iostream>
#include <map>
int idx[100001]{};
char ans[100001]{};
std::map<int, char> hash;
int main()
{
    int n;
    std::cin >> n;
    idx[n] = '\0';
    for (int i = 0; i < n; i++)
    {
        idx[i] = i;
    }
    for (int i = 0; i < n; i++)
    {
        int dis;
        std::cin >> dis;
        for (int delta = 3; delta <= dis; delta += 2)
            idx[i + delta / 2] = idx[i - delta / 2];
    }
    for (int i = 0; i < n - 1; i++)
    {
        int dis;
        std::cin >> dis;
        for (int delta = 2; delta <= dis; delta += 2)
            idx[i + 1 + (delta / 2 - 1)] = idx[i - (delta / 2 - 1)];
    }
    int ch = 97;
    for (int i = 0; i < n; i++)
    {
        if (hash.find(idx[i]) == hash.end())
        {
            hash[idx[i]] = ch;
            ch++;
        }
        ans[i] = hash[idx[i]];
    }
    printf("%s", ans);
}