# 1042. Shuffling Machine

http://www.patest.cn/contests/pat-a-practise/1042

模拟洗牌。

直接模拟：

```cpp
#include <iostream> 
#include <vector>

using namespace std;

void shuffle_cards(const vector<int> &src, vector<int> &dst, const vector<int> &order)
{
    for (int i = 0; i < 54; ++i)
    {
        int j = order[i];
        dst[j] = src[i];
    }
}

void print_cards(const vector<int> &nums)
{
    static char *SUITS = "SHCDJ";

    for (int i = 0; i < 54; ++i)
    {
        cout << (i == 0 ? "" : " ");
        
        cout << SUITS[static_cast<int>(nums[i] / 13)];
        cout << (nums[i] % 13 + 1);
    }
    cout << endl;
}

int main(int argc, char * const argv[])
{
    int K;
    cin >> K;

    vector<int> nums(54, 0);
    vector<int> res(54, 0);
    for (int i = 0; i < 54; ++i)
    {
        nums[i] = i;
    }

    vector<int> order(54, 0);
    for (int i = 0; i < 54; ++i)
    {
        cin >> order[i];
        --(order[i]);
    }

    for (int k = 0; k < K; ++k)
    {
        if (k % 2 == 0)
        {
            shuffle_cards(nums, res, order);
        }
        else
        {
            shuffle_cards(res, nums, order);
        }
    }

    if (K % 2 == 0)
    {
        print_cards(nums);
    }
    else
    {
        print_cards(res);
    }

    return 0;
}

```

上面代码用了两个数组表示上一次洗牌结果，和本次洗牌结果，来回进行洗牌；实际上可以直接用一个二重循环：

```cpp
#include <iostream> 
#include <vector>

using namespace std;

void shuffle_cards(const vector<int> &src, vector<int> &dst, const vector<int> &order, int K)
{
    for (int i = 0; i < 54; ++i)
    {
        int t = i;
        for (int k = 0; k < K; ++k)
        {
            t = order[t];
        }
        dst[t] = src[i];
    }
}

void print_cards(const vector<int> &nums)
{
    static char *SUITS = "SHCDJ";

    for (int i = 0; i < 54; ++i)
    {
        cout << (i == 0 ? "" : " ");
        
        cout << SUITS[static_cast<int>(nums[i] / 13)];
        cout << (nums[i] % 13 + 1);
    }
    cout << endl;
}

int main(int argc, char * const argv[])
{
    int K;
    cin >> K;

    vector<int> nums(54, 0);
    vector<int> res(54, 0);
    for (int i = 0; i < 54; ++i)
    {
        nums[i] = i;
    }

    vector<int> order(54, 0);
    for (int i = 0; i < 54; ++i)
    {
        cin >> order[i];
        --(order[i]);
    }

    shuffle_cards(nums, res, order, K);

    print_cards(res);

    return 0;
}
```
