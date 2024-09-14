#include <iostream>

int depth[100000];

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &depth[i]);
    int day = 0;
    int preP = 0;
    while (true)
    {
        int p = preP;
        while (p < n && !depth[p])
            p++;
        if (p >= n)
            break;
        preP = p;
        while (p < n && depth[p])
            depth[p]--, p++;
        day++;
    }
    printf("%d", day);
}