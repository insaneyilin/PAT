#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <limits.h>

using namespace std;

struct Customer
{
    Customer()
    {
        arrive_time = 0;
        process_time_cost = 0;
    }

    Customer(int arrv_t_, int p_t_) :
        arrive_time(arrv_t_), process_time_cost(p_t_)
    {}

    int arrive_time;   // 到达时刻
    int process_time_cost;   // 需要的处理时间
};

int main(int argc, char * const argv[])
{
    int n, k;
    cin >> n >> k;

    vector<Customer> customers(n);  // 保存 n 个顾客信息

    for (int i = 0; i < n; ++i)
    {
        int h, m, s;
        int process_t;
        scanf("%d:%d:%d %d", &h, &m, &s, &process_t);

        // 时间全部转为秒数
        customers[i].arrive_time = h * 60 * 60 + m * 60 + s;
        customers[i].process_time_cost = process_t * 60;
    }

    // 按照到达时刻对顾客进行排序
    sort(customers.begin(), customers.end(), [](const Customer &a, const Customer &b) {
        return a.arrive_time < b.arrive_time;
    });

    vector<int> window_cur_times(k, 8 * 60 * 60);  // 所有 k 个窗口的当前时间

    int sum_wait_time = 0;   // 顾客等候时间总和
    int num_served_customers = 0;  // 接受服务的顾客数

    // 以顾客为中心进行模拟
    for (int i = 0; i < n; ++i)
    {
        // 到达时刻晚于 17:00，终止
        if (customers[i].arrive_time > 17 * 60 * 60)
            break;

        // 窗口最早出现空闲的时间（即找当前时间最小的窗口）
        auto itr_min_window_cur_time = min_element(window_cur_times.begin(), window_cur_times.end());
        if (*itr_min_window_cur_time > customers[i].arrive_time)  // 窗口最早空闲时间大于（晚于）最近顾客到达时间，顾客才需要等待
        {
            sum_wait_time += *itr_min_window_cur_time - customers[i].arrive_time;
            *itr_min_window_cur_time += customers[i].process_time_cost;  // 更新相应窗口的当前时间
        }
        else
        {
            *itr_min_window_cur_time = customers[i].arrive_time + customers[i].process_time_cost;  // 更新相应窗口的当前时间
        }

        ++num_served_customers;  // 接受服务的顾客数加1
    }

    printf("%.1f", ((float)sum_wait_time / num_served_customers) / 60);

    return 0;
}