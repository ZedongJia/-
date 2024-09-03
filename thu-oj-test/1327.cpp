#pragma GCC optimize(2)
#include <algorithm>
#include <cmath>
#include <stdio.h>
using namespace std;
#define N 50010
int blockSize = 0;
typedef struct Query
{
    int id;
    int leftDay;
    int rightDay;
    bool operator<(const Query &qOther) const
    {
        int q1BlockId = this->leftDay / blockSize;
        int q2BlockId = qOther.leftDay / blockSize;
        if (this->leftDay / blockSize != qOther.leftDay / blockSize)
        {
            return this->leftDay < qOther.leftDay;
        }
        if ((this->leftDay / blockSize) % 2)
        {
            return this->rightDay < qOther.rightDay;
        }
        return this->rightDay > qOther.rightDay;
    }
} Query;
typedef struct Change
{
    int leftStudentId;
    int rightStudentId;
} Change;
typedef struct Answer
{
    int count;
    int id;
} Answer;

typedef struct Node
{
    int tag;
    Answer answer;
} Node;

Node nodes[N << 2];
Change changes[N];
Query querys[N];
Answer answers[N];

inline void down(int nodeId)
{
    if (nodes[nodeId].tag)
    {
        int lChildId = nodeId << 1;
        int rChildId = nodeId << 1 | 1;
        nodes[rChildId].tag += nodes[nodeId].tag;
        nodes[lChildId].tag += nodes[nodeId].tag;
        nodes[lChildId].answer.count += nodes[nodeId].tag;
        nodes[rChildId].answer.count += nodes[nodeId].tag;
        nodes[nodeId].tag = 0;
    }
}

inline void up(int nodeId)
{
    int lChildId = nodeId << 1;
    int rChildId = nodeId << 1 | 1;
    if (nodes[lChildId].answer.count >= nodes[rChildId].answer.count)
    {
        nodes[nodeId].answer = nodes[lChildId].answer;
    }
    else
    {
        nodes[nodeId].answer = nodes[rChildId].answer;
    }
}

void build(int nodeId, int left, int right)
{
    if (left == right)
    {
        nodes[nodeId] = {0, {0, left}};
        return;
    }
    int mid = (left + right) >> 1;
    build(nodeId << 1, left, mid);
    build(nodeId << 1 | 1, mid + 1, right);
    up(nodeId);
}

void modify(int nodeId, int left, int right, int cLeft, int cRight, int val)
{
    if (cLeft <= left && right <= cRight)
    {
        nodes[nodeId].tag += val;
        nodes[nodeId].answer.count += val;
        return;
    }
    down(nodeId);
    int mid = (left + right) >> 1;
    if (mid < cRight)
    {
        modify(nodeId << 1 | 1, mid + 1, right, cLeft, cRight, val);
    }
    if (mid + 1 > cLeft)
    {
        modify(nodeId << 1, left, mid, cLeft, cRight, val);
    }
    up(nodeId);
}

int main()
{
    int maxStudentId = 0;
    int n, m;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int leftStudentId, rightStudentId;
        scanf("%d %d", &leftStudentId, &rightStudentId);
        changes[i] = {leftStudentId, rightStudentId};
        maxStudentId = max(maxStudentId, rightStudentId);
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++)
    {
        int leftDay, rightDay;
        scanf("%d %d", &leftDay, &rightDay);
        querys[i] = {i, leftDay - 1, rightDay - 1};
    }
    blockSize = sqrt(n);
    int leftDay = 0, rightDay = -1;
    sort(querys, querys + m);
    build(1, 1, maxStudentId);
    // modify(1, 1, maxStudentId, changes[0].leftStudentId, changes[0].rightStudentId, 1);
    for (int i = 0; i < m; i++)
    {
        const Query &query = querys[i];
        while (leftDay > query.leftDay)
        {
            leftDay--;
            modify(1, 1, maxStudentId, changes[leftDay].leftStudentId, changes[leftDay].rightStudentId, 1);
        }
        while (rightDay < query.rightDay)
        {
            rightDay++;
            modify(1, 1, maxStudentId, changes[rightDay].leftStudentId, changes[rightDay].rightStudentId, 1);
        }
        while (leftDay < query.leftDay)
        {
            modify(1, 1, maxStudentId, changes[leftDay].leftStudentId, changes[leftDay].rightStudentId, -1);
            leftDay++;
        }
        while (rightDay > query.rightDay)
        {
            modify(1, 1, maxStudentId, changes[rightDay].leftStudentId, changes[rightDay].rightStudentId, -1);
            rightDay--;
        }
        answers[query.id] = nodes[1].answer;
    }
    for (int i = 0; i < m; i++)
    {
        printf("%d %d\n", answers[i].id, answers[i].count);
    }
}