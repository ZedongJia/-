#include <iostream>
int type[1000];
char worker[1000][200];

int main()
{
    int n, m;
    std::cin >> n >> m;
    for (int i = 0; i < n; i++)
        std::cin >> type[i] >> worker[i];
    int idx = 0;
    for (int i = 0; i < m; i++)
    {
        int dir, step;
        std::cin >> dir >> step;
        if (type[idx] == 1)
        {
            if (dir == 0)
            {
                dir = 1;
            }
            else
            {
                dir = 0;
            }
        }
        if (dir == 0)
        {
            idx -= step;
        }
        else
        {
            idx += step;
        }
        while (idx < 0)
        {
            idx += n;
        }
        if (idx >= n)
        {
            idx = idx % n;
        }
    }
    printf("%s", worker[idx]);
}