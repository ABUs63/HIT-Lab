#include <stdio.h>
#include <stdlib.h>
void Print(int arr[],int n);
int main()
{
    int arr[10]={9,1,2,4,5,3,6,7,0,8};//线性结构
    int i,j,temp,n=10;//循环变量、中间变量、数组长度
    for(i=0;i<n-1;i++)
    {
        for(j=n-1;j>=i+1;j--)
        {
            if(arr[j-1]>arr[j])
            {
                temp=arr[j];
                arr[j]=arr[j-1];
                arr[j-1]=temp;
            }
        }
    }
    Print(arr,n);
    return 0;
}
void Print(int arr[],int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%d  ",arr[i]);
    }
}
