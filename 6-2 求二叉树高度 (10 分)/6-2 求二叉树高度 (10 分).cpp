// 6-2 求二叉树高度 (10 分).cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
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

struct TNode* que[5 * MAXN + 1];
int head = 0, tail = 0;

BinTree CreatBinTree(ElementType* preorder, ElementType* inorder, int pre_l, int pre_r, int in_l, int in_r); /* 实现细节忽略？忽略你妈啊！ */
int GetHeight(BinTree BT);

BinTree CreatBinTree(ElementType* preorder, ElementType* inorder, int pre_l, int pre_r, int in_l, int in_r)
{
    if (pre_l > pre_r) { return NULL; }
    BinTree root = (struct TNode*)malloc(sizeof(struct TNode));
    root->Data = preorder[pre_l];
    int k;
    for (k = in_l; k <= in_r; k++)
    {
        if (inorder[k] == preorder[pre_l]) { break; }
    }
    int numleft = k - in_l;
    root->Left = CreatBinTree(preorder, inorder, pre_l + 1, pre_l + numleft, in_l, k - 1);
    root->Right = CreatBinTree(preorder, inorder, pre_l + numleft + 1, pre_r, k + 1, in_r);
    return root;
}

void InorderTraversal(BinTree BT)
{
    if (!BT) { return; }
    InorderTraversal(BT->Left);
    printf(" %c", BT->Data);
    InorderTraversal(BT->Right);
}

void PreorderTraversal(BinTree BT)
{
    if (!BT) { return; }
    printf(" %c", BT->Data);
    PreorderTraversal(BT->Left);
    PreorderTraversal(BT->Right);
}

void PostorderTraversal(BinTree BT)
{
    if (!BT) { return; }
    PostorderTraversal(BT->Left);
    PostorderTraversal(BT->Right);
    printf(" %c", BT->Data);
}

void PrintNode(BinTree NodePtr)
{
    printf(" %c", NodePtr->Data);
}

void Level_order(BinTree T, void (*visit)(BinTree ThisNode))
{
    if (!T) { return; }
    que[tail] = T;
    tail++;
    while (head != tail)
    {
        struct TNode* p = que[head];
        head++;
        visit(p);
        if (p->Left)
        {
            que[tail] = p->Left;
            tail++;
        }
        if (p->Right)
        {
            que[tail] = p->Right;
            tail++;
        }
    }
}

int main()
{
    freopen("1.txt", "r", stdin);
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
    for (int i = 0; i < n; i++) { printf(" %c", preorder[i]); }
    printf("\n----------------------\n");
    for (int i = 0; i < n; i++) { printf(" %c", inorder[i]); }
    printf("\n----------------------\n");
    BinTree BT = CreatBinTree(preorder, inorder, 0, n - 1, 0, n - 1);
    Level_order(BT, PrintNode);
    printf("\n----------------------\n");
    PreorderTraversal(BT);
    printf("\n----------------------\n");
    InorderTraversal(BT);
    printf("\n----------------------\n");
    PostorderTraversal(BT);
    printf("\n----------------------\n");
    printf("%d\n", GetHeight(BT));
    return 0;
}
/* 你的代码将被嵌在这里 */
#define MAX_OF_TWO(a,b) ((a) > (b)) ? (a) : (b)
int GetHeight(BinTree BT)
{
    if (BT == NULL) { return 0; }
    int lefthight = GetHeight(BT->Left);
    int rightheight = GetHeight(BT->Right);
    return (MAX_OF_TWO(lefthight, rightheight)) + 1;
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
