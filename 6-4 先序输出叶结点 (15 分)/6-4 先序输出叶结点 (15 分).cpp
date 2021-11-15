// 6-4 先序输出叶结点 (15 分).cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAXN 100010

typedef char ElementType;
typedef struct TNode* Position;
typedef Position BinTree;
struct TNode {
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

ElementType preorder[MAXN], inorder[MAXN];

BinTree __CreatBinTree(ElementType* preorder, ElementType* inorder, int pre_l, int pre_r, int in_l, int in_r)
{
    /* 道路千万条，安全第一条，行车不规范，亲人两行泪！！！！！ */
    if (pre_l > pre_r) { return NULL; }
    BinTree root = (struct TNode*)malloc(sizeof(struct TNode));
    root->Data = preorder[pre_l];
    int k;
    for (k = in_l; k <= in_r; k++)
    {
        if (inorder[k] == preorder[pre_l]) { break; }
    }
    int numleft = k - in_l;
    root->Left = __CreatBinTree(preorder, inorder, pre_l + 1, pre_l + numleft, in_l, k - 1);
    root->Right = __CreatBinTree(preorder, inorder, pre_l + numleft + 1, pre_r, k + 1, in_r);
    return root;
}

BinTree CreatBinTree(); /* 实现细节已被我补全 */

BinTree CreatBinTree()
{
    int n;
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; i++)
    {
        scanf("%c", &preorder[i]);
    }
    getchar();
    for (int i = 0; i < n; i++)
    {
        scanf("%c", &inorder[i]);
    }
    BinTree root = __CreatBinTree(preorder, inorder, 0, n - 1, 0, n - 1);
    return root;
}

void PreorderPrintLeaves(BinTree BT);

int main()
{
    freopen("1.txt", "r", stdin);
    BinTree BT = CreatBinTree();
    printf("Leaf nodes are:");
    PreorderPrintLeaves(BT);
    printf("\n");

    return 0;
}
/* 你的代码将被嵌在这里 */

void PreorderPrintLeaves(BinTree BT)
{
    if (!BT) { return; }
    if (!BT->Left && !BT->Right) { printf(" %c", BT->Data); }
    PreorderPrintLeaves(BT->Left);
    PreorderPrintLeaves(BT->Right);
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
