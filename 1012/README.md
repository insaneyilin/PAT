# 1012. The Best Rank

http://www.patest.cn/contests/pat-a-practise/1012

输入每个学生的 ID 和三门课程的成绩（C -- C 语言，M -- 数学，E -- 英语），再求三门课程的平均分 A。按照 A C M E 的顺序找出每个学生最好的名次。

按照 A C M E 的顺序对每一门课的分数进行排序，并更新每个学生的最好名次。

这题虽然看起来简单，但是实际写的时候很容易各种细节出错。

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <stdio.h>

using namespace std;

int main(int argc, char * const argv[])
{
    int n, m;
    cin >> n >> m;

    const char COURSE_NAMES[4] = {'A', 'C', 'M', 'E'};

    // 保存每一科目的 <id, score>
    vector<pair<string, int>> a_vec;
    vector<pair<string, int>> c_vec;
    vector<pair<string, int>> m_vec;
    vector<pair<string, int>> e_vec;

    for (int i = 0; i < n; ++i)
    {
        string stu_id;
        int score_c, score_m, score_e, score_a;
        cin >> stu_id >> score_c >> score_m >> score_e;
        score_a = (score_c + score_m + score_e) / 3;

        a_vec.push_back(make_pair(stu_id, score_a));
        c_vec.push_back(make_pair(stu_id, score_c));
        m_vec.push_back(make_pair(stu_id, score_m));
        e_vec.push_back(make_pair(stu_id, score_e));
    }

    // 保存最终结果
    unordered_map<string, pair<int, int>> result;  // pair format: <course, rank>

    // 按照 A > C > M > E 的优先级进行遍历
    vector<pair<string, int>> *courses[4];
    courses[0] = &a_vec;
    courses[1] = &c_vec;
    courses[2] = &m_vec;
    courses[3] = &e_vec;
    // 自定义比较规则
    auto cmp = [](const pair<string, int> &a, const pair<string, int> &b){
        return a.second > b.second;
    };
    for (int i = 0; i < 4; ++i)
    {
        sort(courses[i]->begin(), courses[i]->end(), cmp);

        int rank = 0;
        for (auto itr = courses[i]->begin(); itr != courses[i]->end(); ++itr)
        {
            // 注意排名相同情况的处理；前一个分数比当前分数大时更新排名
            if (itr == courses[i]->begin() || (itr - 1)->second > itr->second)
            {
                rank = itr - courses[i]->begin() + 1;
            }
            
            // 更新每个学生的 best rank
            string id = itr->first;
            auto t = result.find(id);
            if (t == result.end() || t->second.second > rank)
            {
                result[id] = make_pair(i, rank);
            }
        }
    }

    // 输出结果
    for (int i = 0; i < m; ++i)
    {
        string query;
        cin >> query;
        if (result.find(query) == result.end())
        {
            cout << "N/A" << endl;
        }
        else
        {
            cout << result[query].second << " " << COURSE_NAMES[result[query].first] << endl;
        }
    }

    return 0;
}
```
