#include <stdio.h>
#include <stdlib.h>
void Print(int arr[],int n);
int main()
{
    int arr[10]={1,9,3,6,2,7,4,5,0,8};
    int i,j,temp,n=10;
    for(i=0;i<n-1;i++)
    {
        j=i;
        temp=arr[j+1];
        while(j>=0)
        {
            if(temp<arr[j])
            {
                arr[j+1]=arr[j];
                j--;
            }
            else
            {
                break;
            }
        }
        arr[j+1]=temp;
    }
    Print(arr,n);
    return 0;
}
void Print(int arr[],int n)
{
    int i=0;
    for(i=0;i<n;i++)
    {
        printf("%d  ",arr[i]);
    }
}
