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
bool IsEmpty(BTREE BT);//���Ƿ�Ϊ��
BTREE Lchild(BTREE BT);//����������
BTREE Rchild(BTREE BT);//����������
char Data(BTREE BT);//�������ĸ�����ֵ
BTREE Create(char ch,BTREE x,BTREE y);//���������
void CreateBT(BTREE &BT);//cin������������ֵ
void PreOrder(BTREE BT,string *t);//�������
void InOrder(BTREE BT,string *t);//�������
void PostOrder(BTREE BT,string *t);//�������
void LeverOrder(BTREE BT,string *t);//�������
void MakeNullQueue(Queue &Q);//�½�����
bool EmptyQueue(Queue Q);////�����Ƿ�Ϊ��
BTREE Front(Queue Q);//���ض���
void EnQueue(BTREE x,Queue &Q);//���
void DeQueue(Queue &Q);//����
void NoPreOrder(BTREE BT,string *t);//�ǵݹ��������
void NoInOrder(BTREE BT,string *t);//�ǵݹ��������
void NoPostOrder(BTREE BT,string *t);//�ǵݹ�������
int GetMaxWidth(BTREE BT);//���ض����������
bool IsCompleteBTree(BTREE BT);//�Ƿ�Ϊ��ȫ������
void MakeNullStack(Stack &s);//�½�ջ
bool EmptyStack(Stack s);//ջ�Ƿ�Ϊ��
BTREE Top(Stack s);//����ջ��Ԫ��
void Pop(Stack &s);//��ջ
void Push(BTREE x,Stack &s);//��ջ

int main()
{
    string preorder,inorder,postorder,levelorder,nopreorder,noinorder,nopostorder;//������Ӧ���з����ķ�������
    /*����1����:
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

    BTREE A=NULL;//����2����
    CreateBT(A);
    cout<<"�������:"<<endl;
    PreOrder(A,&preorder);
    cout<<preorder;
    cout<<"\n�������:"<<endl;
    InOrder(A,&inorder);
    cout<<inorder;
    cout<<"\n�������:"<<endl;
    PostOrder(A,&postorder);
    cout<<postorder;
    cout<<"\n��α���:"<<endl;
    LeverOrder(A,&levelorder);
    cout<<levelorder;
    cout<<"\n�ǵݹ��������"<<endl;
    NoPreOrder(A,&nopreorder);
    cout<<nopreorder;
    cout<<"\n�ǵݹ��������"<<endl;
    NoInOrder(A,&noinorder);
    cout<<noinorder;
    cout<<"\n�ǵݹ�������"<<endl;
    NoPostOrder(A,&nopostorder);
    cout<<nopostorder;
    cout<<"\n�ö��������Ŀ��Ϊ:"<<GetMaxWidth(A)<<endl;
    bool result=IsCompleteBTree(A);
    cout<<"�Ƿ�����ȫ������:"<<endl;
    if(result)
    {
        cout<<"��";
    }
    else
    {
        cout<<"����";
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
    if(BT->lchild!=NULL)//�ǿշ���������
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
    if(BT->rchild!=NULL)//�ǿշ���������
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
BTREE Create(char ch,BTREE x,BTREE y)//���������
{
    BTREE T=new node;
    T->data=ch;
    T->lchild=x;
    T->rchild=y;
    return T;
}
void CreateBT(BTREE &BT)//cin�����������Ĵ�������
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
void PreOrder(BTREE BT,string *t)//�ݹ��������
{
    if(IsEmpty(BT)==false)
    {
        *t=*t+Data(BT);
        cout<<Data(BT)<<"  ";
        PreOrder(Lchild(BT),t);
        PreOrder(Rchild(BT),t);
    }
}
void InOrder(BTREE BT,string *t)//�ݹ��������
{
    if(IsEmpty(BT)==false)
    {
        InOrder(Lchild(BT),t);
        *t=*t+Data(BT);
        cout<<Data(BT)<<"  ";
        InOrder(Rchild(BT),t);
    }
}
void PostOrder(BTREE BT,string *t)//�ݹ�������
{
    if(IsEmpty(BT)==false)
    {
        PostOrder(Lchild(BT),t);
        PostOrder(Rchild(BT),t);
        *t=*t+Data(BT);
        cout<<Data(BT)<<"  ";
    }
}
void LeverOrder(BTREE BT,string *t)//�������
{
    Queue Q;
    BTREE T;
    MakeNullQueue(Q);//�½�����
    T=BT;
    if(!IsEmpty(T))//���ǿ����
    {
        EnQueue(T,Q);
    }
    while(!EmptyQueue(Q))
    {
        T=Front(Q);//Ϊ����������ӱ��������
        *t=*t+Data(T);
        cout<<Data(T)<<"  ";
        DeQueue(Q);
        if(Lchild(T))//�������ǿ����
        {
            EnQueue(Lchild(T),Q);
        }
        if(Rchild(T))//�������ǿ����
        {
            EnQueue(Rchild(T),Q);
        }
    }
}
void NoPreOrder(BTREE BT,string *order)//�ǵݹ��������
{
    Stack s;
    BTREE t;
    MakeNullStack(s);//�½�ջ
    t=BT;
    while(!IsEmpty(t)||!EmptyStack(s))//���ǿջ�ջ�ǿ�
    {
        if(!IsEmpty(t))//ͨ���������,���г������������ҽ�������ѹ��ջ,���������������
        {
            *order=*order+Data(t);
            cout<<Data(t)<<"  ";
            Push(t,s);
            t=Lchild(t);
        }
        else//����ջ�����������
        {
            t=Top(s);
            Pop(s);
            t=Rchild(t);
        }
    }
}
void NoInOrder(BTREE BT,string *order)//�ǵݹ��������
{
    Stack s;
    BTREE t;
    MakeNullStack(s);//�½�ջ
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
            cout<<Data(t)<<"  ";//��ǵݹ����������ͬ,����ջ��Ԫ��ʱ�ٷ��ʼ���������ʸ��ڵ�
            t=Rchild(t);
        }
    }
}
void NoPostOrder(BTREE BT,string *order)//�ǵݹ�������
{
    Stack s;//������ջ������
    BTREE t=BT;
    MakeNullStack(s);
    while(!IsEmpty(t)||s.top!=-1)//���ǿջ�ջ����
    {
        while(!IsEmpty(t))//�Ƚ�����������ѹ��ջ��
        {
            t->num=1;
            Push(t,s);
            t=Lchild(t);
        }
        if(s.top!=-1)//ջ����
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
            if(t->num==1)//��һ�η��ʵ��ý��,׼������������
            {
                t->num++;
                Push(t,s);
                t=Rchild(t);
            }
            else
            {
                if(t->num==2)//�ڶ��η��ʵ��ýڵ�,���з��ʲ���ʵ�ֺ������
                {
                    *order=*order+Data(t);
                    cout<<Data(t)<<"  ";
                    t=NULL;
                }
            }
        }
    }
}
int GetMaxWidth(BTREE BT)//���������
{
    if(BT==NULL)
    {
        return 0;
    }
    int MaxWidth=0,temp;
    Queue Q;
    BTREE T,Tmp;
    MakeNullQueue(Q);//���Ʋ������,����ջԪ�ظ�����ȡÿ����
    T=BT;
    EnQueue(T,Q);//����Ԫ�س�ʼ��
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
        Tmp=Front(Q);//��¼�������Ԫ��
        do{
            EnQueue(Front(Q),Q);
            DeQueue(Q);
            temp++;
        }while(Front(Q)!=Tmp);//ͨ��ѭ����ӳ��Ӳ���,�ȶԶ����Ƿ����������Ԫ����ͬ
        temp--;//���1��
        if(temp>MaxWidth)//��ȡ��ǰ�ѱ����������
        {
            MaxWidth=temp;
        }
    }
    return MaxWidth;
}
bool IsCompleteBTree(BTREE BT)//�ö������Ƿ�Ϊ��ȫ������
{
    BTREE temp=BT;
    if(temp==NULL)//����Ĭ������ȫ������
    {
        return true;
    }
    bool havenochild=false;
    Queue Q;
    MakeNullQueue(Q);//�½�����
    EnQueue(BT,Q);
    while(!EmptyQueue(Q))
    {
        temp=Front(Q);
        DeQueue(Q);
        if(havenochild)//�˽���Ҫ��û����������������
        {
            if(Lchild(temp)!=NULL||Rchild(temp)!=NULL)
            {
                return false;
            }
        }
        else
        {
            if(Lchild(temp)!=NULL&&Rchild(temp)!=NULL)//������,�ɼ����жϺ�̽��
            {
                EnQueue(Lchild(temp),Q);
                EnQueue(Rchild(temp),Q);
            }
            else if(Lchild(temp)!=NULL&&Rchild(temp)==NULL)//ȱ���������,��һ����������
            {
                havenochild=true;
                EnQueue(Lchild(temp),Q);
            }
            else if(Lchild(temp)==NULL&&Rchild(temp)!=NULL)//ȱ����������������Ϊ����ȫ������
            {
                return false;
            }
            else//��������������,����������������
            {
                havenochild=true;
            }
        }
    }
    return true;//���ܳ�ѭ��,˵�����н�������Ҫ��Ϊ��ȫ������
}
void MakeNullQueue(Queue &Q)//��������
{
    Q.Front=new celltype;
    Q.Front->next=NULL;
    Q.Rear=Q.Front;
}
bool EmptyQueue(Queue Q)//�����Ƿ�Ϊ��
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
BTREE Front(Queue Q)//���ض���Ԫ��
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
void EnQueue(BTREE x,Queue &Q)//���
{
    Q.Rear->next=new celltype;
    Q.Rear=Q.Rear->next;
    Q.Rear->element=x;
    Q.Rear->next=NULL;
}
void DeQueue(Queue &Q)//����
{
    celltype *temp;
    if(EmptyQueue(Q))//�Ƿ���Ԫ���ܹ�����
    {
        cout<<"����Ϊ��"<<endl;
    }
    else{
        temp=Q.Front->next;
        Q.Front->next=temp->next;
        delete temp;//�ͷ�ԭԪ�ؿռ�
        if(Q.Front->next==NULL)
        {
            Q.Rear=Q.Front;
        }
    }
}
void MakeNullStack(Stack &s)//�½�ջ
{
    s.top=MAX;//����Ԫ�س�ʼ��(�Ӻ���ǰʹ��)
}
bool EmptyStack(Stack s)//�Ƿ��ջ
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
BTREE Top(Stack s)//����ջ��Ԫ��
{
    if(EmptyStack(s))//�Ƿ���Ԫ�ؿɷ���
    {
        return NULL;
    }
    else
    {
        return s.data[s.top];
    }
}
void Pop(Stack &s)//��ջ
{
    if(EmptyStack(s))//�Ƿ���Ԫ�ؿɳ�
    {
        cout<<"stack is empty!"<<endl;
        return ;
    }
    else
    {
        s.top+=1;
    }
}
void Push(BTREE x,Stack &s)//��ջ
{
    if(s.top==0)//ջ�Ƿ���
    {
        cout<<"stack is full"<<endl;
    }
    else
    {
        s.top-=1;
        s.data[s.top]=x;
    }
}
