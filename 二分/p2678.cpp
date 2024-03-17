#include <algorithm>
#include <iostream>

int judge(int arr[], int gap, int n)
{
    int cnt = 0;
    int next = 1;
    int curr = 0;
    while (next <= n + 1)
    {
        if (arr[next] - arr[curr] < gap)
        {
            cnt++;
        }
        else
        {
            curr = next;
        }
        next++;
    }
    return cnt;
}

int main()
{
    int arr[60000]{};
    int maxGap, arrLen, totalMoveNum;
    std::cin >> maxGap >> arrLen >> totalMoveNum;
    for (int i = 1; i <= arrLen; i++)
        std::cin >> arr[i];
    arr[0] = 0;
    arr[arrLen + 1] = maxGap;
    std::sort(arr, arr + arrLen + 2);
    int ansGap = 0;
    int minGap = 1;
    while (minGap <= maxGap)
    {
        // printf("%d, %d\n", minGap, maxGap);
        int midGap = (maxGap - minGap) / 2 + minGap;
        int moveNum = judge(arr, midGap, arrLen);
        if (moveNum <= totalMoveNum)
        {
            // 等于m的情况下可能有更好的解决方案？即4是5块，那5也是5块则最优是5而不是4
            ansGap = midGap;
            minGap = midGap + 1;
        }
        else
        {
            maxGap = midGap - 1;
        }
    }
    printf("%d", ansGap);
}