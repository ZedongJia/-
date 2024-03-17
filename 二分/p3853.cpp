#include <iostream>

int judge(int arr[], int l, int n)
{
    int cnt = 0;
    for (int i = 1; i < n; i++)
    {
        cnt += (arr[i] - arr[i - 1] - 1) / l;
    }
    return cnt;
}

int main()
{
    int arr[200001];
    int maxL, n, k;
    std::cin >> maxL >> n >> k;
    for (int i = 0; i < n; i++)
        std::cin >> arr[i];
    int minL = 1;
    int ansL = 0;
    while (minL <= maxL)
    {
        int midL = (maxL - minL) / 2 + minL;
        if (judge(arr, midL, n) <= k)
        {
            ansL = midL;
            maxL = midL - 1;
        }
        else
        {
            minL = midL + 1;
        }
    }
    printf("%d", ansL);
}