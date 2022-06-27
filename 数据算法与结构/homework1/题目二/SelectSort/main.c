#include <stdio.h>
#include <stdlib.h>
void Print(int arr[],int n);
int main()
{
    int arr[10]={0,2,5,7,3,1,8,9,4,6};
    int i,j,k,temp,n=10;
    for(i=0;i<n-1;i++)
    {
        k=i;
        for(j=i+1;j<n;j++)
        {
            if(arr[j]>arr[k])
            {
                k=j;
            }
        }
        if(k!=i)
        {
            temp=arr[i];
            arr[i]=arr[k];
            arr[k]=temp;
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
