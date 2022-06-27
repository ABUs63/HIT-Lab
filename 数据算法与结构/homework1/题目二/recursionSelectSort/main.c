#include <stdio.h>
#include <stdlib.h>
int temp,i;
void Print(int arr[],int n);
void SelectSort(int arr[],int n);
int main()
{
    int arr[10]={0,2,5,7,3,1,8,9,4,6};
    int n=10;
    SelectSort(arr,n-1);
    Print(arr,n);
    return 0;
}
void SelectSort(int arr[],int n)
{
    if(n>=0)
    {
        int k=0;
        for(i=0;i<=n;i++)
        {
            if(arr[i]>arr[k])
            {
                k=i;
            }
        }
        if(k!=0)
        {
            temp=arr[k];
            arr[k]=arr[n];
            arr[n]=temp;
        }
        SelectSort(arr,n-1);
    }
}
void Print(int arr[],int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%d  ",arr[i]);
    }
}
