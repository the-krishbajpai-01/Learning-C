//wap to find average of array elements
#include<stdio.h>
int main()
{
    int size,i;
    float avg,sum=0;
    printf("Enter the number of elements in the array: ");
    scanf("%d",&size);
    int arr[size];//declaring array of size 'size'
    for(i=0;i<size;i++)
    {
        printf("Enter the %d element of the array :",i+1); //taking input from user
        scanf("%d",&arr[i]); //storing input in array
        sum+=arr[i];
    }
    avg=sum/size;
    printf("The average of the array elements is: %.2f",avg); //displaying the average of array elements
    return 0;
}