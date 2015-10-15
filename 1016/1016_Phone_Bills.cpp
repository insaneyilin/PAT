#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

struct Record 
{
    int month;
    int day;
    int hour;
    int minute;

    bool on_line;
    
    bool operator<(const Record &that) const 
    {
        if (day == that.day)
        {
            if (hour == that.hour)
            {
                
                return minute < that.minute;
            }
            else
                return hour < that.hour;
        }
        else
            return day < that.day;
    }
};

int toll[24];  // 每个小时的费率
map<string, vector<Record>> m;  // 保存每个客户的通话记录

// 计算一次通话的费用和时间
// r1 -- on-line 记录
// r2 -- off-line 记录
void compute_charge(Record r1, Record r2, double &charge, int &time) {
    charge = 0.0;
    time = 0;

    while (r1.day < r2.day || r1.hour < r2.hour || r1.minute < r2.minute)
    {
        charge += toll[r1.hour];
        ++time;  // 按每分钟来计算
        ++(r1.minute);
        if (r1.minute == 60)  // 1 小时 60 分钟
        {
            r1.minute = 0;
            ++(r1.hour);
            if (r1.hour == 24)  // 1 天 24 小时
            {
                r1.hour = 0;
                ++(r1.day);
            }
        }
    }
}

int main(int argc, char * const argv[])
{
    int i, j;
    int num_records = 0;
    for (i = 0; i < 24; ++i)  // 输入每小时费率
    {
        cin >> toll[i];
    }

    cin >> num_records;
    for (i = 0; i < num_records; ++i)  // 输入所有记录
    {
        string name;
        string on_line_str;
        Record tmp;
        cin >> name;
        scanf("%d:%d:%d:%d", &tmp.month, &tmp.day, &tmp.hour, &tmp.minute);
        cin >> on_line_str;
        tmp.on_line = (on_line_str == "on-line") ? true : false;
        m[name].push_back(tmp);
    }

    //for (auto customer : m)  // 这里注意要用 auto&，否则无法真正排序
    //{
    //    sort(customer.second.begin(), customer.second.end());
    //    for (auto e : customer.second)
    //    {
    //        cout << e.day << " " << e.hour << " " << e.minute << " " << e.on_line << endl;
    //    }
    //    cout << endl;
    //}
    //cout << endl;

    for (auto &customer : m)
    {
        bool find_pair = false;
        double total_charge = 0.0;

        sort(customer.second.begin(), customer.second.end());  // 按时间排序
        for (auto itr = customer.second.begin(); itr != customer.second.end(); ++itr)
        {
            // 找到一对 on-off 匹配，由于已经按时间排序，一定是相邻的两条记录
            if (itr->on_line && (itr + 1) != customer.second.end() && !(itr + 1)->on_line)
            {
                if (!find_pair)  // 第一次找到匹配时。注意如果找不到 on-off 匹配不输出"姓名"和"月份"
                {
                    cout << customer.first;
                    printf(" %02d\n", itr->month);
                    find_pair = true;
                }

                // 输出一次通话信息
                printf("%02d:%02d:%02d %02d:%02d:%02d",
                    itr->day, itr->hour, itr->minute, (itr + 1)->day, (itr + 1)->hour, (itr + 1)->minute);

                double charge = 0.0;
                int time = 0;
                compute_charge(*itr, *(itr + 1), charge, time);  // 计算本次通话时间和费用
                printf(" %d $%.2f\n", time, charge / 100);

                total_charge += charge;  // 总费用累加
            }
        }

        if (find_pair)  // 至少有一对 on-off 匹配才输出总费用
        {
            printf("Total amount: $%.2lf\n", total_charge / 100);
        }
    }
}