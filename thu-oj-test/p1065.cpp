#include <iostream>
#include <queue>
#include <vector>
typedef struct Machine
{
    std::vector<int> slots = std::vector<int>(10000, 0);
    int maxUsedSlot = -1;
} Machine;

typedef struct Task
{
    std::queue<int> orders;
    std::queue<int> times;
    int preMaxTime = -1;
} Task;

int main()
{
    int m, n;
    scanf("%d%d", &m, &n);
    std::vector<Machine> machines(m + 1);
    std::vector<Task> tasks(n + 1);
    int seqLen = m * n;
    std::vector<int> seqs(seqLen);
    for (int i = 0; i < seqLen; i++)
        scanf("%d", &seqs[i]);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int tmp;
            scanf("%d", &tmp);
            tasks[i].orders.push(tmp);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int tmp;
            scanf("%d", &tmp);
            tasks[i].times.push(tmp);
        }
    }
    for (int i = 0; i < seqLen; i++)
    {
        Task &task = tasks[seqs[i]];
        int order = task.orders.front();
        int time = task.times.front();
        task.orders.pop();
        task.times.pop();
        Machine &machine = machines[order];
        int startTime = task.preMaxTime + 1;
        bool isSetted = false;
        while (!isSetted)
        {
            isSetted = true;
            int nextTime = startTime;
            for (int ts = startTime; ts < startTime + time; ts++)
            {
                if (machine.slots[ts])
                {
                    isSetted = false;
                    nextTime = ts + 1;
                }
            }
            startTime = nextTime;
        }
        for (int ts = startTime; ts < startTime + time; ts++)
        {
            machine.slots[ts] = 1;
        }
        task.preMaxTime = startTime + time - 1;
        machine.maxUsedSlot = std::max(task.preMaxTime, machine.maxUsedSlot);
    }
    int res = -1;
    for (int i = 1; i <= m; i++)
    {
        res = std::max(res, machines[i].maxUsedSlot);
    }
    printf("%d", res + 1);
}