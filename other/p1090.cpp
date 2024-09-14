#include <algorithm>
#include <iostream>
#include <limits.h>
#include <vector>
std::vector<long long> vals;

int main()
{
    int n;
    scanf("%d", &n);
    while (n--)
    {
        long long number;
        scanf("%lld", &number);
        vals.push_back(number);
    }
    long long cost = 0;
    while (vals.size() != 1)
    {
        long long newVal = 0;
        // pick two
        std::vector<long long>::iterator fValIt = std::min_element(vals.begin(), vals.end());
        newVal += *fValIt;
        vals.erase(fValIt);
        std::vector<long long>::iterator sValIt = std::min_element(vals.begin(), vals.end());
        newVal += *sValIt;
        vals.erase(sValIt);
        vals.push_back(newVal);
        cost += newVal;
    }
    printf("%lld", cost);
}