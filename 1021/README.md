# 1021. Deepest Root

http://www.patest.cn/contests/pat-a-practise/1021

一个没有环的图可以看成是一棵树，判断以图中哪个顶点为根时树的深度最大。

首先判断图是否连通，利用并查集实现。然后以每个顶点为根节点用 DFS 求出深度，并记录最大深度。最后输出深度等于最大深度的对应节点。时间复杂度 O(n^2)。

```cpp
// 在 PAT 上提交出现了 "段错误"，可能是 DFS 使用了递归导致栈空间用完了
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>
#include <stdio.h>

using namespace std;

// 并查集中获取根节点，使用路径压缩
int get_root_uf(int x, vector<int> &uf)
{
    int root = x;

    // 先找出根节点
    while (root != uf[root])
    {
        root = uf[root];
    }

    // 路径压缩
    while (x != root)
    {
        int tmp = uf[x];
        uf[x] = root;
        x = tmp;
    }

    // 返回根节点
    return root;
}

// 合并两个集合
void union_two_set(int x, int y, vector<int> &uf)
{
    x = get_root_uf(x, uf);
    y = get_root_uf(y, uf);

    uf[y] = x;
}

// 以顶点 v 为根对图进行 DFS，求出 depth。
int dfs(int v, int parent, vector<vector<int>> &adj_list)
{
    int d = 0;
    for (int i = 0; i < adj_list[v].size(); ++i)
    {
        if (adj_list[v][i] != parent)
        {
            // 最大子树深度
            d = max(d, dfs(adj_list[v][i], v, adj_list));
        }
    }

    // 当前顶点深度 = 最大子树深度 + 1
    return d + 1;
}

int main(int argc, char * const argv[])
{
    int n;
    cin >> n;
    
    vector<vector<int>> adj_list(n + 1);  // 顶点下标从 1 开始

    for (int i = 0; i < n; ++i)
    {
        int a, b;
        cin >> a >> b;
        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }

    // 初始化并查集
    vector<int> uf(n + 1);
    std::iota(uf.begin(), uf.end(), 0);  // 每个节点都是根节点

    // 根据各个顶点的连接情况构建并查集
    for (int u = 1; u <= n; ++u)
    {
        for (int j = 0; j < adj_list[u].size(); ++j)
        {
            int v = adj_list[u][j];

            union_two_set(u, v, uf);
        }
    }

    // 保存并查集中的根节点
    set<int> root_nodes;
    for (int i = 1; i <= n; ++i)
    {
        root_nodes.insert(get_root_uf(i, uf));
    }

    // 根节点数大于 1 => 有多个连通分支
    if (root_nodes.size() > 1)
    {
        cout << "Error: " << root_nodes.size() << " components\n";
        return 0;
    }

    // 记录以每个顶点为根节点时的深度
    vector<int> depths(n + 1, 0);
    int max_depth = 0;
    for (int i = 1; i <= n; ++i)
    {
        depths[i] = dfs(i, -1, adj_list);
        max_depth = max(max_depth, depths[i]);  // 最大深度
    }

    // 输出深度等于最大深度的对应顶点
    for (int i = 1; i <= n; ++i)
    {
        if (depths[i] == max_depth)
        {
            cout << i << endl;
        }
    }

    return 0;
}
```

另一种比较巧妙的方法时间复杂度为 O(n)，首先从任意一个点 DFS（BFS 也可以），得到距离这个点最远的一些点，再从这些点中任取一个进行 DFS，记录所有最远点。两次 DFS 找出的所有最远点就是所有 deepest roots。

这个方法很巧妙，要一下想到不太容易。先介绍两个概念：

- 直径：树的 deepest root 到最远叶子节点的路径称为直径（即图中距离最长的路径）
- 端点：直径的两个端点，即 deepest root 和最远叶子节点

很明显直径的端点一定是 deepest root 。

有下面两个结论（注意这里已经假设图一定是连通的了）

### 结论1：从任意一个点 DFS 得到的最远点都是直径的端点

> 证明：任意选一点 A，DFS 查找距离 A 最远的点，遍历时一定会经过图的某直径上的一点 B，从 B 出发找到的某个最远点 C 是直径的一个端点，则 C 一定是从 A 出发的一个最远点。反证法，设有一点 D，A -> D 不经过任何直径，且 length(A->D) > length(A->C)，则 length(B->A->D) > length(B->C)，即我们可以从 C 所在的直径上构造出经过 D 的比原直径更长的直径，与 C 是直径上的端点矛盾（原直径不是直径）。

### 结论2：连通图的所有直径都相交于一点（或者公共路径上的几点），于是从任意一个端点出发找到的最远点一定也是端点。

> 如果两条直径不相交，而现在图上任意两点之间肯定连通，则从两个直径上可以选取两点连接以组成更长的直径；如果三条直径相交于不同的两点，可以根据相交截断的长度组合出更长的直径。

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <numeric>
#include <stdio.h>

using namespace std;

// 并查集中获取根节点，使用路径压缩
int get_root_uf(int x, vector<int> &uf)
{
    int root = x;

    // 先找出根节点
    while (root != uf[root])
    {
        root = uf[root];
    }

    // 路径压缩
    while (x != root)
    {
        int tmp = uf[x];
        uf[x] = root;
        x = tmp;
    }

    // 返回根节点
    return root;
}

// 合并两个集合
void union_two_set(int x, int y, vector<int> &uf)
{
    x = get_root_uf(x, uf);
    y = get_root_uf(y, uf);

    uf[y] = x;
}

// 从顶点 src 开始进行 BFS，depths 保存从 src 开始遍历时每个顶点的深度
int bfs(int src, vector<int> &depths, const vector<vector<int>> &adj_list)
{
    vector<int> visited(adj_list.size(), 0);
    depths.resize(adj_list.size(), 0);

    queue<int> q;
    q.push(src);
    visited[src] = 1;
    depths[src] = 1;

    int max_depth = depths[src];

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int j = 0; j < adj_list[u].size(); ++j)
        {
            int v = adj_list[u][j];
            if (!visited[v])
            {
                visited[v] = 1;
                q.push(v);

                depths[v] = depths[u] + 1;
                max_depth = max(max_depth, depths[v]);
            }
        }
    }

    return max_depth;  // 返回最大深度
}

int main(int argc, char * const argv[])
{
    int n;
    cin >> n;
    
    vector<vector<int>> adj_list(n + 1);  // 顶点下标从 1 开始

    for (int i = 0; i < n; ++i)
    {
        int a, b;
        cin >> a >> b;
        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }

    // 初始化并查集
    vector<int> uf(n + 1);
    std::iota(uf.begin(), uf.end(), 0);  // 每个节点都是根节点

    // 根据各个顶点的连接情况构建并查集
    for (int u = 1; u <= n; ++u)
    {
        for (int j = 0; j < adj_list[u].size(); ++j)
        {
            int v = adj_list[u][j];

            union_two_set(u, v, uf);
        }
    }

    // 保存并查集中的根节点
    set<int> root_nodes;
    for (int i = 1; i <= n; ++i)
    {
        root_nodes.insert(get_root_uf(i, uf));
    }

    // 根节点数大于 1 => 有多个连通分支
    if (root_nodes.size() > 1)
    {
        cout << "Error: " << root_nodes.size() << " components\n";
        return 0;
    }

    // 下面进行两次 BFS

    set<int> ans;  // 保存 deepest roots
    vector<int> depths(n + 1, 0);  // 保存每次 BFS 后每个顶点的深度
    int max_depth = bfs(1, depths, adj_list);  // 第一次 BFS
    
    // 保存第一次 BFS 后的最远点作为 deepest roots
    for (int i = 1; i <= n; ++i)
    {
        if (depths[i] == max_depth)
        {
            ans.insert(i);
        }
    }

    // 第二次 BFS，此时 max_depth 为图的直径长度
    max_depth = bfs(*(ans.begin()), depths, adj_list);

    // 保存第二次 BFS 后的最远点作为 deepest roots
    for (int i = 1; i <= n; ++i)
    {
        if (depths[i] == max_depth)
        {
            ans.insert(i);
        }
    }
    
    // 输出结果
    for (const auto &v : ans)
    {
        cout << v << endl;
    }

    return 0;
}
```
