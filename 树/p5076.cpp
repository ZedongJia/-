#include <iostream>
#include <queue>
typedef struct Node
{
    int data;
    struct Node *father;
    struct Node *left;
    struct Node *right;
} Node;
int queryRank(Node *root, int data)
{
    std::queue<Node *> q;
    q.push(root);
    int num = 0;
    while (!q.empty())
    {
        Node *p = q.front();
        q.pop();
        if (p->data < data)
            num++;
        if (p->left != nullptr)
            q.push(p->left);
        if (p->right != nullptr)
            q.push(p->right);
    }
    return num + 1;
}
int queryNumByRank(Node *root, int rank)
{
    Node *p = root;
    while (p != nullptr)
    {
        int prank = queryRank(root, p->data);
        if (prank > rank)
        {
            p = p->left;
        }
        else if (prank < rank)
        {
            p = p->right;
        }
        else
        {
            return p->data;
        }
    }
    return 0;
}
Node *queryBefore(Node *root, int data)
{
    Node *p = root;
    Node *before = nullptr;
    while (p != nullptr)
    {
        if (p->data >= data)
        {
            p = p->left;
        }
        else
        {
            before = p;
            p = p->right;
        }
    }
    return before;
}
Node *queryAfter(Node *root, int data)
{
    Node *p = root;
    Node *after = nullptr;
    while (p != nullptr)
    {
        if (p->data > data)
        {
            after = p;
            p = p->left;
        }
        else
        {
            p = p->right;
        }
    }
    return after;
}
void insert(Node *root, int data)
{
    /**
        3
    2      4
    */
    Node *p = root;
    Node *pre = p;
    while (p != nullptr)
    {
        pre = p;
        if (p->data > data)
        {
            p = p->left;
        }
        else
        {
            p = p->right;
        }
    }
    if (pre->data > data)
    {
        pre->left = new Node{data, pre, nullptr, nullptr};
    }
    else
    {
        pre->right = new Node{data, pre, nullptr, nullptr};
    }
}
void rm(Node *node)
{
    if (node == nullptr)
    {
        return;
    }
    rm(node->left);
    rm(node->right);
    delete node;
}
int main()
{
    Node *root = nullptr;
    int q;
    int ans[100000];
    int ansIndex = 0;
    std::cin >> q;
    while (q--)
    {
        int op, x;
        std::cin >> op >> x;
        switch (op)
        {
        case 1: {
            ans[ansIndex] = queryRank(root, x);
            ansIndex++;
            break;
        }
        case 2: {
            ans[ansIndex] = queryNumByRank(root, x);
            ansIndex++;
            break;
        }
        case 3: {
            Node *before = queryBefore(root, x);
            ans[ansIndex] = before == nullptr ? -2147483647 : before->data;
            ansIndex++;
            break;
        }
        case 4: {
            Node *after = queryAfter(root, x);
            ans[ansIndex] = after == nullptr ? 2147483647 : after->data;
            ansIndex++;
            break;
        }
        case 5: {
            if (root == nullptr)
            {
                root = new Node{x, nullptr, nullptr, nullptr};
            }
            else
            {
                insert(root, x);
            }
            break;
        }
        }
    }
    for (int i = 0; i < ansIndex - 1; i++)
        printf("%d\n", ans[i]);
    printf("%d", ans[ansIndex - 1]);
    rm(root);
    return 0;
}