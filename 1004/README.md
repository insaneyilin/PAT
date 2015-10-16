# 1004. Counting Leaves

http://www.patest.cn/contests/pat-a-practise/1004

统计一棵树中的非叶子节点。

题目告诉了最多有 99 个节点，可以用一个数组保存所有节点：

```cpp
Node nodes[100];  // 1 到 99，数组下标为每棵树的 ID
```

树节点的定义：

```cpp
struct Node
{
    Node() : level(0) {}

    int level;  // 当前节点的层级
    vector<int> children;  // 保存每个孩子节点的 ID
};
```

节点输入完之后，我们遍历树来得到每个节点的层级：

```cpp
// 递归计算每个节点所在层数，DFS
void calculate_level(Node nodes[100], int id, int level)
{
    nodes[id].level = level;
    for (auto &child : nodes[id].children)
    {
        // 当前节点所有孩子节点的层数为 level + 1
        calculate_level(nodes, child, level + 1);
    }
}
```

最后遍历所有节点，统计每一层的叶子节点数，输出即可：

```cpp
// 统计每一层的叶子节点数
for (int i = 1; i <= n; ++i)
{
    int level = nodes[i].level;
    if (level > max_level)  // 更新最大层数
        max_level = level;

    // No children ==> Leaf
    if (nodes[i].children.size() == 0)
    {
        ++(leaf_count_by_level[level]);
    }
}

// 输出第 0 层到第 max_level 层中每一层的叶子节点数
for (int i = 0; i <= max_level; ++i)
{
    cout << (i > 0 ? " " : "") << leaf_count_by_level[i];
}
cout << endl;
```

---

这一题说不上难，但一开始我的思路不是很清楚，想用 `map` 来做，而且节点定义中孩子节点使用了指针，其实完全没有必要。既然节点数有限，而且每个节点通过其 ID 索引，完全可以开一个数组，通过 ID 访问孩子节点。

上面的代码使用 DFS 计算每个节点的层数；也可以使用 BFS，即层次遍历一层层统计叶子节点数。

把一棵树看成一个图（graph），从根节点开始进行 BFS：

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

void bfs(int root, const vector<vector<int>> &edges, vector<int> &result)
{
    queue<pair<int, int>> q;
    q.push(make_pair(root, 0));  // 根节点的 level 为 0

    int cur_level = 0;
    int cnt = 0;
    result.clear();

    while (!q.empty())
    {
        int node = q.front().first;
        int level = q.front().second;
        q.pop();

        if (level > cur_level)  // 到新的一层了
        {
            result.push_back(cnt);  // 添加上一层叶子数
            cnt = 0;  // 计数器清 0 
            cur_level = level;
        }

        // 当前节点是叶子节点
        if (edges[node].size() == 0)
        {
            ++cnt;
        }

        // 当前节点的相邻节点添加到队列中
        for (int i = 0; i < edges[node].size(); ++i)
        {
            q.push(make_pair(edges[node][i], cur_level + 1));  // 层数加 1
        }
    }
    result.push_back(cnt);  // 最后一层的叶子数
}

int main(int argc, char * const argv[])
{
    int n, m;  // 总节点数，非叶子节点数
    vector<vector<int>> edges;  // 保存所有有向边

    // 输入数据
    cin >> n >> m;
    edges.resize(n + 1);  // 根节点为 01，下标从 1 开始
    for (int i = 0; i < m; ++i)
    {
        int a, k;
        cin >> a >> k;
        for (int j = 0; j < k; ++j)
        {
            int b;
            cin >> b;
            edges[a].push_back(b);  // 有向边
        }
    }

    // 层次遍历（BFS）
    vector<int> res;
    bfs(1, edges, res);

    // 输出结果
    for (int i = 0; i < res.size(); ++i)
    {
        cout << (i > 0 ? " " : "") << res[i];
    }
    cout << endl;

    return 0;
}
```