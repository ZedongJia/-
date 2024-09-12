#include <iostream>

int map[16][16];
bool isIn(int x, int y)
{
    return x >= 1 && x <= 15 && y >= 1 && y <= 15;
}
bool isOk(int x, int y, int val)
{
    return isIn(x, y) && map[x][y] == val;
}

bool check(int x, int y, int val)
{
    map[x][y] = val;
    int count = 1;
    for (int delta = -1;; delta--)
        if (isOk(x + delta, y + delta, val))
            count++;
        else
            break;
    for (int delta = 1;; delta++)
        if (isOk(x + delta, y + delta, val))
            count++;
        else
            break;
    if (count >= 5)
        return true;
    count = 1;
    for (int delta = -1;; delta--)
        if (isOk(x - delta, y + delta, val))
            count++;
        else
            break;
    for (int delta = 1;; delta++)
        if (isOk(x - delta, y + delta, val))
            count++;
        else
            break;
    if (count >= 5)
        return true;
    count = 1;
    for (int delta = -1;; delta--)
        if (isOk(x + delta, y, val))
            count++;
        else
            break;
    for (int delta = 1;; delta++)
        if (isOk(x + delta, y, val))
            count++;
        else
            break;
    if (count >= 5)
        return true;
    count = 1;
    for (int delta = -1;; delta--)
        if (isOk(x, y + delta, val))
            count++;
        else
            break;
    for (int delta = 1;; delta++)
        if (isOk(x, y + delta, val))
            count++;
        else
            break;
    if (count >= 5)
        return true;
    return false;
}

int main()
{
    for (int i = 1; i <= 15; i++)
        for (int j = 1; j <= 15; j++)
            map[i][j] = -1;
    int T;
    bool isEnd = false;
    std::string winner = "Tie";
    int round = -1;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        if (isEnd)
            continue;
        if (check(x, y, i % 2))
        {
            winner = i % 2 ? "A" : "B";
            round = i;
            isEnd = true;
        }
    }
    if (round == -1)
        printf("%s", winner.c_str());
    else
        printf("%s %d", winner.c_str(), round);
}