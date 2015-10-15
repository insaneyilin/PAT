#include <iostream>
#include <string>
#include <map>

using namespace std;

struct Node
{
    Node() {}
    Node(int next_) : next(next_), flag(false) {}

    bool flag;  // 是否在第一个链表中出现
    int next;   // 下一个节点地址
};

int main(int argc, char * const argv[])
{
    map<int, Node> nodes;  // 保存所有节点，key 为节点地址

    int addrs_1, addrs_2;  // 两个链表的起始地址
    int cur, next;         // 用于输入所有节点
    //string info;

    int num_nodes = 0;    // 节点数

    //cin >> addrs_1 >> addrs_2 >> num_nodes;  // 用 cin 会超时
    scanf("%d%d%d", &addrs_1, &addrs_2, &num_nodes);

	// 输入所有节点
    for (int i = 0; i < num_nodes; ++i)
    {
        //cin >> cur >> info >> next;  // 用 cin 会超时
        scanf("%d%*s%d", &cur, &next);   // (%*s) 表示内容字符不起作用，空读
        nodes[cur] = Node(next);
    }

	// 遍历第一个链表的所有节点
    cur = addrs_1;
    while (cur != -1)
    {
        nodes[cur].flag = true;
        cur = nodes[cur].next;
    }

	// 遍历第二个链表的所有节点
	// 如果某个节点在第一个链表中出现过，说明开始公共部分了
    cur = addrs_2;
    while (cur != -1 && !nodes[cur].flag)
    {
        cur = nodes[cur].next;
    }

	// 输出结果
    if (cur == -1)
        cout << -1 << endl;
    else
        printf("%05d\n", cur);

    return 0;
}