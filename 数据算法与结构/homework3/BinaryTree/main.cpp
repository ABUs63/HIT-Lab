#include <iostream>
#include <cstring>
#define MAX 11

using namespace std;

typedef struct node* BTREE;
struct node {
    struct node *lchild;
    struct node *rchild;
    char data;
    int num;
};
struct celltype{
    BTREE element;
    struct celltype *next;
};
struct Queue{
    struct celltype *Front;
    struct celltype *Rear;
};
struct Stack{
    BTREE data[MAX];
    int top;
};
bool IsEmpty(BTREE BT);//树是否为空
BTREE Lchild(BTREE BT);//返回左子树
BTREE Rchild(BTREE BT);//返回右子树
char Data(BTREE BT);//返回树的根结点的值
BTREE Create(char ch,BTREE x,BTREE y);//创建树结点
void CreateBT(BTREE &BT);//cin方法输入树的值
void PreOrder(BTREE BT,string *t);//先序遍历
void InOrder(BTREE BT,string *t);//中序遍历
void PostOrder(BTREE BT,string *t);//后序遍历
void LeverOrder(BTREE BT,string *t);//层序遍历
void MakeNullQueue(Queue &Q);//新建队列
bool EmptyQueue(Queue Q);////队列是否为空
BTREE Front(Queue Q);//返回队首
void EnQueue(BTREE x,Queue &Q);//入队
void DeQueue(Queue &Q);//出队
void NoPreOrder(BTREE BT,string *t);//非递归先序遍历
void NoInOrder(BTREE BT,string *t);//非递归中序遍历
void NoPostOrder(BTREE BT,string *t);//非递归后序遍历
int GetMaxWidth(BTREE BT);//返回二叉树最大宽度
bool IsCompleteBTree(BTREE BT);//是否为完全二叉树
void MakeNullStack(Stack &s);//新建栈
bool EmptyStack(Stack s);//栈是否为空
BTREE Top(Stack s);//返回栈顶元素
void Pop(Stack &s);//出栈
void Push(BTREE x,Stack &s);//入栈

int main()
{
    string preorder,inorder,postorder,levelorder,nopreorder,noinorder,nopostorder;//保存相应序列方法的访问序列
    /*方法1创建:
    BTREE A,B,C,D,E,F,G,H,I,J,K,L,M,N,O;
    H=Create('H',NULL,NULL);
    I=Create('I',NULL,NULL);
    J=Create('J',NULL,NULL);
    K=Create('K',NULL,NULL);
    L=Create('L',NULL,NULL);
    M=Create('M',NULL,NULL);
    N=Create('N',NULL,NULL);
    O=Create('O',NULL,NULL);

    D=Create('D',H,I);
    E=Create('E',J,K);
    F=Create('F',L,M);
    G=Create('G',N,O);


    B=Create('B',D,E);
    C=Create('C',F,G);

    A=Create('A',B,C);
    */

    BTREE A=NULL;//方法2创建
    CreateBT(A);
    cout<<"先序遍历:"<<endl;
    PreOrder(A,&preorder);
    cout<<preorder;
    cout<<"\n中序遍历:"<<endl;
    InOrder(A,&inorder);
    cout<<inorder;
    cout<<"\n后序遍历:"<<endl;
    PostOrder(A,&postorder);
    cout<<postorder;
    cout<<"\n层次遍历:"<<endl;
    LeverOrder(A,&levelorder);
    cout<<levelorder;
    cout<<"\n非递归先序遍历"<<endl;
    NoPreOrder(A,&nopreorder);
    cout<<nopreorder;
    cout<<"\n非递归中序遍历"<<endl;
    NoInOrder(A,&noinorder);
    cout<<noinorder;
    cout<<"\n非递归后序遍历"<<endl;
    NoPostOrder(A,&nopostorder);
    cout<<nopostorder;
    cout<<"\n该二叉树最大的宽度为:"<<GetMaxWidth(A)<<endl;
    bool result=IsCompleteBTree(A);
    cout<<"是否是完全二叉树:"<<endl;
    if(result)
    {
        cout<<"是";
    }
    else
    {
        cout<<"不是";
    }
    return 0;
}
bool IsEmpty(BTREE BT)
{
    if(BT==NULL)
    {
        return true;
    }
    return false;
}
BTREE Lchild(BTREE BT)
{
    if(BT->lchild!=NULL)//非空返回左子树
    {
        return BT->lchild;
    }
    else
    {
        return NULL;
    }
}
BTREE Rchild(BTREE BT)
{
    if(BT->rchild!=NULL)//非空返回右子树
    {
        return BT->rchild;
    }
    else
    {
        return NULL;
    }
}
char Data(BTREE BT)
{
    return BT->data;
}
BTREE Create(char ch,BTREE x,BTREE y)//创建树结点
{
    BTREE T=new node;
    T->data=ch;
    T->lchild=x;
    T->rchild=y;
    return T;
}
void CreateBT(BTREE &BT)//cin方法输入树的创建过程
{
    char ch;
    cin>>ch;
    if(ch=='#')
    {
        BT=NULL;
    }
    else
    {
        BT=new node;
        BT->data=ch;
        CreateBT(BT->lchild);
        CreateBT(BT->rchild);
    }
}
void PreOrder(BTREE BT,string *t)//递归先序遍历
{
    if(IsEmpty(BT)==false)
    {
        *t=*t+Data(BT);
        cout<<Data(BT)<<"  ";
        PreOrder(Lchild(BT),t);
        PreOrder(Rchild(BT),t);
    }
}
void InOrder(BTREE BT,string *t)//递归中序遍历
{
    if(IsEmpty(BT)==false)
    {
        InOrder(Lchild(BT),t);
        *t=*t+Data(BT);
        cout<<Data(BT)<<"  ";
        InOrder(Rchild(BT),t);
    }
}
void PostOrder(BTREE BT,string *t)//递归后序遍历
{
    if(IsEmpty(BT)==false)
    {
        PostOrder(Lchild(BT),t);
        PostOrder(Rchild(BT),t);
        *t=*t+Data(BT);
        cout<<Data(BT)<<"  ";
    }
}
void LeverOrder(BTREE BT,string *t)//层序遍历
{
    Queue Q;
    BTREE T;
    MakeNullQueue(Q);//新建队列
    T=BT;
    if(!IsEmpty(T))//树非空入队
    {
        EnQueue(T,Q);
    }
    while(!EmptyQueue(Q))
    {
        T=Front(Q);//为后续子树入队保留根结点
        *t=*t+Data(T);
        cout<<Data(T)<<"  ";
        DeQueue(Q);
        if(Lchild(T))//左子树非空入队
        {
            EnQueue(Lchild(T),Q);
        }
        if(Rchild(T))//右子树非空入队
        {
            EnQueue(Rchild(T),Q);
        }
    }
}
void NoPreOrder(BTREE BT,string *order)//非递归先序遍历
{
    Stack s;
    BTREE t;
    MakeNullStack(s);//新建栈
    t=BT;
    while(!IsEmpty(t)||!EmptyStack(s))//树非空或栈非空
    {
        if(!IsEmpty(t))//通过条件语句,进行持续根结点访问且将左子树压入栈,便后续右子树访问
        {
            *order=*order+Data(t);
            cout<<Data(t)<<"  ";
            Push(t,s);
            t=Lchild(t);
        }
        else//访问栈顶结点右子树
        {
            t=Top(s);
            Pop(s);
            t=Rchild(t);
        }
    }
}
void NoInOrder(BTREE BT,string *order)//非递归中序遍历
{
    Stack s;
    BTREE t;
    MakeNullStack(s);//新建栈
    t=BT;
    while(!IsEmpty(t)||!EmptyStack(s))
    {
        if(!IsEmpty(t))
        {
            Push(t,s);
            t=Lchild(t);
        }
        else
        {
            t=Top(s);
            Pop(s);
            *order=*order+Data(t);
            cout<<Data(t)<<"  ";//与非递归先序遍历不同,返回栈顶元素时再访问即可中序访问根节点
            t=Rchild(t);
        }
    }
}
void NoPostOrder(BTREE BT,string *order)//非递归后序遍历
{
    Stack s;//不考虑栈溢出情况
    BTREE t=BT;
    MakeNullStack(s);
    while(!IsEmpty(t)||s.top!=-1)//树非空或栈不满
    {
        while(!IsEmpty(t))//先将所有左子树压入栈中
        {
            t->num=1;
            Push(t,s);
            t=Lchild(t);
        }
        if(s.top!=-1)//栈不满
        {
            t=Top(s);
            if(!EmptyStack(s))
            {
                Pop(s);
            }
            else
            {
                break;
            }
            if(t->num==1)//第一次访问到该结点,准备访问右子树
            {
                t->num++;
                Push(t,s);
                t=Rchild(t);
            }
            else
            {
                if(t->num==2)//第二次访问到该节点,进行访问操作实现后序遍历
                {
                    *order=*order+Data(t);
                    cout<<Data(t)<<"  ";
                    t=NULL;
                }
            }
        }
    }
}
int GetMaxWidth(BTREE BT)//返回最大宽度
{
    if(BT==NULL)
    {
        return 0;
    }
    int MaxWidth=0,temp;
    Queue Q;
    BTREE T,Tmp;
    MakeNullQueue(Q);//类似层序遍历,借助栈元素个数获取每层宽度
    T=BT;
    EnQueue(T,Q);//队列元素初始化
    while(!EmptyQueue(Q))
    {
        temp=0;
        T=Front(Q);
        DeQueue(Q);
        if(Lchild(T))
        {
            EnQueue(Lchild(T),Q);
        }
        if(Rchild(T))
        {
            EnQueue(Rchild(T),Q);
        }
        Tmp=Front(Q);//记录最初队首元素
        do{
            EnQueue(Front(Q),Q);
            DeQueue(Q);
            temp++;
        }while(Front(Q)!=Tmp);//通过循环入队出队操作,比对队首是否与最初队首元素相同
        temp--;//多加1次
        if(temp>MaxWidth)//获取当前已遍历层最大宽度
        {
            MaxWidth=temp;
        }
    }
    return MaxWidth;
}
bool IsCompleteBTree(BTREE BT)//该二叉树是否为完全二叉树
{
    BTREE temp=BT;
    if(temp==NULL)//树空默认是完全二叉树
    {
        return true;
    }
    bool havenochild=false;
    Queue Q;
    MakeNullQueue(Q);//新建队列
    EnQueue(BT,Q);
    while(!EmptyQueue(Q))
    {
        temp=Front(Q);
        DeQueue(Q);
        if(havenochild)//此结点必要求没有左子树和右子树
        {
            if(Lchild(temp)!=NULL||Rchild(temp)!=NULL)
            {
                return false;
            }
        }
        else
        {
            if(Lchild(temp)!=NULL&&Rchild(temp)!=NULL)//均不空,可继续判断后继结点
            {
                EnQueue(Lchild(temp),Q);
                EnQueue(Rchild(temp),Q);
            }
            else if(Lchild(temp)!=NULL&&Rchild(temp)==NULL)//缺少子树结点,下一结点必无子树
            {
                havenochild=true;
                EnQueue(Lchild(temp),Q);
            }
            else if(Lchild(temp)==NULL&&Rchild(temp)!=NULL)//缺少左子树右右子树为非完全二叉树
            {
                return false;
            }
            else//左右子树结点均空,必无子树左右子树
            {
                havenochild=true;
            }
        }
    }
    return true;//若能出循环,说明所有结点均满足要求，为完全二叉树
}
void MakeNullQueue(Queue &Q)//创建队列
{
    Q.Front=new celltype;
    Q.Front->next=NULL;
    Q.Rear=Q.Front;
}
bool EmptyQueue(Queue Q)//队列是否为空
{
    if(Q.Front==Q.Rear)
    {
        return true;
    }
    else
    {
        return false;
    }
}
BTREE Front(Queue Q)//返回队首元素
{
    if(Q.Front->next)
    {
        return Q.Front->next->element;
    }
    else
    {
        return NULL;
    }
}
void EnQueue(BTREE x,Queue &Q)//入队
{
    Q.Rear->next=new celltype;
    Q.Rear=Q.Rear->next;
    Q.Rear->element=x;
    Q.Rear->next=NULL;
}
void DeQueue(Queue &Q)//出队
{
    celltype *temp;
    if(EmptyQueue(Q))//是否有元素能够出队
    {
        cout<<"队列为空"<<endl;
    }
    else{
        temp=Q.Front->next;
        Q.Front->next=temp->next;
        delete temp;//释放原元素空间
        if(Q.Front->next==NULL)
        {
            Q.Rear=Q.Front;
        }
    }
}
void MakeNullStack(Stack &s)//新建栈
{
    s.top=MAX;//可用元素初始化(从后向前使用)
}
bool EmptyStack(Stack s)//是否空栈
{
    if(s.top>MAX-1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
BTREE Top(Stack s)//返回栈顶元素
{
    if(EmptyStack(s))//是否有元素可返回
    {
        return NULL;
    }
    else
    {
        return s.data[s.top];
    }
}
void Pop(Stack &s)//出栈
{
    if(EmptyStack(s))//是否有元素可出
    {
        cout<<"stack is empty!"<<endl;
        return ;
    }
    else
    {
        s.top+=1;
    }
}
void Push(BTREE x,Stack &s)//入栈
{
    if(s.top==0)//栈是否满
    {
        cout<<"stack is full"<<endl;
    }
    else
    {
        s.top-=1;
        s.data[s.top]=x;
    }
}
