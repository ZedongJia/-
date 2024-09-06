#include <algorithm>
#include <iostream>
const int N = 500001;
typedef struct Node
{
    int l = 0;
    int r = 0;
    int maxGreen[3];
    int minGreen[3];
} Node;
Node nodes[N];
std::string input;
int pos = 0;
int gId = 1;

int makeTree()
{
    int nId = gId;
    gId++;
    switch (input[pos++])
    {
    case '0': {
        nodes[nId].maxGreen[0] = 0;
        nodes[nId].maxGreen[1] = 1;
        nodes[nId].maxGreen[2] = 0;
        nodes[nId].minGreen[0] = 0;
        nodes[nId].minGreen[1] = 1;
        nodes[nId].minGreen[2] = 0;
        break;
    }
    case '1': {
        nodes[nId].l = makeTree();
        nodes[nId].maxGreen[0] = std::max(nodes[nodes[nId].l].maxGreen[1], nodes[nodes[nId].l].maxGreen[2]);
        nodes[nId].maxGreen[1] = std::max(nodes[nodes[nId].l].maxGreen[0], nodes[nodes[nId].l].maxGreen[2]) + 1;
        nodes[nId].maxGreen[2] = std::max(nodes[nodes[nId].l].maxGreen[0], nodes[nodes[nId].l].maxGreen[1]);
        nodes[nId].minGreen[0] = std::min(nodes[nodes[nId].l].minGreen[1], nodes[nodes[nId].l].minGreen[2]);
        nodes[nId].minGreen[1] = std::min(nodes[nodes[nId].l].minGreen[0], nodes[nodes[nId].l].minGreen[2]) + 1;
        nodes[nId].minGreen[2] = std::min(nodes[nodes[nId].l].minGreen[0], nodes[nodes[nId].l].minGreen[1]);
        break;
    }
    case '2': {
        nodes[nId].l = makeTree();
        nodes[nId].r = makeTree();
        nodes[nId].maxGreen[0] = std::max(nodes[nodes[nId].l].maxGreen[1] + nodes[nodes[nId].r].maxGreen[2],
                                          nodes[nodes[nId].l].maxGreen[2] + nodes[nodes[nId].r].maxGreen[1]);
        nodes[nId].maxGreen[1] = std::max(nodes[nodes[nId].l].maxGreen[0] + nodes[nodes[nId].r].maxGreen[2],
                                          nodes[nodes[nId].l].maxGreen[2] + nodes[nodes[nId].r].maxGreen[0]) +
                                 1;
        nodes[nId].maxGreen[2] = std::max(nodes[nodes[nId].l].maxGreen[0] + nodes[nodes[nId].r].maxGreen[1],
                                          nodes[nodes[nId].l].maxGreen[1] + nodes[nodes[nId].r].maxGreen[0]);
        nodes[nId].minGreen[0] = std::min(nodes[nodes[nId].l].minGreen[1] + nodes[nodes[nId].r].minGreen[2],
                                          nodes[nodes[nId].l].minGreen[2] + nodes[nodes[nId].r].minGreen[1]);
        nodes[nId].minGreen[1] = std::min(nodes[nodes[nId].l].minGreen[0] + nodes[nodes[nId].r].minGreen[2],
                                          nodes[nodes[nId].l].minGreen[2] + nodes[nodes[nId].r].minGreen[0]) +
                                 1;
        nodes[nId].minGreen[2] = std::min(nodes[nodes[nId].l].minGreen[0] + nodes[nodes[nId].r].minGreen[1],
                                          nodes[nodes[nId].l].minGreen[1] + nodes[nodes[nId].r].minGreen[0]);
        break;
    }
    }
    return nId;
}

int main()
{
    std::cin >> input;
    int root = makeTree();
    printf("%d", *std::max_element(nodes[root].maxGreen, nodes[root].maxGreen + 3));
    printf(" %d", *std::min_element(nodes[root].minGreen, nodes[root].minGreen + 3));
}