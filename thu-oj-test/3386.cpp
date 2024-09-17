#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    int n;
    while (std::cin >> n)
    {
        std::vector<int> tmp;
        int num;
        while (n--)
        {
            std::cin >> num;
            tmp.push_back(num);
        }
        printf("%d %d\n", *std::max_element(tmp.begin(), tmp.end()), *std::min_element(tmp.begin(), tmp.end()));
    }
}