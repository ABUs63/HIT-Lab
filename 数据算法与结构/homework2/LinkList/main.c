#include<stdio.h>
#include<stdlib.h>
#include<math.h>
struct celltype{
    int data;
    struct celltype *next;
};
typedef struct celltype *LIST;
typedef struct celltype *position;
void Reverse(LIST head);
void Print(LIST head);
void Release(LIST head);
int main()
{
    int n,m,choice=-1,obj,k,cout=0;
    position first=NULL,second=NULL,p=NULL,q=NULL,temp=NULL,head1=NULL,head2=NULL;
    do{
        printf("输入表1的长度(不少于2)\n");
        scanf(" %d",&n);
    }while(n<2);
    first=(LIST)malloc(sizeof(struct celltype));
    head1=(LIST)malloc(sizeof(struct celltype));
    if(first==NULL||head1==NULL)
    {
        exit(1);
    }
    printf("输入表1的第1个元素:\n");
    scanf(" %d",&first->data);
    first->next=NULL;
    head1->next=first;
    for (int i=2;i<=n;i++)
    {
        printf("输入表1的第%d元素:\n",i);
        second=(LIST)malloc(sizeof(struct celltype));
        if(second==NULL)
        {
            exit(1);
        }
        scanf(" %d",&second->data);
        first->next=second;//尾插
        second->next=NULL;
        first=second;
    }
    do{
        printf("输入表2的长度(不少于2)\n");
        scanf(" %d",&m);
    }while(m<2);
    first=(LIST)malloc(sizeof(struct celltype));
    head2=(LIST)malloc(sizeof(struct celltype));
    if(first==NULL||head2==NULL)
    {
        exit(1);
    }
    printf("输入表2的第1个元素:\n");
    scanf(" %d",&first->data);
    first->next=NULL;
    head2->next=first;
    for (int j=2;j<=m;j++)
    {
        printf("输入表2的第%d元素:\n",j);
        second=(LIST)malloc(sizeof(struct celltype));
        if(second==NULL)
        {
            exit(1);
        }
        scanf(" %d",&second->data);
        first->next=second;//尾插
        second->next=NULL;
        first=second;
    }
    do{
        printf("1.删除特定元素\n2.删除多余的重复元素\n3.逆置链表\n4.左移k位\n5.合并链表\n不在范围内退出\n");
        printf("选择以上功能:\n");
        scanf(" %d",&choice);
        switch (choice)
        {
        case 1:
            printf("输入想删除的元素:\n");
            scanf(" %d",&obj);
            p=head1;
            while(p->next!=NULL)
            {
                if(p->next->data==obj)
                {
                    q=p->next;
                    p->next=q->next;
                    free(q);
                }
                else
                {
                    p=p->next;
                }
            }
            printf("删除后结果为:\n");
            Print(head1);
            break;
        case 2:
            cout=0;
            p=head1;
            while(p->next!=NULL)
            {
                obj=p->next->data;
                p=p->next;
                while(p->next!=NULL)
                {
                    if(p->next->data==obj)
                    {
                        q=p->next;
                        p->next=q->next;
                        free(q);
                    }
                    else
                    {
                        p=p->next;
                    }
                }
                cout++;
                p=head1;
                for(int i=0;i<cout;i++)
                {
                    p=p->next;
                }
            }
            printf("结果为:\n");
            Print(head1);
            break;
        case 3:
            Reverse(head1);
            printf("结果为:\n");
            Print(head1);
            break;
        case 4://三次逆置得到左移k位
            printf("输入左移位数k(k自动取正):\n");
            scanf(" %d",&k);
            k=abs(k);
            p=head1;//p为前
            q=p;//q为后
            for(int i=0;i<k;i++)
            {
                q=q->next;
            }
            temp=head1;
            while(temp->next!=NULL)
            {
                temp=temp->next;
            }
            Reverse(q);
            for(int i=0;i<k;i++)
            {
                p=p->next;
            }
            p->next=NULL;
            p=head1;
            Reverse(p);
            for(int i=0;i<k;i++)
            {
                p=p->next;
            }
            p->next=temp;
            Reverse(head1);
            printf("结果为:\n");
            Print(head1);
            p->next=NULL;
            break;
        case 5:
            p=head1;
            q=head2;
            while(q->next!=NULL)
            {
                if(q->next->data<p->next->data)
                {
                    temp=p->next;
                    p->next=q->next;
                    q->next=q->next->next;
                    q->next=temp;
                }
                else if(q->next->data==p->next->data)
                {
                    p=p->next;
                    q->next=q->next->next;
                }
                else
                {
                    p=p->next;
                }
                if(p->next==NULL&&q->next!=NULL)
                {
                    p->next=q->next;
                    q->next=q->next->next;
                    p->next->next=NULL;
                }
            }
            printf("结果为:\n");
            Print(head1);
            break;
        default:
            break;
        }
    }while(choice>0&&choice<=5);
    Release(head1);
    Release(head2);
    return 0;
}
void Reverse(LIST head)
{
    position p,q;
    p=head->next;
    if(p){
        q=p->next;
        p->next=NULL;
        while(q!=NULL)
        {
            p=q;
            q=q->next;
            p->next=head->next;
            head->next=p;
        }
    }
}
void Print(LIST head)
{
    position p;
    p=head;
    while (p->next!=NULL)
    {
        printf("%d  ", p->next->data);
        p=p->next;
    }
    printf("\n");
}
void Release(LIST head)
{
    LIST p,q;
    p=head;
    while(p!=NULL)
    {
        q=p->next;
        free(p);
        p=q;
    }
}
