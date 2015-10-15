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