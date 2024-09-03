#include <iostream>
#include <string.h>
#define S 1000
class Number
{
  public:
    int values[S];
    int length;
    Number()
    {
        for (int i = 0; i < S; i++)
            this->values[i] = 0;
        this->length = 0;
    }
    Number(const char *num)
    {
        this->length = strlen(num);
        for (int i = this->length - 1; i >= 0; i--)
            this->values[this->length - i - 1] = num[i] - 48;
    }
    Number(int num)
    {
        this->length = 0;
        while (num != 0)
        {
            this->values[this->length] = num % 10;
            this->length++;
            num /= 10;
        }
    }
    void print()
    {
        for (int i = this->length - 1; i >= 0; i--)
            std::cout << this->values[i];
        std::cout << std::endl;
    }
};

Number add(Number *number1, Number *number2)
{
    if (number1->length < number2->length)
        std::swap(number1, number2);
    Number result;
    for (int i = 0, j = 0; i < number1->length; i++)
    {
        result.values[i] = (result.values[i] + number1->values[i]);
        if (j < number2->length)
        {
            result.values[i] = result.values[i] + number2->values[j];
            j++;
        }
        result.values[i + 1] = result.values[i] / 10;
        result.values[i] = result.values[i] % 10;
        result.length++;
    }
    if (result.values[result.length] != 0)
        result.length++;
    return result;
}

Number mul(Number *number1, Number *number2)
{
    if (number1->length < number2->length)
        std::swap(number1, number2);
    Number result;
    for (int i = 0; i < number1->length; i++)
    {
        for (int j = 0; j < number2->length; j++)
        {
            result.values[i + j] = number1->values[i] * number2->values[j] + result.values[i + j];
            result.values[i + j + 1] += result.values[i + j] / 10;
            result.values[i + j] = result.values[i + j] % 10;
        }
        result.length = i + number2->length;
        while (result.values[result.length] != 0)
        {
            result.values[result.length + 1] += result.values[result.length] / 10;
            result.values[result.length] = result.values[result.length] % 10;
            result.length++;
        }
    }
    return result;
}
int main()
{
    int n;
    std::cin >> n;
    Number answer("0");
    Number delta("1");
    for (int i = 1; i <= n; i++)
    {
        Number tmp(i);
        delta = mul(&delta, &tmp);
        answer = add(&delta, &answer);
    }
    answer.print();
}