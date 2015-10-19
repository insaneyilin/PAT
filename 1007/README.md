# 1007. Maximum Subsequence Sum

http://www.patest.cn/contests/pat-a-practise/1007

最大连续子序列和问题，经典的 DP 思想，需要记录子序列起始位置。

需要注意当序列中包含 0 时，输出结果隐含着子序列最长，比如 `-1 0 2 -3`，要求的子序列为 `0 2` 而不是 `2`，看下面代码里 `if ` 语句中注释掉的地方：

```cpp
#include <iostream>
#include <algorithm>  // std::max
#include <limits.h>  // INT_MIN

using namespace std;

int a[10000 + 5];
int f[10000 + 5];

void dp(int a[], int n)
{
    f[0] = a[0];

    int tmp_start = 0;
    int start = 0, end = 0;
    int ans = a[0];  // 不能 ans = INT_MIN，3 号测试样例过不了
    for (int i = 1; i < n; ++i)
    {
        f[i] = max(f[i - 1] + a[i], a[i]);
        if (/*f[i] == a[i]*/ f[i - 1] < 0)
        {
            tmp_start = i;
        }

        if (f[i] > ans)
        {
            ans = f[i];
            start = tmp_start;
            end = i;
        }
    }

    if (ans < 0)
    {
        cout << 0 << " " << a[0] << " " << a[n-1] << endl;
    }
    else
    {
        cout << ans << " " << a[start] << " " << a[end] << endl;
    }
}

int main(int argc, char * const argv[])
{
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i)
    {
        cin >> a[i];
    }

    dp(a, k);

    return 0;
}
```

使用 O(1) 额外空间（滚动数组思想）：

```cpp
#include <iostream>
#include <algorithm>  // std::max
#include <limits.h>  // INT_MIN

using namespace std;

int a[10000 + 5];

void dp(int a[], int n)
{
    int sum = 0;
    int first_idx = 0;
    int max_sum = a[0];
    int max_seq_start_idx = 0, max_seq_end_idx = 0;

    for (int i = 0; i < n; ++i)
    {
        if (sum < 0)
        {
            sum = a[i];
            first_idx = i;
        }
        else
            sum += a[i];

        if (max_sum < sum)
        {
            max_sum = sum;
            max_seq_start_idx = first_idx;
            max_seq_end_idx = i;
        }
    }

    if (max_sum < 0)
        cout << 0 << " " << a[0] << " " << a[n - 1] << endl;
    else
        cout << max_sum << " " << a[max_seq_start_idx] << " " << a[max_seq_end_idx] << endl;

    return;
}

int main(int argc, char * const argv[])
{
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i)
    {
        cin >> a[i];
    }

    dp(a, k);

    return 0;
}

```


