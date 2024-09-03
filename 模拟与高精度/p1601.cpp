#include <iostream>
#include <string.h>
class Number
{
    char values[20];
    int length;

  public:
    Number(char *str)
    {
        set(str);
    }
    Number()
    {
        this->length = 0;
        for (int i = 0; i < 20; i++)
            this->values[i] = '0';
    }
    void set(char *str)
    {
        this->length = strlen(str);
        for (int i = this->length - 1; i >= 0; i--)
            this->values[this->length - i - 1] = str[i];
    }
    Number operator+(const Number &n) const
    {
        int i = 0;
        int j = 0;
        int up = 0;
        Number result;
        while (i < this->length && j < n.length)
        {
            up = (this->values[i] - 48) + (n.values[j] - 48) + up;
            result.values[i] = up % 10 + 48;
            up /= 10;
            i++;
            j++;
            result.length++;
        }
        while (i < this->length)
        {
            up = (this->values[i] - 48) + up;
            result.values[i] = up % 10 + 48;
            up /= 10;
            i++;
            result.length++;
        }

        while (j < n.length)
        {
            up = (n.values[j] - 48) + up;
            result.values[j] = up % 10 + 48;
            up /= 10;
            j++;
            result.length++;
        }
        if (up != 0)
        {
            result.values[result.length] = up + 48;
            result.length++;
        }
        return result;
    }
    void print()
    {
        for (int i = this->length - 1; i >= 0; i--)
            std::cout << this->values[i];
    }
};
int main()
{

    char tmp[20];
    std::cin >> tmp;
    Number n1(tmp);
    std::cin >> tmp;
    Number n2(tmp);
    (n1 + n2).print();
}