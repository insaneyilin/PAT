# 1013. Battle Over Cities

http://www.patest.cn/contests/pat-a-practise/1013

给出一个图，问去掉某个顶点后为了使剩下的顶点可以连通需要增加多少条边。

只需要考虑去掉该顶点后图中有多少个连通分支，需要增加的边数为 `连通分支数 - 1`。

可以利用并查集来实现，注意要使用 **路径压缩** 。

```cpp
#include <iostream>
#include <vector>
#include <set>
#include <stdio.h>

using namespace std;

// 并查集查找根节点，使用路径压缩
int find_root_uf(int x, vector<int> &uf)
{
    // 查找根节点，记录在 root 中
    int root = x;
    while (root != uf[root])
    {
        root = uf[root];
    }

    // 非递归路径压缩操作
    int p = x;
    while (p != root)
    {
        int t = uf[p];  // t 暂存 p 的父节点
        uf[p] = root;   // p 的父节点改为 root
        p = t;          // p 移到其原父节点
    }

    return root;
}

// 合并两个集合
void union_two_set(int x, int y, vector<int> &uf)
{
    int a = find_root_uf(x, uf);
    int b = find_root_uf(y, uf);
    uf[a] = b;
}

int main(int argc, char * const argv[])
{
    // n -- number of city
    // m -- number of edge
    // k -- number of query
    int n, m, k;
    cin >> n >> m >> k;

    // 边的邻接表表示； edges[u][j] 表示与顶点 u 相邻的一个顶点 v
    vector<vector<int>> edges(n + 1);

    for (int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    for (int i = 0; i < k; ++i)
    {
        int q;
        cin >> q;

        // Init uf
        vector<int> uf(n + 1);
        for (int i = 1; i <= n; ++i)  // 注意本题顶点标号从 1 开始
        {
            uf[i] = i;
        }

        for (int u = 1; u <= n; ++u)
        {
            for (int j = 0; j < edges[u].size(); ++j)
            {
                int v = edges[u][j];
                if (u != q && v != q)  // 忽略与 q 相邻的边
                {
                    // Union two set
                    union_two_set(u, v, uf);
                }
            }
        }

        // 保存所有根节点
        set<int> root_nodes;
        for (int u = 1; u <= n; ++u)
        {
            if (u == q)  // Ignore node 'q'
                continue;

            root_nodes.insert(find_root_uf(u, uf));
        }
        cout << root_nodes.size() - 1 << endl;  // 连通分支数减一
    }

    return 0;
}
```
