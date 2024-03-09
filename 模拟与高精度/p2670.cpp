#include <iostream>
int main()
{
    char arr[102][102];
    int ans[102][102]{};
    int row = 0;
    int col = 0;
    std::cin >> row >> col;
    for (int i = 1; i <= row; i++)
    {
        for (int j = 1; j <= col; j++)
        {
            std::cin >> arr[i][j];
        }
    }
    for (int i = 0; i <= row + 1; i++)
    {
        for (int j = 0; j <= col + 1; j++)
        {
            ans[i][j] = 0;
        }
    }
    for (int i = 1; i <= row; i++)
    {
        for (int j = 1; j <= col; j++)
        {
            if (arr[i][j] == '*')
            {
                if (ans[i - 1][j - 1] != -1)
                    ans[i - 1][j - 1]++;
                if (ans[i - 1][j] != -1)
                    ans[i - 1][j]++;
                if (ans[i - 1][j + 1] != -1)
                    ans[i - 1][j + 1]++;

                if (ans[i][j - 1] != -1)
                    ans[i][j - 1]++;
                ans[i][j] = -1;
                if (ans[i][j + 1] != -1)
                    ans[i][j + 1]++;

                if (ans[i + 1][j - 1] != -1)
                    ans[i + 1][j - 1]++;
                if (ans[i + 1][j] != -1)
                    ans[i + 1][j]++;
                if (ans[i + 1][j + 1] != -1)
                    ans[i + 1][j + 1]++;
            }
        }
    }
    for (int i = 1; i <= row; i++)
    {
        for (int j = 1; j <= col; j++)
        {
            if (ans[i][j] != -1)
            {
                std::cout << ans[i][j];
            } else {
                std::cout << "*";
            }
        }
        std::cout << std::endl;
    }
}