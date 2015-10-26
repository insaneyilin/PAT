# 1019. General Palindromic Number

http://www.patest.cn/contests/pat-a-practise/1019

给出一个十进制数 `N` 和一个进制 `b`，判断 `N` 在 `b` 进制下是不是 **回文数**。

直接进行进制转换即可。注意下面循环用 `do ... while` 处理 `N == 0` 的情况。

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <limits.h>

using namespace std;

bool is_palindromic(const vector<int> &nums)
{
    int n = nums.size();
    int m = nums.size() / 2;
    for (int i = 0; i < m; ++i)
    {
        if (nums[i] != nums[n - i - 1])
        {
            return false;
        }
    }

    return true;
}

int main(int argc, char * const argv[])
{
    int n, b;
    cin >> n >> b;

    vector<int> res;

    do
    {
        res.push_back(n % b);
        n /= b;
    } while (n);

    if (is_palindromic(res))
    {
        cout << "Yes\n";
    }
    else
    {
        cout << "No\n";
    }

    for (int i = 0; i < res.size(); ++i)
    {
        cout << (i == 0 ? "" : " ") << res[res.size() - i - 1];
    }
    cout << endl;

    return 0;
}
```