#include <stdio.h>
#include <stdlib.h>

int main()
{
    long f[101];
    f[0]=1,f[1]=1;
    for(int i=2;i<=100;i++)
    {
        f[i]=f[i-1]+f[i-2];
        printf("%d,%ld\n",i,f[i]);
    }
    double g2=1.0*f[99]/f[100];
    printf("g=%.8f",g2);
    return 0;
}
