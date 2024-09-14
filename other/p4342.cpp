#include <algorithm>
#include <iostream>

int maxScoreDp[50][50];
int minScoreDp[50][50];
int vals[50];
char ops[50];
int n;

int post(int index, int dt)
{
    return (index + dt) % n;
}

int eval(int x, int y, char op)
{
    return op == 't' ? x + y : x * y;
}

int main()
{
    std::cin >> n;
    for (int i = 0; i < n; i++)
        std::cin >> ops[i] >> vals[i];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            maxScoreDp[i][j] = INT32_MIN;
            minScoreDp[i][j] = INT32_MAX;
        }
    for (int i = 0; i < n; i++)
        maxScoreDp[i][i] = minScoreDp[i][i] = vals[i];
    for (int l = 2; l <= n; l++)
    {
        int start = 0, end = 0;
        do
        {
            end = post(start, l - 1);
            for (int k = start; k != end; k = post(k, 1))
            {
                maxScoreDp[start][end] = std::max(
                    maxScoreDp[start][end], eval(maxScoreDp[start][k], maxScoreDp[post(k, 1)][end], ops[post(k, 1)]));
                maxScoreDp[start][end] = std::max(
                    maxScoreDp[start][end], eval(minScoreDp[start][k], minScoreDp[post(k, 1)][end], ops[post(k, 1)]));
                minScoreDp[start][end] = std::min(
                    minScoreDp[start][end], eval(maxScoreDp[start][k], minScoreDp[post(k, 1)][end], ops[post(k, 1)]));
                minScoreDp[start][end] = std::min(
                    minScoreDp[start][end], eval(minScoreDp[start][k], maxScoreDp[post(k, 1)][end], ops[post(k, 1)]));
            }
            printf("<%d,%d>:%d\n", start, end, maxScoreDp[start][end]);
            start = post(start, 1);
        } while (start != 0);
    }
    int maxScore = INT32_MIN;
    for (int i = 0; i < n; i++)
        maxScore = std::max(maxScore, maxScoreDp[i][post(i, n - 1)]);
    printf("%d\n", maxScore);
    for (int i = 0; i < n; i++)
    {
        if (maxScoreDp[i][post(i, n - 1)] == maxScore)
            printf("%d ", i + 1);
    }
}