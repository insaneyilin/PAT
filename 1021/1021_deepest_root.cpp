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