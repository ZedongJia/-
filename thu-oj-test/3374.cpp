#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    int m, n;
    cin >> m >> n;
    string numStr;
    cin >> numStr;
    int num10 = 0;
    vector<int> number;
    for (int i = numStr.length() - 1; i >= 0; i--)
    {
        if (numStr[i] >= 'A')
            number.push_back(numStr[i] - 'A' + 10);
        else
            number.push_back(numStr[i] - 48);
    }
    reverse(number.begin(), number.end());
    string out = "";
    while (!number.empty())
    {
        // divide
        vector<int> tmp;
        int r = 0;
        for (int i = 0; i < number.size(); i++)
        {
            number[i] = r * m + number[i];
            tmp.push_back(number[i] / n);
            r = number[i] % n;
        }
        while (!tmp.empty() && *tmp.begin() == 0)
            tmp.erase(tmp.begin());
        number = tmp;
        if (r >= 10)
            out.insert(out.begin(), 'a' + r - 10);
        else
            out.insert(out.begin(), r + 48);
    }
    printf("%s", out.c_str());
}