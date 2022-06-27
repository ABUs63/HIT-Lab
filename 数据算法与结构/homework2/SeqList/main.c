#include <stdio.h>
#include <stdlib.h>
#define N 20
typedef struct SeqList{
    int data[N];
    int last;
}SeqList;
void Print(SeqList x);//��ӡdataֵ
void Swap(int *x,int *y);//������������
void Delete(SeqList *x,int data);//����data����ȫ��ɾ��
void Sort(SeqList *x);//��data����
void SortDelete(SeqList *x);//ɾ���ź����data��������ͬ��Ԫ��
void Substitute(SeqList *x);//����data
void LeftMove(SeqList *x,int k);//data����kλ
void RightMove(SeqList *x,int k);//data����kλ
void SortMerge(SeqList *x,SeqList *y);//�ϲ�����õ�x,y
int main()
{
    SeqList seqlist1,seqlist2;
    int obj,step,choice;
    do{
        printf("�������1����:(������20)\n");
        scanf(" %d",&seqlist1.last);
        getchar();
    }while(seqlist1.last<0||seqlist1.last>20);
    printf("������������seqList1:\n");
    for(int i=0;i<seqlist1.last;i++)
    {
        scanf(" %d",&seqlist1.data[i]);
        getchar();
    }
    do{
        printf("�������2����:(������20)\n");
        scanf(" %d",&seqlist2.last);
        getchar();
    }while(seqlist2.last<0||seqlist2.last>20);
    printf("������������seqList2:\n");
    for(int i=0;i<seqlist2.last;i++)
    {
        scanf(" %d",&seqlist2.data[i]);
        getchar();
    }
    printf("1.����\n2.ɾ��Ŀ��Ԫ��\n3.��������õı�ɾ����ͬԪ�أ�δ�������Զ�����\n4.��������Ԫ��\n5.����kλ\n6.����kλ\n7.�ϲ���������õ����Ա�\n");
    printf("Ĭ�϶Ա�1���в���\n");
    printf("����ѡ��Ĺ���:\n");
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
                    printf("������Ҫɾ����Ԫ��:\n");
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
                    printf("��������λ��:������Ϊ���ƣ�\n");
                    scanf("%d",&step);
                    LeftMove(&seqlist1,step);
                    break;
                case 6:
                    printf("��������λ��:������Ϊ���ƣ�\n");
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
        printf("\n����ѡ��Ĺ���:\n");
        scanf("%d",&choice);
        getchar();
    }
    return 0;
}
void Print(SeqList x)
{
    printf("���Ա���������:\n");
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
    Sort(x);//ȷ��data�ź���
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
        printf("�������ȹ����޷��ϲ�\n");
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
        printf("�ϲ����");
        Print(z);
    }
}
