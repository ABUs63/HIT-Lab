#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#define N 100

int isprime(int a);//素数判断,返回0为素数，1为非素数
unsigned long long int randprime();//随机生成素数的函数
unsigned long long int gcd(unsigned long long int a,unsigned long long int b);//gcd算法
unsigned long long int rsa(unsigned long long int a,unsigned long long int b,unsigned long long int c);//rsa(e,m,n),rsa(d,c,n)
unsigned long long int get_d(unsigned long long int a,unsigned long long int b);//计算d

int main()
{
    printf("120L021905--郎朗\n");
    printf("生成素数p，q，对应的e过程有点缓慢，请稍等\n");
    int e=1,s=31;
    int p,q;
    unsigned long long int f,n,d;
    char sources[N];//明文
    p=randprime();
    q=randprime();
    f=(p-1)*(q-1);//计算Eular函数值
    n=p*q;//计算n
    printf("生成p,q完成,p:%lu,q:%lu\n",p,q);
    do{
        e++;
    }while(e<1||e>f||gcd(e,f)!=1);
    printf("生成e完成,e:%lu\n",e);
    d=get_d(e,f);
    printf("生成d完成,d:%lu\n",d);
    printf("请输入要加密的明文:");
    gets(sources);
    int len=0;
    for(len=0;sources[len]!='\0';len++)//计算输入长度
    {
    }
    printf("p=%lu\n",p);//显示各个参数及计算过程
    printf("q=%lu\n",q);
    printf("f=(p-1)*(q-1)=%lu\n",f);
    printf("n=p*q=%lu\n",n);
    printf("e=%u\n",e);
    printf("d=%lu\n",d);
    printf("s=%u\n",s);
    printf("Sources\n");
    for(int i=0;i<len;i++)//显示要加密的明文
    {
        printf("%c",sources[i]);
    }
    printf("\nEncode:\n");
    int temp[N];
    for(int i=0;i<len;i++)//显示加密后的明文
    {
        temp[i]=rsa(e,(unsigned long long int)sources[i],n);
        printf("%x\t",temp[i]);
    }
    printf("\nDecode:\n");
    for(int i=0;i<len;i++)//显示解密后的明文
    {
        printf("%x\t",rsa(d,temp[i],n));
    }
    printf("\nDecryption:\n");
    for(int i=0;i<len;i++)//显示解密后的明文char
    {
        printf("%c",rsa(d,temp[i],n));
    }
    return 0;
}
int isprime(int a)//判断a是否为素数
{
    if(a==1)
    {
        return 1;//非素数
    }
    else{
        int i;
        for(i=2;i<=sqrt(a*1.0);i++)
        {
            if(a%i==0)
            {
                break;
            }
        }
        if(i<=sqrt(a*1.0))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}
unsigned long long int randprime()//随机生成素数函数
{
    unsigned long long int result=0;
    Sleep(1000);
    do{
        srand((unsigned)time(NULL));
        result=rand()%10000+1;
    }while(isprime(result));
    return result;
}
unsigned long long int gcd(unsigned long long int a,unsigned long long int b)//辗转相除
{
    if(b==0)
    {
        return a;
    }
    else
    {
        return gcd(b,a%b);
    }
}
unsigned long long int get_d(unsigned long long int a,unsigned long long int b)
{
    unsigned long long int i;
    unsigned long long int k=1;
    for(k=2;k<b;k++)
    {
        if((b*k+1)%a==0)
        {
            break;
        }
    }
    return (b*k+1)/a;
}
unsigned long long int rsa(unsigned long long int a,unsigned long long int b,unsigned long long int c)//加密算法
{
    unsigned long long int i=1;
    while(a!=0)//i相应的*和%
    {
        i*=b;
        i%=c;
        a--;
    }
    return i;
}

