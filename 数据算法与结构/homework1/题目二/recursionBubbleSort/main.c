#include <stdio.h>
#include <stdlib.h>
int temp;
void Print(int arr[],int n);
void BubbleSort(int arr[],int n);
int main()
{
    int arr[10]={9,1,2,4,5,3,6,7,0,8};//线性结构
    int n=10;
    BubbleSort(arr,n-1);//下标操作，n-1
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
void BubbleSort(int arr[],int n)
{
    if(n>=1)
    {
        for(int i=0;i<n;i++)
        {
            if(arr[i]<arr[i+1])
            {
                temp=arr[i];
                arr[i]=arr[i+1];
                arr[i+1]=temp;
            }
        }
        BubbleSort(arr,n-1);
    }
}
