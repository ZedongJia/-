#include <iostream>
#include <vector>

int fromSys, toSys;

int main()
{
    std::string str;
    std::vector<int> input;
    std::cin >> fromSys;
    std::cin >> str;
    std::cin >> toSys;
    for (char &ch : str)
        input.push_back(ch > '9' ? ch - 'A' + 10 : ch - '0');
    std::vector<int> ans;
    while (!input.empty())
    {
        int rest = 0;
        std::vector<int> tmp;
        for (int &number : input)
        {
            rest = rest * fromSys + number;
            tmp.push_back(rest / toSys);
            rest = rest % toSys;
        }
        while (!tmp.empty() && *tmp.begin() == 0)
        {
            tmp.erase(tmp.begin());
        }
        input = tmp;
        ans.push_back(rest);
    }
    while (!ans.empty() && *ans.rbegin() == 0)
    {
        ans.pop_back();
    }
    if (ans.empty())
        printf("0");
    else
        for (int i = ans.size() - 1; i >= 0; i--)
            printf("%c", ans[i] >= 10 ? ans[i] - 10 + 'A' : ans[i] + '0');
}