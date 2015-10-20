# 1010. Radix

http://www.patest.cn/contests/pat-a-practise/1010

给出两个数，其中一个数是 r 进制的，问另外一个数是多少进制才能使得两数相等。所有数长度不超过 10，每一位只有0-9还有a-z。

一开始我觉得直接对进制进行遍历就可以，但是注意题目没有告诉我们 radix 的取值范围，radix 可能取值非常大。如果把对 radix 遍历的上限设得很大，会导致超时，设得不够大有些 case 过不了。

```
测试用例:
s9jix hj 1 36

对应输出应该为:
2792614
```

第一次代码（radix 遍历上限设为100000，有三个 case 答案错误，得分 22/ 25）：

```cpp
#include <iostream>
#include <string>

#include <limits.h>

using namespace std;

long long to_decimal(string s, long long radix)
{
    long long res = 0;
    for (int i = 0; i < s.size(); ++i)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            // 数字中出现了超出当前进制表示的数，比如二进制出现了 'a'
            if (s[i] - '0' >= radix)
            {
                return -1;
            }

            res = res * radix + (s[i] - '0');
        }
        else
        {
            if (s[i] - 'a' + 10 >= radix)
            {
                return -1;
            }

            res = res * radix + (s[i] - 'a' + 10);
        }
    }

    return res;
}

int main(int argc, char * const argv[])
{
    string n1, n2;
    long long tag, radix;

    cin >> n1 >> n2 >> tag >> radix;

    string query, train;
    if (tag == 1)
    {
        query = n1;
        train = n2;
    }
    else
    {
        query = n2;
        train = n1;
    }

    int val_decimal_query = to_decimal(query, radix);
    for (long long rad = 2; rad <= 100000; ++rad)
    {
        if (val_decimal_query == to_decimal(train, rad))
        {
            cout << rad << endl;
            return 0;
        }
    }

    cout << "Impossible" << endl;

    return 0;
}
```