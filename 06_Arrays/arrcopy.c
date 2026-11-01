//wap to copy one array into another array
#include<stdio.h>
int main(){
    int size,i;
    printf("Enter the size of the array:");
    scanf("%d",&size);
    printf("Enter the elements of the array:");
    int arr1[size];
    int arr2[size];
    for(i=0;i<size;i++){
    scanf("%d",&arr1[i]);
    printf("The element of arr1 at index %d is : %d\n",i,arr1[i]);
    }
    for(i=0;i<size;i++){
        arr2[i]=arr1[i];
        printf("The elements of arr2 at index %d is : %d\n",i,arr2[i]);
    }
    return 0;
    }