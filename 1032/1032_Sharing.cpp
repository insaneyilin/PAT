#include <iostream>
#include <string>
#include <map>

using namespace std;

struct Node
{
    Node() {}
    Node(int next_) : next(next_), flag(false) {}

    bool flag;  // �Ƿ��ڵ�һ�������г���
    int next;   // ��һ���ڵ��ַ
};

int main(int argc, char * const argv[])
{
    map<int, Node> nodes;  // �������нڵ㣬key Ϊ�ڵ��ַ

    int addrs_1, addrs_2;  // �����������ʼ��ַ
    int cur, next;         // �����������нڵ�
    //string info;

    int num_nodes = 0;    // �ڵ���

    //cin >> addrs_1 >> addrs_2 >> num_nodes;  // �� cin �ᳬʱ
    scanf("%d%d%d", &addrs_1, &addrs_2, &num_nodes);

	// �������нڵ�
    for (int i = 0; i < num_nodes; ++i)
    {
        //cin >> cur >> info >> next;  // �� cin �ᳬʱ
        scanf("%d%*s%d", &cur, &next);   // (%*s) ��ʾ�����ַ��������ã��ն�
        nodes[cur] = Node(next);
    }

	// ������һ����������нڵ�
    cur = addrs_1;
    while (cur != -1)
    {
        nodes[cur].flag = true;
        cur = nodes[cur].next;
    }

	// �����ڶ�����������нڵ�
	// ���ĳ���ڵ��ڵ�һ�������г��ֹ���˵����ʼ����������
    cur = addrs_2;
    while (cur != -1 && !nodes[cur].flag)
    {
        cur = nodes[cur].next;
    }

	// ������
    if (cur == -1)
        cout << -1 << endl;
    else
        printf("%05d\n", cur);

    return 0;
}