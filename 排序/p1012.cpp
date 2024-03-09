#include <iostream>
#include <string.h>
char *nums[20];
bool cmp(char *num1, char *num2)
{
    char nnum1[22];
    char nnum2[22];
    sprintf(nnum1, "%s%s", num1, num2);
    sprintf(nnum2, "%s%s", num2, num1);
    return strcmp(nnum1, nnum2) > 0;
}
int main()
{
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        char *num = new char[11];
        std::cin >> num;
        int j = i;
        for (; j >= 1 && cmp(num, nums[j - 1]); j--)
        {
            nums[j] = nums[j - 1];
        }
        nums[j] = num;
    }
    for (int i = 0; i < n; i++)
    {
        printf("%s", nums[i]);
        delete nums[i];
    }
}