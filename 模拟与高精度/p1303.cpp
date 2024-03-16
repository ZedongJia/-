#include <iostream>
#include <string.h>
#define NUM_SIZE 10000
void mul(char *result, char *n1, char *n2)
{
    int arr[NUM_SIZE]{};
    int len1 = strlen(n1);
    int len2 = strlen(n2);
    for (int i = len1 - 1; i >= 0; i--)
    {
        for (int j = len2 - 1; j >= 0; j--)
        {
            int ridx = len1 + len2 - (i + 1) - (j + 1);
            int tmp = (n1[i] - 48) * (n2[j] - 48) + arr[ridx];
            arr[ridx + 1] = int(tmp / 10) + arr[ridx + 1];
            arr[ridx] = tmp % 10;
        }
    }
    int j = 0;
    int i = len1 + len2;
    while (arr[i] == 0)
    {
        i--;
    }
    while (i >= 0)
    {
        result[j] = arr[i] + 48;
        i--;
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
    mul(tmp, num1, num2);
    printf("%s", tmp);
}