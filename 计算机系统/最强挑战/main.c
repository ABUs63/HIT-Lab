#include <stdio.h>
#include <stdlib.h>
int fun(int a,int b,int c)
{
    int x=c-b;
    if(x<0)
        x++;
    x=x>>1;
    x=x+b;
    if(x>a)return x+fun(a,b,x-1);
    else if(x<a)return x+fun(a,x+1,c);
    else return x;
}
int main()
{
    for(int i=1;i<16;i++)
    {
        printf("i:%d->%d\n",i,fun(i,0,14));
    }
    return 0;
}
