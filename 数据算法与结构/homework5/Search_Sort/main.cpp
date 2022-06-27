#include <iostream>
#include <cstring>
#include <fstream>
#include <queue>
#include <stack>
#include <ctime>
#include <cstdlib>
#define MAX 1024

using namespace std;

typedef int records;
typedef struct celltype
{
    records data;//记录考虑只有一个变量
    celltype *lchild;//链域
    celltype *rchild;//链域
}Node;
typedef records *LIST;
typedef Node *BST;

int COUNT=0;//比较次数
int anc=0;
int cc=0;//折半查找次数

void Insert(BST &F,records k)//BST插入算法
{
    if(F==NULL)//空BST,新建一个结点
    {
        F=new Node;
        F->data=k;
        F->lchild=NULL;
        F->rchild=NULL;
    }
    else if(F->data==k)//有关键字
    {
        cout<<"已经存在该关键字"<<endl;
    }
    else if(F->data<k)//关键字大
    {
        Insert(F->rchild,k);
    }
    else//关键字小
    {
        Insert(F->lchild,k);
    }
}
Node *Search(BST F,records k)//BST查找
{
    BST P=F;
    if(P==NULL)
    {
        return P;
    }
    COUNT++;//比较次数
    if(P->data==k)
    {
        return P;
    }
    else if(k<P->data)//记录更小,往左子树找
    {
        return (Search(P->lchild,k));
    }
    else//记录更大,往右子树找
    {
        return (Search(P->rchild,k));
    }
}
records DeleteMin(BST &F)//删除最小结点并返回记录
{
    records temp;
    BST P;
    if(F->lchild==NULL)//没有左子树,根节点最小
    {
        P=F;
        temp=F->data;
        F=F->rchild;
        delete P;
        return temp;
    }
    else
    {
        return DeleteMin(F->lchild);//递归寻找最小结点
    }
}
void Delete(BST &F,records k)//删除BST的为k的节点
{
    if(F!=NULL)
    {
        if(F->data<k)
        {
            Delete(F->rchild,k);//递归查找右子树
        }
        else if(F->data>k)
        {
            Delete(F->lchild,k);//递归查找左子树
        }
        else
        {
            if(F->lchild==NULL)
            {
                F=F->rchild;//右链继承
            }
            else if(F->rchild==NULL)
            {
                F=F->lchild;//左链继承
            }
            else
            {
                F->data=DeleteMin(F->rchild);//删除最小结点并继承
            }
        }
    }
}
void Inorder(BST F,LIST L)//递归中序遍历
{
    if(F==NULL||L==NULL)
    {
        return;
    }
    else
    {
        Inorder(F->lchild,L);
        L[anc++]=F->data;
        Inorder(F->rchild,L);
    }
}
records half(LIST L,records k,int up)//折半查找
{
    int low=0;
    int mid;
    while(low<=up)
    {
        cc++;
        mid=(low+up)/2;
        if(L[mid]==k)
        {
            return mid;
        }
        else if(L[mid]>k)
        {
            up=mid-1;
        }
        else if(L[mid]<k)
        {
            low=mid+1;
        }
    }
    return -1;
}
void Getdata()//生成数据
{
    fstream file1,file2;
    file1.open("dizen.txt");//顺序排列的奇数
    int a[MAX],temp,w;
    for(int i=0;i<MAX;i++)
    {
        a[i]=2*i+1;
        file1<<2*i+1<<endl;
    }
    file1.close();
    file2.open("random.txt");//随机排列奇数
    srand(int(time(0)));
    for(int i=0;i<MAX;i++)
    {
        w=rand()%MAX;//随机交换生成随机数列
        temp=a[w];
        a[w]=a[i];
        a[i]=temp;
    }
    for(int i=0;i<MAX;i++)
    {
        file2<<a[i]<<endl;
    }
    file2.close();
}
BST Create1()//用顺序奇数生成BST
{
    Getdata();
    fstream in;
    in.open("dizen.txt");
    if(in.fail())
    {
        cout<<"打开失败"<<endl;
        return NULL;
    }
    BST P=NULL;
    records k;
    for(int i=0;i<MAX;i++)//依次生成结点
    {
        in>>k;
        Insert(P,k);
    }
    in.close();
    return P;
}
BST Create2()//用随机奇数创建BST
{
    Getdata();
    fstream in;
    in.open("random.txt");
    if(in.fail())
    {
        cout<<"打开失败"<<endl;
        return NULL;
    }
    BST P=NULL;
    records k;
    for(int i=0;i<MAX;i++)//依次生成结点
    {
        in>>k;
        Insert(P,k);
    }
    in.close();
    return P;
}
void Time(BST F)//计算查找次数
{
    double sum1=0,sum2=0;
    for(int i=0;i<MAX;i++)
    {
        COUNT=0;
        Search(F,2*i+1);
        sum1+=COUNT;
    }
    cout<<"查找所有奇数的平均次数为:"<<(sum1/MAX)<<endl;
    for(int i=0;i<MAX;i++)
    {
        COUNT=0;
        Search(F,2*i+1);
        sum1+=COUNT;
    }
    for(int i=0;i<MAX;i++)
    {
        COUNT=0;
        Search(F,2*i);
        sum2+=COUNT;
    }
    Search(F,2048);
    sum2+=COUNT;//查找总次数
    cout<<"查找所有的偶数平均次数:"<<(sum2/(1+MAX))<<endl;
}
void Testhalf()//折半查找平均长度
{
    int sum=0;
    double avg;
    records a[MAX];
    for(int i=0;i<MAX;i++)
    {
        a[i]=2*i+1;
    }
    for(int i=0;i<MAX;i++)
    {
        cc=0;
        half(a,2*i+1,MAX-1);
        sum+=cc;
    }
    avg=(double)(sum)/MAX;
    cout<<"折半查找成功平均长度为:"<<avg<<endl;
    sum=0;anc=0;
    for(int i=0;i<MAX;i++)
    {
        cc=0;
        half(a,2*i,MAX-1);
        sum+=cc;
    }
    half(a,2048,MAX-1);
    sum+=cc;
    avg=(double)sum/(MAX+1);
    cout<<"折半查找失败平均长度为:"<<avg<<endl;
}
void Inordercout(BST F)//显示树的中序遍历结果
{
    BST P=F;
    if(P==NULL)
    {
        return ;
    }
    else
    {
        stack<BST> s;
        while(!s.empty()||P!=NULL)
        {
            if(P!=NULL)
            {
                s.push(P);
                P=P->lchild;
            }
            else
            {
                P=s.top();
                s.pop();
                cout<<P->data<<"\t"<<endl;
                P=P->rchild;
            }
        }
    }
}
void Menu()
{
    cout<<"1.BST建立功能;"<<endl;
    cout<<"2.BST插入功能;"<<endl;
    cout<<"3.BST删除功能;"<<endl;
    cout<<"4.BST排序功能;"<<endl;
    cout<<"5.BST查找功能;"<<endl;
    cout<<"6.折半查找功能;"<<endl;
    cout<<"7.实验比较."<<endl;
}
int main()
{
    LIST L0=NULL;
    L0=new records[MAX];
    BST G=NULL,F=NULL,P=NULL,temp=NULL;
    int choice,num,data;
    for(int i=0;i<MAX;i++)
    {
        L0[i]=-1;
    }
    do
    {
        Menu();
        cout<<"输入功能选择:"<<endl;
        cin>>choice;
        if(choice<1||choice>7)
        {
            break;
        }
        switch (choice)
        {
        case 1:
            cout<<"输入数字个数:"<<endl;
            cin>>num;
            cout<<"依次输入元素键值:"<<endl;
            for(int i=0;i<num;i++)
            {
                cin>>data;
                Insert(G,data);
            }
            cout<<"结果如下:"<<endl;
            Inordercout(G);
            break;
        case 2:
            cout<<"输入插入元素键值:"<<endl;
            cin>>data;
            Insert(G,data);
            cout<<"结果如下:"<<endl;
            Inordercout(G);
            break;
        case 3:
            cout<<"输入删除元素键值:"<<endl;
            cin>>data;
            Delete(G,data);
            cout<<"结果如下:"<<endl;
            Inordercout(G);
            break;
        case 4:
            Inorder(G,L0);
            for(int i=0;i<MAX;i++)
            {
                if(L0[i]==-1)
                {
                    num=i;
                    break;
                }
                else
                {
                    cout<<L0[i]<<"\t";
                }
            }
            cout<<endl;
            break;
        case 5:
            cout<<"输入查找元素键值:"<<endl;
            cin>>data;
            temp=Search(G,data);
            if(!temp)
            {
                cout<<"查不到该元素"<<endl;
            }
            else
            {
                cout<<"查到此元素"<<endl;
            }
            break;
        case 6:
            cout<<"对功能1建立的BST对应的排序结果进行折半查找:(提前使用功能4)"<<endl;
            cout<<"输入查找键值:"<<endl;
            cin>>data;
            if(half(L0,data,num-1)==-1)
            {
                cout<<"查找失败"<<endl;
            }
            else
            {
                cout<<"查找成功"<<endl;
            }
            break;
        case 7:
            F=Create1();
            P=Create2();
            Time(F);
            Testhalf();
            break;
        default:
            break;
        }
    }while(choice>=1&&choice<=7);
    delete []L0;
    return 0;
}
