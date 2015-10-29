#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stdio.h>

using namespace std;

int main(int argc, char * const argv[])
{
    string num_str;
    cin >> num_str;

    // 用 Hash 表记录数字出现情况
    // 原数中出现数字 d，则 h[d] 加一
    // double 后的数中出现 d，则 h[d] 减一
    unordered_map<int, int> h;

    // string 转为 vector<int>
    vector<int> nums(num_str.begin(), num_str.end());
    for_each(nums.begin(), nums.end(), [&h](int &d){
        d = d - '0';

        // 数字出现次数加1
        if (h.find(d) == h.end())
            h[d] = 1;
        else
            ++(h[d]);
    });

    int carry = 0;  // 进位
    vector<int> doubled_nums(nums.size(), 0);
    for (int i = nums.size() - 1; i >= 0; --i)  // 从低位到高位
    {
        int d = nums[i] * 2 + carry;
        doubled_nums[i] = d % 10;
        carry = d / 10;

        // 数字出现次数减1
        if (h.find(doubled_nums[i]) == h.end())
            h[doubled_nums[i]] = -1;
        else
            --(h[doubled_nums[i]]);
    }

    // 如果最高位有进位或者 Hash 表中有数字的次数记录非 0，说明原数和 double 后的数中的数字有差异
    if (carry > 0 || 
        h.size() != count_if(h.begin(), h.end(), [](const pair<int, int> &pr) { return pr.second == 0; }))
        cout << "No\n";
    else
        cout << "Yes\n";

    if (carry > 0)
        cout << carry;

    for_each(doubled_nums.begin(), doubled_nums.end(), [](int &d){
        cout << d;
    });
    cout << endl;

    return 0;
}
