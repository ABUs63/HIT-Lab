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
    records data;//��¼����ֻ��һ������
    celltype *lchild;//����
    celltype *rchild;//����
}Node;
typedef records *LIST;
typedef Node *BST;

int COUNT=0;//�Ƚϴ���
int anc=0;
int cc=0;//�۰���Ҵ���

void Insert(BST &F,records k)//BST�����㷨
{
    if(F==NULL)//��BST,�½�һ�����
    {
        F=new Node;
        F->data=k;
        F->lchild=NULL;
        F->rchild=NULL;
    }
    else if(F->data==k)//�йؼ���
    {
        cout<<"�Ѿ����ڸùؼ���"<<endl;
    }
    else if(F->data<k)//�ؼ��ִ�
    {
        Insert(F->rchild,k);
    }
    else//�ؼ���С
    {
        Insert(F->lchild,k);
    }
}
Node *Search(BST F,records k)//BST����
{
    BST P=F;
    if(P==NULL)
    {
        return P;
    }
    COUNT++;//�Ƚϴ���
    if(P->data==k)
    {
        return P;
    }
    else if(k<P->data)//��¼��С,����������
    {
        return (Search(P->lchild,k));
    }
    else//��¼����,����������
    {
        return (Search(P->rchild,k));
    }
}
records DeleteMin(BST &F)//ɾ����С��㲢���ؼ�¼
{
    records temp;
    BST P;
    if(F->lchild==NULL)//û��������,���ڵ���С
    {
        P=F;
        temp=F->data;
        F=F->rchild;
        delete P;
        return temp;
    }
    else
    {
        return DeleteMin(F->lchild);//�ݹ�Ѱ����С���
    }
}
void Delete(BST &F,records k)//ɾ��BST��Ϊk�Ľڵ�
{
    if(F!=NULL)
    {
        if(F->data<k)
        {
            Delete(F->rchild,k);//�ݹ����������
        }
        else if(F->data>k)
        {
            Delete(F->lchild,k);//�ݹ����������
        }
        else
        {
            if(F->lchild==NULL)
            {
                F=F->rchild;//�����̳�
            }
            else if(F->rchild==NULL)
            {
                F=F->lchild;//�����̳�
            }
            else
            {
                F->data=DeleteMin(F->rchild);//ɾ����С��㲢�̳�
            }
        }
    }
}
void Inorder(BST F,LIST L)//�ݹ��������
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
records half(LIST L,records k,int up)//�۰����
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
void Getdata()//��������
{
    fstream file1,file2;
    file1.open("dizen.txt");//˳�����е�����
    int a[MAX],temp,w;
    for(int i=0;i<MAX;i++)
    {
        a[i]=2*i+1;
        file1<<2*i+1<<endl;
    }
    file1.close();
    file2.open("random.txt");//�����������
    srand(int(time(0)));
    for(int i=0;i<MAX;i++)
    {
        w=rand()%MAX;//������������������
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
BST Create1()//��˳����������BST
{
    Getdata();
    fstream in;
    in.open("dizen.txt");
    if(in.fail())
    {
        cout<<"��ʧ��"<<endl;
        return NULL;
    }
    BST P=NULL;
    records k;
    for(int i=0;i<MAX;i++)//�������ɽ��
    {
        in>>k;
        Insert(P,k);
    }
    in.close();
    return P;
}
BST Create2()//�������������BST
{
    Getdata();
    fstream in;
    in.open("random.txt");
    if(in.fail())
    {
        cout<<"��ʧ��"<<endl;
        return NULL;
    }
    BST P=NULL;
    records k;
    for(int i=0;i<MAX;i++)//�������ɽ��
    {
        in>>k;
        Insert(P,k);
    }
    in.close();
    return P;
}
void Time(BST F)//������Ҵ���
{
    double sum1=0,sum2=0;
    for(int i=0;i<MAX;i++)
    {
        COUNT=0;
        Search(F,2*i+1);
        sum1+=COUNT;
    }
    cout<<"��������������ƽ������Ϊ:"<<(sum1/MAX)<<endl;
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
    sum2+=COUNT;//�����ܴ���
    cout<<"�������е�ż��ƽ������:"<<(sum2/(1+MAX))<<endl;
}
void Testhalf()//�۰����ƽ������
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
    cout<<"�۰���ҳɹ�ƽ������Ϊ:"<<avg<<endl;
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
    cout<<"�۰����ʧ��ƽ������Ϊ:"<<avg<<endl;
}
void Inordercout(BST F)//��ʾ��������������
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
    cout<<"1.BST��������;"<<endl;
    cout<<"2.BST���빦��;"<<endl;
    cout<<"3.BSTɾ������;"<<endl;
    cout<<"4.BST������;"<<endl;
    cout<<"5.BST���ҹ���;"<<endl;
    cout<<"6.�۰���ҹ���;"<<endl;
    cout<<"7.ʵ��Ƚ�."<<endl;
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
        cout<<"���빦��ѡ��:"<<endl;
        cin>>choice;
        if(choice<1||choice>7)
        {
            break;
        }
        switch (choice)
        {
        case 1:
            cout<<"�������ָ���:"<<endl;
            cin>>num;
            cout<<"��������Ԫ�ؼ�ֵ:"<<endl;
            for(int i=0;i<num;i++)
            {
                cin>>data;
                Insert(G,data);
            }
            cout<<"�������:"<<endl;
            Inordercout(G);
            break;
        case 2:
            cout<<"�������Ԫ�ؼ�ֵ:"<<endl;
            cin>>data;
            Insert(G,data);
            cout<<"�������:"<<endl;
            Inordercout(G);
            break;
        case 3:
            cout<<"����ɾ��Ԫ�ؼ�ֵ:"<<endl;
            cin>>data;
            Delete(G,data);
            cout<<"�������:"<<endl;
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
            cout<<"�������Ԫ�ؼ�ֵ:"<<endl;
            cin>>data;
            temp=Search(G,data);
            if(!temp)
            {
                cout<<"�鲻����Ԫ��"<<endl;
            }
            else
            {
                cout<<"�鵽��Ԫ��"<<endl;
            }
            break;
        case 6:
            cout<<"�Թ���1������BST��Ӧ�������������۰����:(��ǰʹ�ù���4)"<<endl;
            cout<<"������Ҽ�ֵ:"<<endl;
            cin>>data;
            if(half(L0,data,num-1)==-1)
            {
                cout<<"����ʧ��"<<endl;
            }
            else
            {
                cout<<"���ҳɹ�"<<endl;
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
