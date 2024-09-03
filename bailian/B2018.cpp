#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<string> ss(n);
    for (int i = 0; i < n; i++)
    {
        cin >> ss[i];
    }
    vector<string> ans;
    for (int i = 0; i < n; i++)
    {
        bool find = false;
        string &str = ss[i];
        for (int l = str.length(); l >= 1; l--)
        {
            for (int sl = 0; sl <= str.length() - l; sl++)
            {
                int sr = sl + l - 1;
                int pl = sl, pr = sr;
                while (pl < pr && str[pl] == str[pr])
                {
                    pl++;
                    pr--;
                }
                if (pl >= pr)
                {
                    ans.push_back(str.substr(sl, l));
                    find = true;
                    break;
                }
            }
            if (find)
                break;
        }
    }
    for (int i = 0; i < ans.size() - 1; i++)
        printf("%s\n", ans[i].c_str());
    printf("%s", ans.rbegin()->c_str());
}