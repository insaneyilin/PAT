# 1054. The Dominant Color

http://www.patest.cn/contests/pat-a-practise/1054

输入一个二维矩阵，找出出现次数超过矩阵元素数一半的元素。

朴素的做法，直接统计出现次数(读取数据要用 `scanf`，用 `cin` 会超时)：

```cpp
#include <iostream>
#include <map>

using namespace std;

int main(int argc, char * const argv[])
{
    map<int, int> mp;

    int n = 0, m = 0;
    int num = 0;

    cin >> n >> m;
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            scanf("%d", &num);  // 用 cin 会超时
            ++(mp[num]);  // 记录每个元素出现次数
        }
    }

    int num_half_elems = n * m / 2;
    for (const auto &e : mp)
    {
        if (e.second > num_half_elems)  // 超过一半元素数，输出
        {
            cout << e.first << endl;
            break;
        }
    }

    return 0;
}
```

---

比较巧妙的算法：因为肯定会有一个数的个数超过总数的一半，那么可以用一个计数器 `count` 和一个临时变量 `color` 来实现对超过一半数目的颜色的筛选：

1. `count` 初始化为 0，`color` 初始化为 -1；
2. 读入新的颜色值 `new_color`，如果 `new_color == color`，`count` 加一。如果不一样，且 `count` 不为 0，则 `count` 减一；如果不一样，且 `count` 为 0，则 `color = new_color;`。
3. 不断循环步骤2，直到读入所有颜色值，最后输出 `color`。

这个方法怎么想到的？不妨假设只有两种颜色，那么其实上面的方法类似于“连连看”，只不过消去的是不同的元素（每次消去两个不一样的元素）。最后 `count` 中保存的实际上是 `dominant color` 超过其他颜色的数量。

注意只有当 `count` 为 0 时才会用 `new_color` 更新 `color` 的值，即 `color` 保存的是直到当前读入颜色为止的 dominant color 。
