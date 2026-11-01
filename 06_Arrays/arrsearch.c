//wap for linear search in an array
#include<stdio.h>
int main(){
    int size,i,search;
    printf("Enter the size of the array:");
    scanf("%d",&size);
    printf("Enter the elements of the array:");
    int arr[size];
    for(i=0;i<size;i++){
    scanf("%d",&arr[i]);
    printf("The element at index %d is : %d\n",i,arr[i]);
    }
    printf("Enter the element to search in array ");
    scanf("%d",&search);
    for(i=0;i<size;i++){
        if(arr[i]==search){
            printf("The element %d is at %d index of the array",arr[i],i);
            break;
        }
    }
    return 0;
    }
                        
                        
                        