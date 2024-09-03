#include <iostream>
#include <vector>
using namespace std;
typedef struct Decimal
{
    int nums[10000]{};
    int numLen = 0;
    int dotPos = 0;
} Decimal;

void print(Decimal &f)
{
    int lower = -1;
    for (int i = 0; i < f.numLen && i < f.dotPos; i++)
        if (f.nums[i] == 0)
            lower = i;
        else
            break;
    int higher = f.numLen;
    for (int i = f.numLen - 1; i >= f.dotPos; i--)
        if (f.nums[i] == 0)
            higher = i;
        else
            break;
    if (higher <= lower)
    {
        printf("0");
        return;
    }
    for (int i = higher - 1; i > lower; i--)
    {
        if (i + 1 == f.dotPos)
            printf(".");
        printf("%d", f.nums[i]);
    }
}

void assign(Decimal &f, string s)
{
    for (int i = s.length() - 1; i >= 0; i--)
    {

        if (s[i] == '.')
        {
            f.dotPos = s.length() - i - 1;
        }
        else
        {
            f.nums[f.numLen] = s[i] - 48;
            f.numLen++;
        }
    }
}

Decimal mul(Decimal f1, Decimal f2)
{
    Decimal rt;
    rt.dotPos = f1.dotPos + f2.dotPos;
    if (f1.numLen < f2.numLen)
        swap(f1, f2);
    for (int i = 0; i < f2.numLen; i++)
    {
        int rest = 0;
        for (int j = 0; j < f1.numLen; j++)
        {
            rest = rest + f2.nums[i] * f1.nums[j] + rt.nums[i + j];
            rt.nums[i + j] = rest % 10;
            rest /= 10;
        }
        rt.numLen = i + f1.numLen;
        while (rest)
        {
            rest = rest + rt.nums[rt.numLen];
            rt.nums[rt.numLen] = rest % 10;
            rest /= 10;
            rt.numLen++;
        }
    }
    return rt;
}

Decimal power(Decimal f, int pow)
{
    if (pow == 1)
        return f;
    Decimal l = power(f, pow / 2);
    Decimal r = power(f, pow - pow / 2);
    Decimal rt = mul(l, r);
    return rt;
}

int main()
{
    vector<pair<Decimal, int>> qs;
    string s;
    int n;
    while (cin >> s >> n)
    {
        // 0.0 < R < 99.999; 0 < n <= 25
        Decimal f;
        for (int i = s.length() - 1; i >= 0; i--)
        {
            if (s[i] == '.')
            {
                f.dotPos = s.length() - i - 1;
                if (i == 0)
                {
                    // . add 0
                    f.nums[f.numLen] = 0;
                    f.numLen++;
                }
            }
            else
            {
                f.nums[f.numLen] = s[i] - 48;
                f.numLen++;
            }
        }
        qs.push_back(make_pair(f, n));
    }
    vector<Decimal> ans;
    for (pair<Decimal, int> &q : qs)
    {
        Decimal f = power(q.first, q.second);
        ans.push_back(f);
    }
    for (int i = 0; i < ans.size(); i++)
    {
        print(ans[i]);
        printf("\n");
    }
}
