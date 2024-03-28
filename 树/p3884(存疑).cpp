#include <iostream>
#include <map>

typedef struct Node
{
    int id;
    int depth;
    Node *father;
    Node *left;
    Node *right;
} Node;
bool isLeaf(Node *node)
{
    return node->left == nullptr && node->right == nullptr;
}
int getLeafNum(Node *node)
{
    int cnt = 0;
    if (node->left != nullptr && isLeaf(node->left))
        cnt++;
    if (node->right != nullptr && isLeaf(node->right))
        cnt++;
    return cnt;
}
int getRootNum(Node *node)
{
    int cnt = 0;
    if (node->father != nullptr && node->father->id == 1)
        cnt++;
    return cnt * 2;
}
int calc(Node *n1, Node *n2)
{
    if (n1->depth < n2->depth)
    {
        Node *tmp = n1;
        n1 = n2;
        n2 = tmp;
    }
    int cnt = 0;
    if (isLeaf(n1))
    {
        cnt--;
    }
    if (isLeaf(n2))
    {
        cnt--;
    }
    while (n1->depth != n2->depth)
    {
        cnt += getLeafNum(n1) + getRootNum(n1);
        n1 = n1->father;
    }
    while (n1->id != n2->id)
    {
        cnt += getLeafNum(n1) + getLeafNum(n2) + getRootNum(n1) + getRootNum(n2);
        n1 = n1->father;
        n2 = n2->father;
    }
    cnt += getLeafNum(n1) + getRootNum(n1);
    return cnt;
}
void gc(Node *node)
{
    if (node == nullptr)
        return;
    gc(node->left);
    gc(node->right);
    delete node;
}
int main()
{
    int n;
    std::cin >> n;
    std::map<int, Node *> hash;
    Node *root = new Node{1, 1, nullptr, nullptr, nullptr};
    hash[1] = root;
    int maxDepth = 0;
    int width[200]{};
    width[1]++;
    for (int i = 0; i < n - 1; i++)
    {
        int src, dst;
        std::cin >> src >> dst;
        Node *tmp = new Node{dst, hash[src]->depth + 1, hash[src], nullptr, nullptr};
        if (hash[src]->left == nullptr)
        {
            hash[src]->left = tmp;
        }
        else
        {
            hash[src]->right = tmp;
        }
        hash[dst] = tmp;
        maxDepth = std::max(maxDepth, tmp->depth);
        width[tmp->depth]++;
    }
    int maxWidth = 0;
    for (int i = 1; i <= maxDepth; i++)
        maxWidth = std::max(maxWidth, width[i]);
    int x, y;
    std::cin >> x >> y;
    printf("%d\n", maxDepth);
    printf("%d\n", maxWidth);
    printf("%d", calc(hash[x], hash[y]));
    gc(root);
}