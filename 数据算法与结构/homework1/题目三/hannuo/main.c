#include <stdio.h>
#include <stdlib.h>
void move(int x,int y);//��x�ƶ���y
void hanoi(int n,int start,int temp,int obj);
int main()
{
    int n=0;
    printf("��������:");
    scanf("%d",&n);
    hanoi(n,1,2,3);//1,2,3�ֱ����λ��
    return 0;
}
void move(int x,int y)
{
    printf("��%dλ���Ƶ�%dλ��\n",x,y);
}
void hanoi(int n,int start,int temp,int obj)//nΪ��������startΪ��ʼ��tempΪ���ɣ�objΪĿ��
{
    if(n==1)
    {
        move(start,obj);
    }
    else
    {
        hanoi(n-1,start,obj,temp);//n-1����start�ƶ���temp
        move(start,obj);//��n�����ƶ���obj
        hanoi(n-1,temp,start,obj);//n-1����temp�ƶ���obj
    }
}
