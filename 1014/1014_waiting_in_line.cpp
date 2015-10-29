#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <stdio.h>
#include <limits.h>

using namespace std;

int main(int argc, char * const argv[])
{
    // n -- number of windows
    // m -- the maximum capacity of each line inside the yellow line
    // k -- number of customers
    // q -- number of customer queries
    int n, m, k, q;
    cin >> n >> m >> k >> q;

    vector<int> process_time_costs(k, 0);  // 每个顾客的处理时间
    for (int i = 0; i < k; ++i)
    {
        cin >> process_time_costs[i];
    }

    vector<queue<int>> queues(n);  // n 个窗口对应的队列，保存每个顾客的编号
    vector<int> queue_cur_times(n, 0);  // n 个窗口对应的队列的当前时间
    vector<int> leave_times(k, 0);   // k 个顾客的离开时间

    int idx_queue = 0;
    int idx_customer = 0;

    // 前 n * m 个顾客进队；顾客一旦进队，就可以确定该顾客的离开时间
    for (; idx_customer < m * n && idx_customer < k; ++idx_customer)
    {
        queues[idx_queue].push(idx_customer);  // 顾客进队
        // 计算顾客离开时间
        leave_times[idx_customer] = queue_cur_times[idx_queue] + process_time_costs[idx_customer];
        // 更新队列当前时间：刚刚进队的顾客的离开时间
        queue_cur_times[idx_queue] = leave_times[idx_customer];

        idx_queue = (idx_queue + 1) % n;  // 循环遍历队列 1 到 n（但这里以0为起始下标，实际上是 0 到 n-1）
    }

    // 黄线后的顾客开始进队
    for (; idx_customer < k; ++idx_customer)
    {
        int min_leave_time = INT_MAX;  // 黄线前区域中最早离开的顾客的离开时间
        int min_idx = -1;  //  黄线前区域中最早离开的顾客所在队列的编号（即最早有坑的队列编号）
        for (int j = 0; j < n; ++j)
        {
            int t = queues[j].front();  // 比较队首顾客的离开时间
            if (min_leave_time > leave_times[t])
            {
                min_leave_time = leave_times[t];
                min_idx = j;
            }
        }

        queues[min_idx].pop();
        queues[min_idx].push(idx_customer);  // 新顾客入队
        // 计算刚刚入队顾客的离开时间
        leave_times[idx_customer] = queue_cur_times[min_idx] + process_time_costs[idx_customer];
        // 更新队列当前时间：刚刚入队的顾客的离开时间
        queue_cur_times[min_idx] = leave_times[idx_customer];
    }

    // 查询，输出
    for (int i = 0; i < q; ++i)
    {
        int query;
        cin >> query;  // 1-based index
        --query;  // 0-based index

        // 注意按照题意，是开始服务时间不能超过 17:00，而不是服务结束时间
        // 即 17:00 以后还没有开始接受服务才输出 "Sorry"
        if (leave_times[query] - process_time_costs[query] >= 60 * 9)
        {
            cout << "Sorry\n";
        }
        else
        {
            int hour = leave_times[query] / 60;
            int minute = leave_times[query] % 60;
            cout << setw(2) << setfill('0') << 8 + hour << ":";
            cout << setw(2) << setfill('0') << minute << endl;
        }
    }

    return 0;
}