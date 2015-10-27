#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <stdio.h>

using namespace std;

// 树节点定义
struct TreeNode
{
    TreeNode(int v_) : val(v_)
    {
        left = NULL;
        right = NULL;
    }

    int val;
    TreeNode *left, *right;
};

// 递归实现从后序遍历序列和中序遍历序列中建立树
static TreeNode *buildTree(vector<int>& postorder, int post_start, int post_end,
    vector<int>& inorder, int in_start, int in_end, const unordered_map<int, int> &h)
{
    if (post_end <= post_start || in_end <= in_start)
        return NULL;

    TreeNode *root = new TreeNode(postorder[post_end - 1]);
    int root_pos_inorder = h.at(root->val);
    int left_tree_size = root_pos_inorder - in_start;

    root->left = buildTree(postorder, post_start, post_start + left_tree_size, inorder, in_start, root_pos_inorder, h);
    root->right = buildTree(postorder, post_start + left_tree_size, post_end - 1, inorder, root_pos_inorder + 1, in_end, h);

    return root;
}

// 从后序遍历序列和中序遍历序列中建立树
TreeNode *buildTree(vector<int> &postorder, vector<int> &inorder)
{
    unordered_map<int, int> h;  // 用 Hash 表记录节点在中序遍历中的位置
    for (int i = 0; i < inorder.size(); ++i)
    {
        h[inorder[i]] = i;
    }

    return buildTree(postorder, 0, postorder.size(), inorder, 0, inorder.size(), h);
}

// 树的层次遍历
void level_order_traverse(TreeNode *root, vector<int> &res)
{
    if (root == NULL)
        return;

    queue<TreeNode*> q;
    q.push(root);

    res.clear();
    while (!q.empty())
    {
        auto t = q.front();
        q.pop();
        res.push_back(t->val);

        if (t->left)
            q.push(t->left);
        if (t->right)
            q.push(t->right);
    }
}

// 后序遍历删除一棵树
void deleteTree(TreeNode *root)
{
    if (root == NULL)
        return;

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
    root = NULL;
}

int main(int argc, char * const argv[])
{
    int n;
    cin >> n;

    vector<int> post_order(n);
    vector<int> in_order(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> post_order[i];
    }
    for (int i = 0; i < n; ++i)
    {
        cin >> in_order[i];
    }

    // 建树
    vector<int> result;
    TreeNode *tree = buildTree(post_order, in_order);

    // 层次遍历
    level_order_traverse(tree, result);

    // 释放空间
    deleteTree(tree);

    // 输出
    for (int i = 0; i < result.size(); ++i)
    {
        cout << (i == 0 ? "" : " ") << result[i];
    }
    cout << endl;

    return 0;
}