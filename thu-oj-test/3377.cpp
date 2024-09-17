#include <cmath>
#include <iostream>

int main()
{
    int n;
    scanf("%d", &n);
    while (n--)
    {
        int number, count = 0;
        scanf("%d", &number);
        int bdr = std::sqrt(number);
        if (number == bdr * bdr)
            count--;
        for (int i = 1; i <= bdr; i++)
            if (number % i == 0)
                count += 2;
        printf("%d\n", count);
    }
}