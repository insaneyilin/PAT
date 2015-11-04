#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <stdio.h>
#include <limits.h>

using namespace std;

// 树节点定义
struct TreeNode
{
    TreeNode(int v) : val(v)
    {
        left = NULL;
        right = NULL;
    }

    int val;
    TreeNode *left, *right;
};

// 从先序遍历序列和中序遍历序列中构建一棵树
TreeNode* create_tree(
    const vector<int> &pre_order, int pre_start, int pre_end, 
    const vector<int> &in_order, int in_start, int in_end,
    const unordered_map<int, int> &h_inorder_pos)
{
    if (pre_start >= pre_end || in_start >= in_end)
        return NULL;
    
    int root_val = pre_order[pre_start];
    int root_inorder_pos = h_inorder_pos.at(root_val);
    int left_size = root_inorder_pos - in_start;

    TreeNode *root = new TreeNode(root_val);
    root->left = create_tree(
        pre_order, pre_start + 1, pre_start + left_size + 1, 
        in_order, in_start, root_inorder_pos, h_inorder_pos);
    root->right = create_tree(
        pre_order, pre_start + left_size + 1, pre_end, 
        in_order, root_inorder_pos + 1, in_end, h_inorder_pos);

    return root;
}

// 二叉树后序遍历，pred 为对节点的访问方法
template <class Predicate>
void post_order_traverse(TreeNode *root, Predicate pred)
{
    if (!root)
        return;

    post_order_traverse(root->left, pred);
    post_order_traverse(root->right, pred);
    pred(root);
}

int main(int argc, char * const argv[])
{
    int n;
    cin >> n;

    vector<int> pre_order;
    vector<int> in_order;
    stack<int> s;

    int x;
    string operation;

    while (cin >> operation)
    {
        if (operation == "Push")
        {
            cin >> x;
            pre_order.push_back(x);  // 将每次 Push 的节点保存到先序遍历序列
            s.push(x);
        }
        else  // Pop
        {
            in_order.push_back(s.top());  // 保存到中序遍历序列
            s.pop();
        }
    }

    // 用 Hash 表保存每个节点在中序遍历序列中的位置
    unordered_map<int, int> h_inorder_pos;
    for (int i = 0; i < in_order.size(); ++i)
    {
        h_inorder_pos[in_order[i]] = i;
    }

    // 构建树
    TreeNode *tree = create_tree(pre_order, 0, pre_order.size(), in_order, 0, in_order.size(), h_inorder_pos);

    vector<int> post_order;  // 后序遍历序列
    // 用 Lambda 表达式定义访问节点的方法
    auto print_node = [&post_order](TreeNode *node) {
        if (!node)
            return;
        post_order.push_back(node->val);
    };

    // 生成后序遍历序列
    post_order_traverse(tree, print_node);

    // 释放节点空间
    auto destroy_node = [](TreeNode *node) {
        if (!node)
            return;
        delete node;
        node = NULL;
    };

    // 后序遍历删除树
    post_order_traverse(tree, destroy_node);

    // 输出后序遍历序列
    for (int i = 0; i < post_order.size(); ++i)
    {
        cout << (i == 0 ? "" : " ") << post_order[i];
    }
    cout << endl;

    return 0;
}