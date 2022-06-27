#include <stdio.h>
#include <stdlib.h>
void move(int x,int y);//从x移动到y
void hanoi(int n,int start,int temp,int obj);
int main()
{
    int n=0;
    printf("输入数量:");
    scanf("%d",&n);
    hanoi(n,1,2,3);//1,2,3分别代表位置
    return 0;
}
void move(int x,int y)
{
    printf("从%d位置移到%d位置\n",x,y);
}
void hanoi(int n,int start,int temp,int obj)//n为操作数，start为起始，temp为过渡，obj为目标
{
    if(n==1)
    {
        move(start,obj);
    }
    else
    {
        hanoi(n-1,start,obj,temp);//n-1个从start移动到temp
        move(start,obj);//第n个从移动到obj
        hanoi(n-1,temp,start,obj);//n-1个从temp移动到obj
    }
}
