#include <iostream> 
#include <vector>
#include <algorithm>
#include <utility>
#include <functional>
#include <numeric>

using namespace std;

const int k_INF = std::numeric_limits<int>::max();

void dijkstra(const vector<vector<pair<int, int>>> &graph, 
    int src, int dst, vector<int> &dists, vector<int> &costs, vector<int> &path)
{
    int num_vs = graph.size();
    dists.resize(num_vs);  // 记录当前顶点 src 到顶点 i 的最短路径长度
    costs.resize(num_vs);  // 记录当前顶点 src 到顶点 i 的最小花费
    vector<int> pre(num_vs);  // 记录当前顶点 src 到顶点 i 最短路径上 i 的前一个顶点

    vector<int> visited(num_vs, 0);
    visited[src] = 1;  // 访问起始顶点
    dists[src] = 0;
    costs[src] = 0;
    pre[src] = -1;

    // 初始化辅助数组
    for (int i = 0; i < num_vs; ++i)
    {
        if (i == src)
            continue;

        if (graph[src][i].first != k_INF)
        {
            dists[i] = graph[src][i].first;
            costs[i] = graph[src][i].second;
            pre[i] = src;
        }
        else
        {
            dists[i] = k_INF;
            costs[i] = k_INF;
        }
    }

    // 处理剩下 N - 1 个顶点
    for (int k = 0; k < num_vs - 1; ++k)
    {
        // 找到到当前已访问集合的距离最短的顶点
        int min_dist = k_INF;
        int u = -1;
        for (int i = 0; i < num_vs; ++i)
        {
            if (visited[i])
                continue;

            if (min_dist > dists[i])
            {
                min_dist = dists[i];
                u = i;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;  // 顶点 u 的最短路径已经找到

        // 以刚加入的顶点作为中介，更新剩余顶点信息
        for (int i = 0; i < num_vs; ++i)
        {
            if (visited[i] || graph[u][i].first == k_INF)
                continue;

            if (dists[i] > dists[u] + graph[u][i].first)
            {
                dists[i] = dists[u] + graph[u][i].first;
                costs[i] = costs[u] + graph[u][i].second;
                pre[i] = u;
            }
            else if (dists[i] == dists[u] + graph[u][i].first)  // 距离相同，考虑花费更小
            {
                if (costs[i] > costs[u] + graph[u][i].second)
                {
                    costs[i] = costs[u] + graph[u][i].second;
                    pre[i] = u;
                }
            }
        }
    }

    // src 到 dst 的最短路径上的顶点
    path.clear();
    while (dst != -1)
    {
        path.push_back(dst);
        dst = pre[dst];
    }
    std::reverse(path.begin(), path.end());
}

int main(int argc, char * const argv[])
{
    int N, M, S, D;
    cin >> N >> M >> S >> D;

    // pair format: <distance, cost>
    vector<vector<pair<int, int>>> graph(N, vector<pair<int, int>>(N, make_pair(k_INF, k_INF)));
    for (int i = 0; i < N; ++i)
    {
        graph[i][i].first = 0;
        graph[i][i].second = 0;
    }

    for (int i = 0; i < M; ++i)
    {
        int a, b;
        cin >> a >> b;
        cin >> graph[a][b].first >> graph[a][b].second;
        graph[b][a].first = graph[a][b].first;
        graph[b][a].second = graph[a][b].second;
    }

    vector<int> dists;
    vector<int> costs;
    vector<int> path;
    dijkstra(graph, S, D, dists, costs, path);

    for (int i = 0; i < path.size(); ++i)
    {
        cout << path[i] << " ";
    }
    cout << dists[D] << " " << costs[D] << endl;

    return 0;
}