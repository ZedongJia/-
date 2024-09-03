#include <iostream>
#include <vector>
using namespace std;
int rec(const vector<int> &v, int left, int right)
{
    if (left + 1 == right)
        return v[left];
    int mid = (left + right) / 2;
    int lmax = rec(v, left, mid);
    int rmax = rec(v, mid, right);
    return max(lmax, rmax);
}
int maxv(const vector<int> &v)
{
    return rec(v, 0, v.size());
}

int main()
{
    vector<int> arr;
    int num = 0;
    while (cin >> num)
    {
        arr.push_back(num);
    }
    printf("%d", maxv(arr));
}