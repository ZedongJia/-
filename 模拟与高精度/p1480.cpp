#include <iostream>
#include <string.h>
#define NUM_SIZE 10000
void div(char *result, char *n1, char *n2)
{
    int arr[NUM_SIZE]{};
    int len1 = strlen(n1);
    long long _div = std::stoll(n2);
    long long rest = 0;
    for (int i = 0; i < len1; i++)
    {
        long long tmp = rest * 10 + n1[i] - 48;
        arr[i] = tmp / _div;
        rest = tmp % _div;
    }
    int i = 0;
    int j = 0;
    while (arr[i] == 0)
    {
        i++;
    }
    while (i < len1)
    {
        result[j] = arr[i] + 48;
        i++;
        j++;
    }
    if (j == 0)
    {
        result[j] = 48;
        j++;
    }
    result[j] = '\0';
}
int main()
{
    char num1[NUM_SIZE];
    char num2[NUM_SIZE];
    char tmp[NUM_SIZE];
    std::cin >> num1 >> num2;
    div(tmp, num1, num2);
    printf("%s", tmp);
}