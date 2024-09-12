#include <algorithm>
#include <iostream>
int nums[1001];
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int x;
        scanf("%d", &x);
        nums[x] = 1;
    }
    int i = 0;
    for (; nums[i]; i++)
        ;
    printf("%d", i);
}