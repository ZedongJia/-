#include <cmath>
#include <iostream>

int dis[100001];

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    int times = std::pow(m, n);
    for (int i = 0; i < times; i++)
        scanf("%d", &dis[i]);
}