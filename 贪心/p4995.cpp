#include <algorithm>
#include <iostream>

using namespace std;
int h[301]{};
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> h[i];
    sort(h, h + n);
    long long ans = 0;
    ans += h[n - 1] * h[n - 1];
    for (int i = 0; i < n / 2; i++)
    {
        ans += (h[n - 1 - i] - h[i]) * (h[n - 1 - i] - h[i]);
        ans += (h[n - 2 - i] - h[i]) * (h[n - 2 - i] - h[i]);
    }
    printf("%lld", ans);
}