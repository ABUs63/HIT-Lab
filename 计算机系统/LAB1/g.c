#include <stdio.h>
#include <stdlib.h>
double fib(int n,double f1,double f2)
{
    if(n<2) return n;
    else if(n==2) return f1+f2;
    return fib(n-1,f2,f1+f2);
}
int main()
{
    double f[10];
    f[0]=0,f[1]=1,f[8]=f[9]=0;
    for(int i=0;i<=9;i++)
    {
        if(i!=0)
        {
            f[0]=f[9]+f[8];
            f[1]=f[0]+f[9];
        }
        for(int n=2;n<10;n++)
        {
            f[n]=f[n-1]+f[n-2];
        }
    }
    f[0]=f[9]+f[8];
    f[1]=f[0]+f[9];
    printf("better loop version:\n");
    printf("f(100)=%lf\nf(101)=%lf\n",f[0],f[1]);
    printf("g=%.8lf\n",f[0]/f[1]);
    double f100=fib(100,0,1);
    double f101=fib(101,0,1);
    printf("better recursion version:\n");
    printf("f(100)=%lf\nf(101)=%lf\n",f100,f101);
    printf("g=%.8lf",f100/f101);
    return 0;
}
