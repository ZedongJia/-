#include <algorithm>
#include <iostream>
#include <map>
#include <queue>

typedef struct Box
{
    int max;
    int len;
    bool operator<(const Box b) const
    {
        return len > b.len;
    }
} Box;

std::map<int, std::priority_queue<Box> *> hash;

int main()
{
    int n = 0;
    std::cin >> n;
    int nums[100001];
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);
    std::sort(nums, nums + n);
    for (int i = 0; i < n; i++)
    {
        if (hash.find(nums[i]) != hash.end())
        {
            // find
            Box b = hash[nums[i]]->top();
            hash[nums[i]]->pop();
            if (hash[nums[i]]->size() == 0)
                hash.erase(nums[i]);
            b.max++;
            b.len++;
            // push
            if (hash.find(b.max + 1) == hash.end())
                hash[b.max + 1] = new std::priority_queue<Box>;
            hash[b.max + 1]->push(b);
        }
        else
        {
            Box box;
            box.max = nums[i];
            box.len = 1;
            if (hash.find(box.max + 1) == hash.end())
                hash[box.max + 1] = new std::priority_queue<Box>;
            hash[box.max + 1]->push(box);
        }
    }
    int ans = INT32_MAX;
    for (std::map<int, std::priority_queue<Box> *>::iterator itr = hash.begin(); itr != hash.end(); itr++)
    {
        std::priority_queue<Box> *q = itr->second;
        while (!q->empty())
        {
            Box b = q->top();
            q->pop();
            ans = std::min(ans, b.len);
        }
    }
    printf("%d", ans);
}