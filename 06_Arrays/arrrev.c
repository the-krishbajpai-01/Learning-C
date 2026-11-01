//wap to reverse an array
#include<stdio.h>
int main(){
    int size,i,rev;
    printf("Enter the size of the array:");
    scanf("%d",&size);
    printf("Enter the elements of the array:");
    int arr[size];
    for(i=0;i<size;i++){
    scanf("%d",&arr[i]);
    printf("The element at index %d is : %d\n",i,arr[i]);}
    //reverse the array
    printf("The reversed array is :");
    for(i=size-1;i>=0;i--){
        printf("%d ",arr[i]);}
        return 0;
    }
                        