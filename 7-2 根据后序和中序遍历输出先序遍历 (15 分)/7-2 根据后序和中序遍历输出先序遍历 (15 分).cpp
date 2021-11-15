// 7-2 根据后序和中序遍历输出先序遍历 (15 分).cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

typedef int ElemType;

struct Node {
    ElemType data;
    Node* left;
    Node* right;
};

typedef Node* BTree, * Pointer;

const int N = 1e5 + 10;

ElemType postorder[N];
ElemType inorder[N];

BTree unseralizeBTree(ElemType* postorder, ElemType* inorder, int post_l, int post_r, int in_l, int in_r)
{
    if (post_l > post_r) { return nullptr; }
    Pointer root = new Node;
    root->data = postorder[post_r];
    int k;
    for (k = in_l; k <= in_r; k++)
    {
        if (postorder[post_r] == inorder[k]) { break; }
    }
    int numleft = k - in_l;
    root->left = unseralizeBTree(postorder, inorder, post_l, post_l + numleft - 1, in_l, k - 1);
    root->right = unseralizeBTree(postorder, inorder, post_l + numleft, post_r - 1, k + 1, in_r);
    return root;
}

void preOrderPrint(BTree root, int n)
{
    static int cnt = 0;
    if (root == nullptr) { return; }
    std::cout << root->data;
    cnt++;
    if (cnt < n) { std::cout << " "; }
    preOrderPrint(root->left, n);
    preOrderPrint(root->right, n);
}

int main()
{
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        std::cin >> postorder[i];
    }
    for (int i = 0; i < n; i++)
    {
        std::cin >> inorder[i];
    }
    BTree root = unseralizeBTree(postorder, inorder, 0, n - 1, 0, n - 1);
    std::cout << "Preorder: ";
    preOrderPrint(root, n);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
