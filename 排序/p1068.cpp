#include <iostream>

typedef struct P
{
    int id;
    int score;
} P;

int main()
{
    int n, m;
    std::cin >> n >> m;
    P **parr = new P *[n];
    for (int i = 0; i < n; i++)
    {
        P *p = new P();
        std::cin >> p->id >> p->score;
        int j = i;
        for (; j >= 1 && (parr[j - 1]->score < p->score || (parr[j - 1]->score == p->score && parr[j - 1]->id > p->id));
             j--)
        {
            parr[j] = parr[j - 1];
        }
        parr[j] = p;
    }
    int ln = m * 1.5;
    int lnScore = 0;
    for (int i = 0; i < n; i++)
    {
        if (i == ln - 1)
        {
            lnScore = parr[i]->score;
        }
        if (i >= ln && parr[i]->score != lnScore)
        {
            break;
        }
        if (i >= ln)
        {
            ln++;
        }
    }
    printf("%d %d\n", lnScore, ln);
    for (int i = 0; i < n; i++)
    {
        if (i >= ln)
        {
            break;
        }
        printf("%d %d\n", parr[i]->id, parr[i]->score);
    }
}