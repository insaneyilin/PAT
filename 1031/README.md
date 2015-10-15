# 1031. Hello World for U

http://www.patest.cn/contests/pat-a-practise/1031

按照 U 形打印字符串。左右两列长度为 n1, n3（n1 == n3），底部一行长度为 n2。

设字符串长度为 `N`：

```
n1 = n3 = max { k| k <= n2 for all 3 <= n2 <= N } with n1 + n2 + n3 - 2 = N.
```

先确定 n1 n2 的值，再按照格式输出即可。由上面的规则，可以循环遍历 n2 来找 n1。

```cpp
// 确定 n1, n2 和 n3 的值
//  n1 = n3 = max { k| k <= n2 for all 3 <= n2 <= N } with n1 + n2 + n3 - 2 = N.
bool found = false;
for (n2 = 3; n2 <= n; ++n2)
{
    for (n1 = n2; n1 >= 1; --n1)
    {
        if (n1 + n2 + n1 - 2 == n)
        {
            found = true;
            break;
        }
    }
    if (found)
        break;
}
```