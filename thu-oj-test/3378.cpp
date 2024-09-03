#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;
map<string, int> ipLoc;

int main()
{
    int n, m;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string ip;
        cin >> ip;
        ipLoc[ip] = i;
    }
    cin >> m;
    vector<int> vis(n, 0);
    int rest = n;
    int count = 0;
    for (int i = 0; i < m; i++)
    {
        string ip;
        cin >> ip;
        if (ipLoc.find(ip) == ipLoc.end() || vis[ipLoc[ip]])
        {
            // skip
            continue;
        }
        // we found
        vis[ipLoc[ip]]++;
        // rest down
        rest--;
        if (rest == 0)
        {
            // must switch
            count++;
            rest = n - 1;
            vis = vector<int>(n, 0);
            vis[ipLoc[ip]]++;
        }
    }
    if (ipLoc.size() <= 1)
    {
        printf("-1");
    }
    else
    {
        printf("%d", count);
    }
}