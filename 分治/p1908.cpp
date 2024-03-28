#include <iostream>
int n;
int arr[500001]{};
int tmp[500001]{};
long long solve(int left, int right)
{
    if (left >= right)
        return 0;
    int mid = (left + right) / 2;
    long long lans = solve(left, mid);
    long long rans = solve(mid + 1, right);
    int s1 = left;
    int s2 = mid + 1;
    int s3 = left;
    long long cnt = 0;
    while (s1 <= mid && s2 <= right)
    {
        if (arr[s1] <= arr[s2])
        {
            tmp[s3] = arr[s2];
            s2++;
        }
        else
        {
            tmp[s3] = arr[s1];
            s1++;
            cnt += (right - s2 + 1);
        }
        s3++;
    }
    while (s1 <= mid)
    {
        tmp[s3] = arr[s1];
        s3++;
        s1++;
    }
    while (s2 <= right)
    {
        tmp[s3] = arr[s2];
        s3++;
        s2++;
    }
    for (int i = left; i <= right; i++)
        arr[i] = tmp[i];
    return lans + rans + cnt;
}
int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    printf("%lld", solve(0, n - 1));
}