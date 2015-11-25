#include <iostream> 
#include <vector>
#include <functional>

#include <stdio.h>

using namespace std;

// BST 节点定义
struct BSTNode
{
    BSTNode(int _v) : val(_v) 
    {
        lchild = NULL;
        rchild = NULL;
    }

    int val;
    BSTNode *lchild, *rchild;
};

// 向 BST 中插入节点
template <typename Pred>
void insert_bst(BSTNode *&root, int val, Pred _pred)
{
    if (root == NULL)
    {
        root = new BSTNode(val);
        return;
    }

    if (_pred(val, root->val))
    {
        insert_bst(root->lchild, val, _pred);
    }
    else
    {
        insert_bst(root->rchild, val, _pred);
    }
}

// 从先序遍历序列创建 BST
template <typename Pred>
BSTNode* create_bst_from_preorder(const vector<int> &preorder, Pred _pred)
{
    BSTNode *root = NULL;
    for (size_t i = 0; i < preorder.size(); ++i)
    {
        insert_bst(root, preorder[i], _pred);
    }

    return root;
}

// 先序遍历
void get_preorder(BSTNode *root, vector<int> &preorder)
{
    if (root == NULL)
    {
        return;
    }

    preorder.push_back(root->val);
    get_preorder(root->lchild, preorder);
    get_preorder(root->rchild, preorder);
}

// 后序遍历
void get_postorder(BSTNode *root, vector<int> &postorder)
{
    if (root == NULL)
    {
        return;
    }

    get_postorder(root->lchild, postorder);
    get_postorder(root->rchild, postorder);
    postorder.push_back(root->val);
}

// 释放整棵 BST 的空间
void destroy_bst(BSTNode *root)
{
    if (root == NULL)
    {
        return;
    }

    destroy_bst(root->lchild);
    destroy_bst(root->rchild);
    delete root;
    root = NULL;
}

int main(int argc, char * const argv[])
{
    int N;
    cin >> N;
    vector<int> nums(N, 0);
    for (int i = 0; i < N; ++i)
    {
        cin >> nums[i];
    }

    // 判断是否为 BST
    vector<int> preorder;
    BSTNode *bst = create_bst_from_preorder(nums, [](int a, int b) {
        return a < b;
    });
    get_preorder(bst, preorder);
    
    if (preorder == nums)
    {
        cout << "YES\n";
        vector<int> postorder;
        get_postorder(bst, postorder);

        for (size_t i = 0; i < postorder.size(); ++i)
        {
            cout << (i == 0 ? "" : " ");
            cout << postorder[i];
        }
        cout << endl;

        destroy_bst(bst);
        return 0;
    }
    destroy_bst(bst);

    // 判断是否为 mirror BST
    vector<int> preorder_mirror;
    BSTNode *bst_mirror = create_bst_from_preorder(nums, [](int a, int b) {
        return a >= b;
    });
    get_preorder(bst_mirror, preorder_mirror);
    
    if (preorder_mirror == nums)
    {
        cout << "YES\n";
        vector<int> postorder;
        get_postorder(bst_mirror, postorder);

        for (size_t i = 0; i < postorder.size(); ++i)
        {
            cout << (i == 0 ? "" : " ");
            cout << postorder[i];
        }
        cout << endl;

        destroy_bst(bst_mirror);
        return 0;
    }
    destroy_bst(bst_mirror);

    // 不是 BST 和 mirror BST
    cout << "NO\n";

    return 0;
}