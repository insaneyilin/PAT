#include <iostream>
#include <vector>

using namespace std;

// 节点定义
struct Node
{
    Node() : level(0) {}

    int level;  // 当前节点的层级
    vector<int> children;  // 保存每个孩子节点的 ID
};

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

int main(int argc, char * const argv[])
{
    int n, m;

    Node nodes[100];  //  0 < n < 100，即 [1, 99]
    int leaf_count_by_level[100] = { 0 };  // 统计各层的叶子节点数。层数从 0 开始
    int max_level = 0;

    // 输入数据
    cin >> n >> m;
    for (int i = 0; i < m; ++i)
    {
        int id, k;
        int child_id;
        cin >> id >> k;
        for (int j = 0; j < k; ++j)
        {
            cin >> child_id;
            nodes[id].children.push_back(child_id);
        }
    }

    // 计算每个节点的 level
    calculate_level(nodes, 1, 0);  // 节点 `01` 的 level 为 0

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

    return 0;
}