//wap program for input and output of array elements
#include<stdio.h>
int main()
{
    int size;
    printf("Enter the size of the array:"); //input of size of array
    scanf("%d", &size);
    int arr[size]; //declaration of array
    printf("Enter the elements of the array: ");
    for(int i=0;i<size;i++) //loop for input of array elements
    {
        scanf("%d", &arr[i]);
        printf("Element at index %d is: %d\n", i, arr[i]); //loop for output of array elements
    }
    return 0;
}