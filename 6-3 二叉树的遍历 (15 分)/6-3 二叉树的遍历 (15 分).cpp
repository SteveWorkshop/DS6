// 6-3 二叉树的遍历 (15 分).cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAXN 10010

typedef char ElementType;
typedef struct TNode* Position;
typedef Position BinTree;
struct TNode {
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

ElementType preorder[MAXN], inorder[MAXN];

BinTree CreatBinTree(); /* 实现细节忽略 */
void InorderTraversal(BinTree BT);
void PreorderTraversal(BinTree BT);
void PostorderTraversal(BinTree BT);
void LevelorderTraversal(BinTree BT);

BinTree __CreatBinTree(ElementType* preorder, ElementType* inorder, int pre_l, int pre_r, int in_l, int in_r)
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
    root->Left = __CreatBinTree(preorder, inorder, pre_l + 1, pre_l + numleft, in_l, k - 1);
    root->Right = __CreatBinTree(preorder, inorder, pre_l + numleft + 1, pre_r, k + 1, in_r);
    return root;
}

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

int main()
{
    freopen("1.txt", "r", stdin);
    BinTree BT = CreatBinTree();
    printf("Inorder:");    InorderTraversal(BT);    printf("\n");
    printf("Preorder:");   PreorderTraversal(BT);   printf("\n");
    printf("Postorder:");  PostorderTraversal(BT);  printf("\n");
    printf("Levelorder:"); LevelorderTraversal(BT); printf("\n");
    return 0;
}
/* 你的代码将被嵌在这里 */

struct TNode* que[5 * MAXN + 1];
int head = 0, tail = 0;

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

void LevelorderTraversal(BinTree BT)
{
    if (!BT) { return; }
    que[tail] = BT;
    tail++;
    while (head != tail)
    {
        struct TNode* p = que[head];
        head++;
        printf(" %c", p->Data);
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

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
