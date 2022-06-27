#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#define N 100

int isprime(int a);//�����ж�,����0Ϊ������1Ϊ������
unsigned long long int randprime();//������������ĺ���
unsigned long long int gcd(unsigned long long int a,unsigned long long int b);//gcd�㷨
unsigned long long int rsa(unsigned long long int a,unsigned long long int b,unsigned long long int c);//rsa(e,m,n),rsa(d,c,n)
unsigned long long int get_d(unsigned long long int a,unsigned long long int b);//����d

int main()
{
    printf("120L021905--����\n");
    printf("��������p��q����Ӧ��e�����е㻺�������Ե�\n");
    int e=1,s=31;
    int p,q;
    unsigned long long int f,n,d;
    char sources[N];//����
    p=randprime();
    q=randprime();
    f=(p-1)*(q-1);//����Eular����ֵ
    n=p*q;//����n
    printf("����p,q���,p:%lu,q:%lu\n",p,q);
    do{
        e++;
    }while(e<1||e>f||gcd(e,f)!=1);
    printf("����e���,e:%lu\n",e);
    d=get_d(e,f);
    printf("����d���,d:%lu\n",d);
    printf("������Ҫ���ܵ�����:");
    gets(sources);
    int len=0;
    for(len=0;sources[len]!='\0';len++)//�������볤��
    {
    }
    printf("p=%lu\n",p);//��ʾ�����������������
    printf("q=%lu\n",q);
    printf("f=(p-1)*(q-1)=%lu\n",f);
    printf("n=p*q=%lu\n",n);
    printf("e=%u\n",e);
    printf("d=%lu\n",d);
    printf("s=%u\n",s);
    printf("Sources\n");
    for(int i=0;i<len;i++)//��ʾҪ���ܵ�����
    {
        printf("%c",sources[i]);
    }
    printf("\nEncode:\n");
    int temp[N];
    for(int i=0;i<len;i++)//��ʾ���ܺ������
    {
        temp[i]=rsa(e,(unsigned long long int)sources[i],n);
        printf("%x\t",temp[i]);
    }
    printf("\nDecode:\n");
    for(int i=0;i<len;i++)//��ʾ���ܺ������
    {
        printf("%x\t",rsa(d,temp[i],n));
    }
    printf("\nDecryption:\n");
    for(int i=0;i<len;i++)//��ʾ���ܺ������char
    {
        printf("%c",rsa(d,temp[i],n));
    }
    return 0;
}
int isprime(int a)//�ж�a�Ƿ�Ϊ����
{
    if(a==1)
    {
        return 1;//������
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
unsigned long long int randprime()//���������������
{
    unsigned long long int result=0;
    Sleep(1000);
    do{
        srand((unsigned)time(NULL));
        result=rand()%10000+1;
    }while(isprime(result));
    return result;
}
unsigned long long int gcd(unsigned long long int a,unsigned long long int b)//շת���
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
unsigned long long int rsa(unsigned long long int a,unsigned long long int b,unsigned long long int c)//�����㷨
{
    unsigned long long int i=1;
    while(a!=0)//i��Ӧ��*��%
    {
        i*=b;
        i%=c;
        a--;
    }
    return i;
}

