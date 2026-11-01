//Wap to find minimum element in an array
#include <stdio.h>
int main(){
    int size,i,min;
    printf("Enter the size of the array:");
    scanf("%d",&size);
    int arr[size];
    printf("Enter the elements of the array:");
    for(i=0;i<size;i++){
    scanf("%d",&arr[i]);
    printf("Element at index %d is : %d\n" ,i,arr[i]);
    }
    min=arr[0];
    for(i=1;i<size;i++){
    if(arr[i]<min){
    min=arr[i];
    }
    }
    printf("The minimum element in the array is:%d",min);
    return 0;
}