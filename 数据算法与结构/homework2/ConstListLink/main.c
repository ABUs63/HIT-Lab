#include <stdio.h>
#include <stdlib.h>
#define MAX 13
typedef struct{
    int data;
    int next;
}spacestr;
spacestr SPACE[MAX];
typedef int position,Cursor;
Cursor L,M,av;
void Initialize();
Cursor GetNode();
void FreeNode(Cursor p);
void Insert(int x,position p,spacestr *SPACE);
void Delete(position p,spacestr *SPACE);
void PrintAll();
void Print(Cursor x,int num);
void Inversion(int data[],int len,Cursor x);
int main()
{
    int num1,num2,number,data[MAX];
    Initialize();
    printf("输入表L的元素个数:");
    scanf(" %d",&num1);
    L=GetNode();
    SPACE[L].next=-1;
    for(int i=0;i<num1;i++)
    {
        printf("请输入第%d个元素:",i+1);
        scanf(" %d",&number);
        Insert(number,L,SPACE);
        Delete(av,SPACE);
    }
    printf("输入表M的元素个数:");
    scanf(" %d",&num2);
    M=GetNode();
    SPACE[M].next=-1;
    for(int i=0;i<num2;i++)
    {
        printf("请输入第%d个元素:",i+1);
        scanf(" %d",&number);
        Insert(number,M,SPACE);
        Delete(av,SPACE);
    }
    printf("SPACE的next值:\n");
    for(int i=0;i<MAX-1;i++)
    {
        printf("%d\t",SPACE[i].next);
    }
    printf("\nSPACE的data值:\n");
    for(int i=0;i<MAX-1;i++)
    {
        printf("%d\t",SPACE[i].data);
    }
    printf("\nL表元素为(从后至前):\n");
    Print(L,num1);
    printf("M表元素为(从后至前):\n");
    Print(M,num2);
    printf("表L的逆置为:\n");
    Inversion(data,num1,L);
    printf("表M的逆置为:\n");
    Inversion(data,num2,M);
    return 0;
}
void Initialize()
{
    int i;
    for(i=0;i<MAX-1;i++)
    {
        SPACE[i].next=i+1;
    }
    SPACE[i].next=-1;
    av=0;
}
Cursor GetNode()
{
    Cursor p;
    if(SPACE[av].next==-1)
    {
        p=-1;
    }
    else
    {
        p=SPACE[av].next;
        SPACE[av].next=SPACE[p].next;
    }
    return p;
}
void FreeNode(Cursor p)
{
    SPACE[p].next=SPACE[av].next;
    SPACE[av].next=p;
}
void Insert(int x,position p,spacestr *SPACE)
{
    position q;
    q=GetNode();
    SPACE[q].data=x;
    SPACE[q].next=SPACE[p].next;
    SPACE[p].next=q;
}
void Delete(position p,spacestr *SPACE)
{
    position q;
    if(SPACE[p].next!=-1)
    {
        q=SPACE[p].next;
        SPACE[p].next=SPACE[q].next;
        FreeNode(q);
    }
}
void PrintAll()
{
    for(int i=0;i<MAX-1;i++)
    {
        if(SPACE[i].next==-1)
        {
            break;
        }
        printf("%d  ",SPACE[i].data);
    }
    printf("\n");
}
void Print(Cursor x,int num)
{
    int count=0,temp=SPACE[x].next;
    for(count=0;count<num;count++)
    {
        printf("%d  ",SPACE[temp].data);
        temp=SPACE[temp].next;
    }
    printf("\n");
}
void Inversion(int data[],int len,Cursor x)
{
    int pos=SPACE[x].next;
    for(int i=len-1;i>=0;i--)
    {
        data[i]=SPACE[pos].data;
        pos=SPACE[pos].next;
    }
    for(int i=0;i<len;i++)
    {
        printf("%d\t",data[i]);
    }
    printf("\n");
}
