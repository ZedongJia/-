#include <algorithm>
#pragma GCC optimize(2)
#include <cstring>
#include <map>
#include <stdio.h>

using namespace std;
map<int, int> cnt;
int heights[100001];
int temp[100001];

bool isOk(int len, int m, int k)
{
    memcpy(temp, heights, sizeof(int) * len);
    sort(temp, temp + len);
    for (int i = m - 1; i < len; i++)
    {
        if ((temp[i] - temp[i - m + 1]) <= k)
            return true;
    }
    return false;
}

int main()
{
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &heights[i]);
    }
    int left = m, right = n;
    if (!isOk(n, m, k))
    {
        printf("impossible");
        return 0;
    }
    while (left < right)
    {
        int mid = (left + right) / 2;
        if (isOk(mid, m, k))
        {
            // may be at left
            right = mid;
        }
        else
        {
            // may be at right
            left = mid + 1;
        }
    }
    printf("%d", left);
    return 0;
}