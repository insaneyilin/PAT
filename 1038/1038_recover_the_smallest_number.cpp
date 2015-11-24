#include <iostream> 
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <numeric>

#include <stdio.h>
#include <string.h>

using namespace std;

int main(int argc, char * const argv[])
{
    int N;
    cin >> N;
    vector<string> nums_str(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> nums_str[i];
    }

    // 排序，注意排序规则
    std::sort(nums_str.begin(), nums_str.end(), [](const string &a, const string &b) {
        return a + b < b + a;
    });

    string res = std::accumulate(nums_str.begin(), nums_str.end(), string(""));

    bool all_zero = true;
    for (size_t i = 0; i < res.length(); ++i)
    {
        if (res[i] != '0')
        {
            all_zero = false;
            cout << res.substr(i) << endl;
            break;
        }
    }
    if (all_zero)  // 特殊处理结果为 0 的情况
    {
        cout << "0" << endl;
    }

    return 0;
}
