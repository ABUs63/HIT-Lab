#include <stdio.h>
#include <stdlib.h>
#define N 20
typedef struct SeqList{
    int data[N];
    int last;
}SeqList;
void Print(SeqList x);//打印data值
void Swap(int *x,int *y);//交换两个数字
void Delete(SeqList *x,int data);//若有data，则全部删除
void Sort(SeqList *x);//给data排序
void SortDelete(SeqList *x);//删除排好序的data中所有相同的元素
void Substitute(SeqList *x);//逆序data
void LeftMove(SeqList *x,int k);//data左移k位
void RightMove(SeqList *x,int k);//data右移k位
void SortMerge(SeqList *x,SeqList *y);//合并排序好的x,y
int main()
{
    SeqList seqlist1,seqlist2;
    int obj,step,choice;
    do{
        printf("请输入表1长度:(不超过20)\n");
        scanf(" %d",&seqlist1.last);
        getchar();
    }while(seqlist1.last<0||seqlist1.last>20);
    printf("请输入整数给seqList1:\n");
    for(int i=0;i<seqlist1.last;i++)
    {
        scanf(" %d",&seqlist1.data[i]);
        getchar();
    }
    do{
        printf("请输入表2长度:(不超过20)\n");
        scanf(" %d",&seqlist2.last);
        getchar();
    }while(seqlist2.last<0||seqlist2.last>20);
    printf("请输入整数给seqList2:\n");
    for(int i=0;i<seqlist2.last;i++)
    {
        scanf(" %d",&seqlist2.data[i]);
        getchar();
    }
    printf("1.排序\n2.删除目标元素\n3.将已排序好的表删除相同元素（未排序则自动排序）\n4.逆置所有元素\n5.左移k位\n6.右移k位\n7.合并两个排序好的线性表\n");
    printf("默认对表1进行操作\n");
    printf("输入选择的功能:\n");
    scanf("%d",&choice);
    getchar();
    while(choice>0&&choice<=7)
    {
        switch (choice)
            {
                case 1:
                    Sort(&seqlist1);
                    break;
                case 2:
                    printf("请输入要删除的元素:\n");
                    scanf("%d",&obj);
                    Delete(&seqlist1,obj);
                    break;
                case 3:
                    SortDelete(&seqlist1);
                    break;
                case 4:
                    Substitute(&seqlist1);
                    break;
                case 5:
                    printf("输入左移位数:（负数为右移）\n");
                    scanf("%d",&step);
                    LeftMove(&seqlist1,step);
                    break;
                case 6:
                    printf("输入右移位数:（负数为左移）\n");
                    scanf("%d",&step);
                    RightMove(&seqlist1,step);
                    break;
                case 7:
                    SortMerge(&seqlist1,&seqlist2);
                    break;
                default:
                    break;
            }
        if(choice!=7)
        {
            Print(seqlist1);
        }
        printf("\n输入选择的功能:\n");
        scanf("%d",&choice);
        getchar();
    }
    return 0;
}
void Print(SeqList x)
{
    printf("线性表数据如下:\n");
    for(int i=0;i<x.last;i++)
    {
        printf("%d  ",x.data[i]);
    }
}
void Swap(int *x,int *y)
{
    int temp;
    temp=*x;
    *x=*y;
    *y=temp;
}
void Delete(SeqList *x,int data)
{
    int i,j,flag=0;
    for(i=0;i<x->last;i++)
    {
        if(x->data[i]==data)
        {
            flag++;
            j=i;
            while(j<x->last)
            {
                x->data[j]=x->data[j+1];
                j++;
            }
            x->last--;
            i--;
        }
    }
}
void Sort(SeqList *x)
{
    int i,j,k;
    for(i=0;i<x->last-1;i++)
    {
        k=i;
        for(j=i;j<x->last;j++)
        {
            if(x->data[k]<x->data[j])
            {
                k=j;
            }
        }
        if(k!=i)
        {
            Swap(&x->data[i],&x->data[k]);
        }
    }
}
void SortDelete(SeqList *x)
{
    int i,obj;
    Sort(x);//确保data排好序
    for(i=0;i<x->last-1;i++)
    {
        if(x->data[i]==x->data[i+1])
        {
            obj=x->data[i];
            Delete(x,obj);
        }
    }
}
void Substitute(SeqList *x)
{
    int i,j;
    if(x->last%2==0)
    {
        for(i=0,j=x->last-1;(j-i)>=0;i++,j--)
        {
            Swap(&x->data[i],&x->data[j]);
        }
    }
    else
    {
        for(i=0,j=x->last-1;(j-i)>0;i++,j--)
        {
            Swap(&x->data[i],&x->data[j]);
        }
    }
}
void LeftMove(SeqList *x,int k)
{
    int temp;
    if (k==0)
    {
        return;
    }
    else if(k<0)
    {
        RightMove(x,(-k));
    }
    else
    {
        for(int i=0;i<k;i++)
        {
            temp=x->data[0];
            for(int j=0;j<x->last-1;j++)
            {
                x->data[j]=x->data[j+1];
            }
            x->data[x->last-1]=temp;
        }
    }
}
void RightMove(SeqList *x,int k)
{
    int temp;
    if (k==0)
    {
        return;
    }
    else if(k<0)
    {
        LeftMove(x,(-k));
    }
    else
    {
        for(int i=0;i<k;i++)
        {
            temp=x->data[x->last-1];
            for(int j=x->last-1;j>0;j--)
            {
                x->data[j]=x->data[j-1];
            }
            x->data[0]=temp;
        }
    }
}
void SortMerge(SeqList *x,SeqList *y)
{
    if((x->last+y->last)>20)
    {
        printf("两个表长度过大，无法合并\n");
        return;
    }
    else
    {
        SeqList z;
        z.last=x->last+y->last;
        Sort(x);
        Sort(y);
        for(int i=0;i<x->last;i++)
        {
            z.data[i]=x->data[i];
        }
        for(int i=0;i<y->last;i++)
        {
            z.data[x->last+i]=y->data[i];
        }
        Sort(&z);
        printf("合并后的");
        Print(z);
    }
}
