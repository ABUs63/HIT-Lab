#include <stdio.h>
#include <stdlib.h>
long fun(int n)
{
    if(n<=1)return n;
    else return (fun(n-1)+fun(n-2));
}
int main()
{
    int n=100;
    double g1=(1.0*fun(n))/fun(n+1);
    printf("g=%.8f",g1);
    return 0;
}
