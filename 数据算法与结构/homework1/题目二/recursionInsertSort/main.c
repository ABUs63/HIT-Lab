#include <stdio.h>
#include <stdlib.h>
int temp,i;
void Print(int arr[],int n);
void InsertSort(int arr[],int n);
int main()
{
    int arr[10]={1,2,5,7,3,0,8,9,4,6};
    int n=10;
    InsertSort(arr,n);
    Print(arr,n);
    return 0;
}
void InsertSort(int arr[],int n)
{
    if(n>1)
    {
        InsertSort(arr,n-1);
        temp=arr[n-1];
        for(i=n-2;i>=0;i--)
        {
            if(temp<arr[i])
            {
                arr[i+1]=arr[i];
            }
            else
            {
                break;
            }
        }
        arr[i+1]=temp;
    }
}
void Print(int arr[],int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%d  ",arr[i]);
    }
}
