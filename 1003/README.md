# 1003. Emergency

http://www.patest.cn/contests/pat-a-practise/1003

一张图，各边都有权值而且每个点也有权值，求出给定两点之间最短路的条数并输出 **最大** 的最短路径点权值和。即求最短路的条数，多条最短路输出最大的那个点权值和。

图论的题我不太会做，这题自己做了很久，最后也是参考了网上其他人的解法。主要还是基本算法不熟悉，如果对 Dijkstra 算法的思想真正理解了，很容易修改代码实现。

### Dijkstra 算法

原始 Dijkstra 只考虑距离信息，本题要考虑两个额外信息，点权值和最短路条数。

```cpp
// 使用 Dijkstra 算法

#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

void dijkstra(int src, int dst, const vector<vector<int>> &graph, const vector<int> &teams)
{   
    int num_vs = graph.size();
    vector<int> visited(num_vs, 0);  // 标记每个顶点的最短路是否已经找到
    vector<int> min_dists(num_vs, INT_MAX);   // src 到每个顶点的最短距离
    vector<int> max_teams(num_vs, 0);   // src 到每个顶点的最大救援队数量
    vector<int> cnts_pathes(num_vs, 0);  // src 到每个顶点的最短路数量

    // 初始化 src 顶点信息
    min_dists[src] = 0;
    max_teams[src] = teams[src];
    cnts_pathes[src] = 1;

    while (true)
    {
        // 找当前到 src 顶点距离最短的顶点（第一次一定是 src 顶点自己）
        int t = -1;
        int min_d = INT_MAX;
        for (int j = 0; j < num_vs; ++j)
        {
            if (visited[j] == 0 && min_dists[j] < min_d)
            {
                t = j;
                min_d = min_dists[j];
            }
        }

        // 找不到，说明所有顶点都已经访问过，退出
        if (t == -1)
            break;;

        visited[t] = 1;  // 标记最短路已经找到

        // 如果到 dst 顶点的最短路已经找到，退出
        if (t == dst)
            break;

        // 以新找到的顶点 t 为中介，更新其余顶点
        for (int j = 0; j < num_vs; ++j)
        {
            // 已访问或者不存在从 t 到 j 的边，跳过本次迭代
            if (visited[j] == 1 || graph[t][j] == INT_MAX)
                continue;

            // 以 t 为中介使得距离减小，更新到 src 的最短距离
            if (min_dists[t] + graph[t][j] < min_dists[j])
            {
                min_dists[j] = min_dists[t] + graph[t][j];
                max_teams[j] = max_teams[t] + teams[j];  // 注意额外信息
                cnts_pathes[j] = cnts_pathes[t];  // src 到 j 的最短路径数等于 src 到 t 的最短路径数
                                                  // 因为只是增加了一条边 t->j
            }
            // 距离不变，最短距离信息不需要更新，但要更新额外信息
            else if (min_dists[t] + graph[t][j] == min_dists[j])
            {
                cnts_pathes[j] += cnts_pathes[t];  // 最短路径数更新
                if (max_teams[j] < max_teams[t] + teams[j])  // 更新最大救援队数
                {
                    max_teams[j] = max_teams[t] + teams[j];
                }
            }
        }
    }

    // 输出结果
    cout << cnts_pathes[dst] << " " << max_teams[dst] << endl;
}

int main(int argc, char * const argv[])
{
    int num_vertices = 0;
    int num_edges = 0;
    int src = 0;
    int dst = 0;

    cin >> num_vertices >> num_edges >> src >> dst;

    vector<vector<int>> graph(num_vertices, vector<int>(num_vertices, INT_MAX));
    vector<int> rescue_teams(num_vertices, 0);

    for (int i = 0; i < num_vertices; ++i)
    {
        cin >> rescue_teams[i];
    }

    int v1, v2, w;
    for (int i = 0; i < num_edges; ++i)
    {
        cin >> v1 >> v2 >> w;
        graph[v1][v2] = graph[v2][v1] = w;
    }

    // Dijkstra 最短路算法
    dijkstra(src, dst, graph, rescue_teams);

    return 0;
}

```

---

### DFS 回溯搜索

```cpp
#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

/**
 * @brief DFS 回溯搜索
 *
 * @param [in] cur 当前访问顶点
 * @param [in] dst 目标顶点
 * @param [in] dist 当前路径距离
 * @param [in] num_teams 当前救援队数量
 *
 * @param [inout] min_dist 记录最短路径长度
 * @param [inout] max_teams 记录最大救援队数量
 * @param [inout] cnt 记录最短路径数量
 *
 * @param [in] visited 标记每个顶点访问情况
 * @param [in] graph 图的邻接矩阵
 * @param [in] teams 每个顶点的权值（救援队数量）
 */
void dfs(int cur, int dst, int dist, int num_teams, 
    int &min_dist, int &max_teams, int &cnt, 
    vector<int> &visited, 
    const vector<vector<int>> &graph, const vector<int> &teams)
{
    if (cur == dst)
    {
        if (dist < min_dist)
        {
            cnt = 1;
            min_dist = dist;
            max_teams = num_teams;
        }
        else if (dist == min_dist)
        {
            ++cnt;
            if (max_teams < num_teams)
            {
                max_teams = num_teams;
            }
        }

        return;
    }

    if (dist > min_dist)  // 剪枝
        return;

    for (int i = 0; i < visited.size(); ++i)
    {
        if (visited[i] == 0 && graph[cur][i] != INT_MAX)
        {
            // 回溯法
            // 这样做的目的是为了防止逆向查找，比如从 A 与 B 连接，那么从 A 查到 B 之后，
            // 从 B 开始查找时，不会再次回到 A （因为 visited[A] == 1）；
            // 但是当从 A 查找完所有孩子后就要撤销 A 的标记(visited[A] = 0)，这样其他查找才能正常进行。
            visited[i] = 1;
            dfs(i, dst, 
                dist + graph[cur][i], num_teams + teams[i], 
                min_dist, max_teams, cnt, 
                visited, graph, teams);
            visited[i] = 0;
        }
    }
}

int main(int argc, char * const argv[])
{
    int num_vertices = 0;
    int num_edges = 0;
    int src = 0;
    int dst = 0;

    cin >> num_vertices >> num_edges >> src >> dst;

    vector<vector<int>> graph(num_vertices, vector<int>(num_vertices, INT_MAX));
    vector<int> rescue_teams(num_vertices, 0);

    for (int i = 0; i < num_vertices; ++i)
    {
        cin >> rescue_teams[i];
    }

    int v1, v2, w;
    for (int i = 0; i < num_edges; ++i)
    {
        cin >> v1 >> v2 >> w;
        graph[v1][v2] = graph[v2][v1] = w;
    }

    int min_dist = INT_MAX; 
    int max_teams = 0; 
    int cnt = 0;
    vector<int> visited(num_vertices, 0);

    dfs(src, dst, 
        0, rescue_teams[src], 
        min_dist, max_teams, cnt, 
        visited, graph, rescue_teams);

    cout << cnt << " " << max_teams << endl;

    return 0;
}
```