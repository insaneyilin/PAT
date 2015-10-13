# 1015. Reversible Primes

http://www.patest.cn/contests/pat-a-practise/1015

一个数本身和其在 d 进制下的逆序都是素数，称为 “Reversible Prime”。

判断一个数在 d 进制表示下是否是 “Reversible Prime”。

例子，73 在十进制下表示仍为 73，逆序为 37， 是素数。

23 在 2 进制下表示为 10111，其逆序 11101，十进制值为 29，是素数。

```cpp
#include <iostream>
#include <string>

using namespace std;

// 判断素数
bool is_prime(int n)
{
    if (n <= 1)
        return false;
    for (int i = 2; i * i <= n; ++i)  // 避免用 sqrt()
    {
        if (n % i == 0)
            return false;
    }

    return true;
}

// 判断 reverse prime
bool judge(int n, int d)
{
    if (!is_prime(n))
        return false;
    
    // 注意这里直接求 d 进制逆序后数的值
    int rev = 0;
    while (n)
    {
        rev = d * rev + (n % d);
        n /= d;
    }

    return is_prime(rev);
}

int main()
{
    int n, d;

    while (cin >> n && n >= 0)
    {
        cin >> d;
        cout << (judge(n, d) ? "Yes" : "No") << endl;
    }

    return 0;
}
```
