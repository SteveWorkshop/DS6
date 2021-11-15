// 6-5 中序线索化二叉树及遍历 (10 分).cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

typedef struct BiThrNode
{
    char data;
    struct BiThrNode* lchild, * rchild;
    int LTag, RTag;
}BiThrNode, * BiThrTree;


BiThrNode* pre = new BiThrNode;

void CreateBiTree(BiThrTree& T)
{
    /*
        单纯的一串先序遍历序列无法确定二叉树（因为不知道什么时候到达树叶）
        因此前面建树都是给了两种不同顺序的遍历序列
        但是如果把先序遍历过程中的空指针也写出来那么先序遍历本身就可以确定二叉树
        请看下面的代码：
    */
    char ch;
    std::cin >> ch;
    if (ch == '#') { T = nullptr; }
    else
    {
        T = new BiThrNode;
        T->data = ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
}

void InThreading(BiThrTree p);
void InOrderTraverse_Thr(BiThrTree T);

int main()
{
    pre->RTag = 1;
    pre->rchild = NULL;
    BiThrTree tree;
    CreateBiTree(tree);
    InThreading(tree);
    InOrderTraverse_Thr(tree);
    return 0;
}
/* 请在这里填写答案 */

#define POINTER 0
#define THREAD 1
#define EDG 2

void f(BiThrTree p)
{
    if (!p) { return; }
    f(p->lchild);
    p->LTag = p->RTag = POINTER;
    if (!pre->rchild)
    {
        pre->RTag = THREAD;
        pre->rchild = p;
    }
    if (!p->lchild)
    {
        p->LTag = THREAD;
        p->lchild = pre;
    }
    pre = p;
    f(p->rchild);
}

void InThreading(BiThrTree p)
{ 
    pre->LTag = POINTER;
    pre->RTag = THREAD;
    pre->lchild = p;
    f(p);
    pre->rchild = nullptr;
    pre->RTag = EDG;
}

void InOrderTraverse_Thr(BiThrTree T)
{
    while (T != nullptr)
    {
        while (T->LTag == POINTER) { T = T->lchild; }
        std::cout << T->data;
        while (T->RTag == THREAD && T->rchild != nullptr) 
        { 
            T = T->rchild;
            std::cout << T->data;
        } 
        T = T->rchild;
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
