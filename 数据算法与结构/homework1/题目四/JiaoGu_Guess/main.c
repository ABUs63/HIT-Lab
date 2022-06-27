#include <stdio.h>
#include <stdlib.h>
typedef struct data{
    int num;
    int step;
}DATA;
void jiao(DATA x[],int n);
void Print(DATA x[],int n);
int main()
{
    DATA x[101];
    for(int i=1;i<101;i++)
    {
        x[i].num=i;
        x[i].step=0;
    }
    for(int i=1;i<101;i++)
    {
        printf("第%d个数:\n",i);
        jiao(x,i);
    }
    Print(x,100);
    return 0;
}
void jiao(DATA x[],int n)
{
    if(x[n].num==1)
    {
        printf("总结num=%d,step=%d,over\n",n,x[n].step);
        return;
    }
    else
    {
        x[n].step++;
        if(x[n].num%2==0)
        {
            x[n].num/=2;
        }
        else
        {
            if(x[n].num==1)
            {
                jiao(x,n);
            }
            else
            {
                x[n].num=3*x[n].num+1;
            }
        }
        printf("num=%d,step=%d\n",x[n].num,x[n].step);
        jiao(x,n);
    }
}
void Print(DATA x[],int n)
{
    printf("十个为一行，步骤数分别为:\n");
    for(int i=1;i<=n;i++)
    {
        printf("%d\t",x[i].step);
        if(i%10==0)
        {
            printf("\n");
        }
    }
}
