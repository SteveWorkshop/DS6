// 6-1 Level-order Traversal (15 分).cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MaxTree 10 /* maximum number of nodes in a tree */
typedef int ElementType;

typedef struct TreeNode* Tree;
struct TreeNode {
    ElementType Element;
    Tree  Left;
    Tree  Right;
};

Tree BuildTree(ElementType* preorder, ElementType* inorder, int pre_l, int pre_r, int in_l, int in_r); /* details omitted */
void PrintNode(Tree NodePtr)
{
    printf(" %d", NodePtr->Element);
}

void Level_order(Tree T, void (*visit)(Tree ThisNode));

ElementType preorder[MaxTree + 1];
ElementType inorder[MaxTree + 1];

int main()
{
    freopen("1.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &preorder[i]);
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &inorder[i]);
    }
    Tree T = BuildTree(preorder, inorder, 0, n - 1, 0, n - 1);
    printf("Level-order:");
    Level_order(T, PrintNode);
    return 0;
}

/* Your function will be put here */

Tree BuildTree(ElementType* preorder, ElementType* inorder, int pre_l, int pre_r, int in_l, int in_r)
{
    if (pre_l > pre_r) { return NULL; }
    Tree root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->Element = preorder[pre_l];
    int k;
    for (k = in_l; k <= in_r; k++)
    {
        if (inorder[k] == preorder[pre_l]) { break; }
    }
    int numleft = k - in_l;
    root->Left = BuildTree(preorder, inorder, pre_l + 1, pre_l + numleft, in_l, k - 1);
    root->Right = BuildTree(preorder, inorder, pre_l + numleft + 1, pre_r, k + 1, in_r);
    return root;
}

struct TreeNode* que[5 * MaxTree + 1];
int head = 0, tail = 0;
void Level_order(Tree T, void (*visit)(Tree ThisNode))
{
    if (!T) { return; }
    que[tail] = T;
    tail++;
    while (head != tail)
    {
        struct TreeNode* p = que[head];
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
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
