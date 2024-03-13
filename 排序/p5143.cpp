#include <cmath>
#include <iostream>


typedef struct Pos
{
    int x;
    int y;
    int z;
} Pos;

double getDis(Pos *p1, Pos *p2)
{
    return sqrt(pow((p1->x - p2->x), 2) + pow((p1->y - p2->y), 2) + pow((p1->z - p2->z), 2));
}

int main()
{
    int n;
    std::cin >> n;
    Pos **arr = new Pos *[n];
    for (int i = 0; i < n; i++)
    {
        Pos *pos = new Pos();
        std::cin >> pos->x >> pos->y >> pos->z;
        int j = i;
        for (; j >= 1 && arr[j - 1]->z > pos->z; j--)
        {
            arr[j] = arr[j - 1];
        }
        arr[j] = pos;
    }
    double dis = 0;
    for (int i = 1; i < n; i++)
    {
        dis += getDis(arr[i], arr[i - 1]);
    }
    for (int i = 0; i < n; i++)
    {
        delete arr[i];
    }
    delete[] arr;
    printf("%.3lf", dis);
}