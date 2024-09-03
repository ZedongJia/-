#include <iostream>
#include <queue>
#include <string>
#include <vector>

#define N 100001
typedef struct Node
{
    struct Node *parent = nullptr;
    struct Node *lChild = nullptr;
    struct Node *rChild = nullptr;
    int val = 0;
    int count = 0;
    int size = 0;
} Node;

Node *root = nullptr;
void maintain(Node *node)
{
    int lSize = 0;
    int rSize = 0;
    if (node->lChild)
        lSize = node->lChild->size;
    if (node->rChild)
        rSize = node->rChild->size;
    node->size = node->count + lSize + rSize;
}

bool isLeftChild(Node *node)
{
    if (node->parent->lChild == node)
        return true;
    return false;
}

void rotate(Node *node)
{
    bool isLR = !isLeftChild(node);
    Node *parent = node->parent;
    Node *gParent = parent->parent;
    if (gParent)
    {
        if (isLeftChild(parent))
            gParent->lChild = node;
        else
            gParent->rChild = node;
    }
    node->parent = gParent;
    if (isLR)
    {
        // left rotate
        parent->rChild = node->lChild;
        if (parent->rChild)
        {
            parent->rChild->parent = parent;
        }
        node->lChild = parent;
        parent->parent = node;
    }
    else
    {
        // right rotate
        parent->lChild = node->rChild;
        if (parent->lChild)
        {
            parent->lChild->parent = parent;
        }
        node->rChild = parent;
        parent->parent = node;
    }
    maintain(parent);
    maintain(node);
}

void splay(Node *node)
{
    while (node->parent != nullptr)
    {
        if (node->parent->parent)
        {
            if (isLeftChild(node) == isLeftChild(node->parent))
                // right right or left left
                rotate(node->parent);
            else
                // right left or left right
                rotate(node);
        }
        rotate(node);
    }
    root = node;
}

void insert(int val)
{
    if (root == nullptr)
    {
        // first
        root = new Node;
        root->val = val;
        root->count = 1;
        maintain(root);
        return;
    }
    Node *pptr = nullptr;
    Node *ptr = root;
    while (ptr)
    {
        if (ptr->val > val)
        {
            pptr = ptr;
            ptr = ptr->lChild;
        }
        else if (ptr->val < val)
        {
            pptr = ptr;
            ptr = ptr->rChild;
        }
        else
        {
            // equal
            ptr->count++;
            maintain(ptr);
            if (pptr)
            {
                maintain(pptr);
                splay(ptr);
            }
            break;
        }
    }
    if (ptr)
    {
        return;
    }
    Node *temp = new Node;
    temp->val = val;
    temp->count = 1;
    temp->parent = pptr;
    if (pptr->val > val)
    {
        // left
        pptr->lChild = temp;
    }
    else if (pptr->val < val)
    {
        pptr->rChild = temp;
        // right
    }
    maintain(temp);
    maintain(pptr);
    splay(temp);
}

int findRank(int val)
{
    int rank = 0;
    Node *ptr = root;
    while (ptr)
    {
        if (ptr->val < val)
        {
            int lSize = 0;
            if (ptr->lChild)
                lSize = ptr->lChild->size;
            rank += lSize + ptr->count;
            ptr = ptr->rChild;
        }
        else if (ptr->val > val)
        {
            ptr = ptr->lChild;
        }
        else
        {
            int lSize = 0;
            if (ptr->lChild)
                lSize = ptr->lChild->size;
            rank += lSize;
            splay(ptr);
            break;
        }
    }
    return rank + 1;
}

int findVal(int rank)
{
    int val = 0;
    Node *ptr = root;
    while (ptr)
    {
        if (ptr->lChild && ptr->lChild->size >= rank)
        {
            ptr = ptr->lChild;
        }
        else
        {
            int lSize = 0;
            if (ptr->lChild)
                lSize = ptr->lChild->size;
            rank -= (ptr->count + lSize);
            if (rank <= 0)
            {
                val = ptr->val;
                splay(ptr);
                break;
            }
            ptr = ptr->rChild;
        }
    }
    return val;
}

int preVal()
{
    Node *ptr = root->lChild;
    if (ptr)
    {
        while (ptr->rChild)
        {
            ptr = ptr->rChild;
        }
        splay(ptr);
        return ptr->val;
    }
    else
    {
        return -1;
    }
}

int postVal()
{
    Node *ptr = root->rChild;
    if (ptr)
    {
        while (ptr->lChild)
        {
            ptr = ptr->lChild;
        }
        splay(ptr);
        return ptr->val;
    }
    else
    {
        return -1;
    }
}

void mergeTree(Node *t1, Node *t2)
{
    if (!t1 && !t2)
    {
        root = nullptr;
        return;
    }
    if (!t1)
    {
        root = t2;
        t2->parent = nullptr;
        return;
    }
    if (!t2)
    {
        root = t1;
        t1->parent = nullptr;
        return;
    }
    t1->parent = nullptr;
    t2->parent = nullptr;
    // merge
    Node *ptr = t1;
    while (ptr->rChild)
    {
        ptr = ptr->rChild;
    }
    splay(ptr);
    ptr->rChild = t2;
    ptr->rChild->parent = ptr;
    ptr->parent = nullptr;
    root = ptr;
    maintain(root);
}

void remove(int val)
{
    Node *ptr = root;
    while (ptr)
    {
        if (ptr->val < val)
        {
            ptr = ptr->rChild;
        }
        else if (ptr->val > val)
        {
            ptr = ptr->lChild;
        }
        else
        {
            splay(ptr);
            break;
        }
    }
    root->count--;
    if (root->count <= 0)
    {
        mergeTree(root->lChild, root->rChild);
    }
    else
    {
        maintain(root);
    }
}

std::vector<int> results;

int main()
{
    int n;
    scanf("%d", &n);
    while (n--)
    {
        int op, num;
        scanf("%d %d", &op, &num);
        switch (op)
        {
        case 1: {
            insert(num);
            break;
        }
        case 2: {
            remove(num);
            break;
        }
        case 3: {
            results.push_back(findRank(num));
            break;
        }
        case 4: {
            results.push_back(findVal(num));
            break;
        }
        case 5: {
            insert(num);
            results.push_back(preVal());
            remove(num);
            break;
        }
        case 6: {
            insert(num);
            results.push_back(postVal());
            remove(num);
            break;
        }
        }
    }
    for (int result : results)
        printf("%d\n", result);
}