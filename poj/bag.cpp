#include <iostream>
using namespace std;
int main()
{
    int n, m;
    int w[3500];
    int d[3500];
    int earn[12881]{};
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> w[i] >> d[i];
    for (int i = 0; i < n; i++)
    {
        for (int j = m; j >= w[i]; j--)
        {
            earn[j] = max(earn[j], earn[j - w[i]] + d[i]);
        }
    }
    cout << earn[m];
}