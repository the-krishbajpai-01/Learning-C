//Wap to find the maximum element in the array 
#include<stdio.h>
int main(){
    int max,i,size;
    printf("Enter the size of the array : ");
    scanf("%d",&size);
    int arr[size];
    printf("Enter the elements of the array :");
    for(i=0;i<size;i++){
    scanf("%d",&arr[i]);
    printf("Element at index %d is : %d\n",i,arr[i]);
    }
    max=arr[0];
    for(i=1;i<size;i++){
        if(arr[i]>max){
            max=arr[i];
        }
    }
    printf("The maximum element in the array is : %d",max);
    return 0;
    }