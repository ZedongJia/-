#include <iostream>
#include <set>
char map[12][12];

typedef struct Obj
{
    int r;
    int c;
    int d;
} Obj;
int getTr(Obj obj1, Obj obj2)
{
    return obj1.r + obj1.c * 12 + obj1.d * 12 * 12 + obj2.r * 12 * 12 * 12 + obj2.c * 12 * 12 * 12 * 12 +
           obj2.d * 12 * 12 * 12 * 12 * 12;
}
/*
    up: 0, down: 1, left: 2, right: 3
*/
void move(Obj &obj)
{
    if (obj.d == 0)
    {
        if (map[obj.r - 1][obj.c] != '*')
        {
            obj.r--;
        }
        else
        {
            obj.d = 3;
        }
    }
    else if (obj.d == 1)
    {
        if (map[obj.r + 1][obj.c] != '*')
        {
            obj.r++;
        }
        else
        {
            obj.d = 2;
        }
    }
    else if (obj.d == 2)
    {
        if (map[obj.r][obj.c - 1] != '*')
        {
            obj.c--;
        }
        else
        {
            obj.d = 0;
        }
    }
    else
    {
        if (map[obj.r][obj.c + 1] != '*')
        {
            obj.c++;
        }
        else
        {
            obj.d = 1;
        }
    }
}

int main()
{
    Obj F = {0, 0, 0};
    Obj C = {0, 0, 0};
    std::set<int> trs;
    for (int i = 0; i <= 11; i++)
    {
        map[0][i] = '*';
        map[11][i] = '*';
        map[i][0] = '*';
        map[i][11] = '*';
    }

    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= 10; j++)
        {
            std::cin >> map[i][j];
            if (map[i][j] == 'F')
            {
                F.r = i;
                F.c = j;
            }
            else if (map[i][j] == 'C')
            {
                C.r = i;
                C.c = j;
            }
        }
    }
    int minu = 0;
    while (!(F.r == C.r && F.c == C.c))
    {
        move(F);
        move(C);
        int tr = getTr(F, C);
        if (trs.count(tr))
        {
            minu = 0;
            break;
        } else {
            trs.insert(tr);
        }
        minu++;
    }
    printf("%d", minu);
}