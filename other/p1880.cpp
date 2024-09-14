#include <iostream>
int n;
int nums[100];
int maxDp[100][100];
int minDp[100][100];

int post(int index, int dt = 1)
{
    return (index + dt) % n;
}

int main()
{
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            maxDp[i][j] = INT32_MIN;
            minDp[i][j] = INT32_MAX;
        }
    for (int i = 0; i < n; i++)
        maxDp[i][i] = minDp[i][i] = 0;
    for (int l = 2; l <= n; l++)
    {
        int start = 0, end = post(start, l - 1);
        int score = 0;
        for (int i = start; i != end; i = post(i))
            score += nums[i];
        do
        {
            end = post(start, l - 1);
            score += nums[end];
            for (int k = start; k != end; k = post(k))
            {
                maxDp[start][end] = std::max(maxDp[start][end], maxDp[start][k] + maxDp[post(k)][end] + score);
                minDp[start][end] = std::min(minDp[start][end], minDp[start][k] + minDp[post(k)][end] + score);
            }
            printf("<%d,%d>:%d\n", start, end, minDp[start][end]);
            score -= nums[start];
            start = post(start);
        } while (start != 0);
    }
    int maxAns = INT32_MIN, minAns = INT32_MAX;
    for (int i = 0; i < n; i++)
    {
        maxAns = std::max(maxAns, maxDp[i][post(i, n - 1)]);
        minAns = std::min(minAns, minDp[i][post(i, n - 1)]);
    }
    printf("%d\n%d", minAns, maxAns);
}