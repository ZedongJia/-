#include <iostream>
#include <vector>
using namespace std;
long long matrix[102][102];
int n, m;
typedef struct Answer
{
    int i;
    int j;
    int val;
} Answer;
vector<Answer> answers;

void bfs(int i, int j)
{
    if (i < 1 || i > n || j < 1 || j > m)
        return;
}
int main()
{
    cin >> n >> m;
    for (int i = 0; i <= n + 1; i++)
    {
        if (i == 0 || i == n + 1)
        {
            for (int j = 0; j <= m + 1; j++)
                matrix[i][j] = 0;
        }
        for (int j = 0; j <= m + 1; j++)
        {
            if (j == 0 || j == m + 1)
                matrix[i][j] = 0;
            else
                cin >> matrix[i][j];
        }
    }
}