#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>

using namespace std;

struct Record
{
    Record(string reg_num, int s_, int loc_num) : 
        registration_number(reg_num), score(s_), location_number(loc_num)
    {
        local_rank = -1;
        final_rank = -1;
    }

    string registration_number;
    int score;

    int location_number;
    int local_rank;
    int final_rank;
};

int main(int argc, char * const argv[])
{
    int n;
    cin >> n;
    vector<Record> records;

    // 自定义排序规则：按分数降序，分数相同按注册号非降序
    auto cmp = [](const Record &a, const Record &b) {
        if (a.score == b.score)
            return a.registration_number <= b.registration_number;
        else
            return a.score > b.score;
    };

    // loc_num 为区域编号，loc_start 为每个区域第一个记录的位置
    for (int loc_num = 1, loc_start = 0; loc_num <= n; ++loc_num)
    {
        int k;
        cin >> k;
        for (int i = 0; i < k; ++i)
        {
            string reg_num;
            int score;
            cin >> reg_num >> score;

            records.push_back(Record(reg_num, score, loc_num));
        }

        // 局部排序
        sort(records.begin() + loc_start, records.end(), cmp);

        // 计算局部排名
        int rank = 0;
        for (auto itr = records.begin() + loc_start; itr != records.end(); ++itr)
        {
            if (itr == records.begin() + loc_start || (itr - 1)->score > itr->score)
            {
                rank = itr - records.begin() - loc_start + 1;
            }

            itr->local_rank = rank;
        }
        loc_start += k;
    }

    // 全局排序
    sort(records.begin(), records.end(), cmp);

    cout << records.size() << endl;

    // 计算全局排名
    int rank = 0;
    for (auto itr = records.begin(); itr != records.end(); ++itr)
    {
        if (itr == records.begin() || (itr - 1)->score > itr->score)
        {
            rank = itr - records.begin() + 1;
        }

        itr->final_rank = rank;

        cout << itr->registration_number << " " << itr->final_rank << " " 
            << itr->location_number << " " << itr->local_rank << endl;
    }

    return 0;
}
