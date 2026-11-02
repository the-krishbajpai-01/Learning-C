//wap to sum of array elements using function
#include<stdio.h>
int size;
int arrsum(int arr[] , int size){
    int sumofarr=0;
    for(int i=0;i<size;i++){
        sumofarr += arr[i];
    }
    return sumofarr;
}
      
//function for sum of elements of an array
int main(){
    printf("Enter the size of array:");
    int size;
    scanf("%d",&size);
    int arr[size], sumofarray;
    printf("Enter the elements of the array :");
    for(int i=0;i<size;i++){
        scanf("%d",&arr[i]);
    }
    sumofarray=arrsum(arr,size);
    printf("The sum of array is %d",sumofarray);
    return 0;
}
    
                      
                      
                      