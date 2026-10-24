//wap to find sum of array elements 
#include <stdio.h>
int main(){
    int n,sum=0;
    printf("Enter the number of elements in the array: "); //input of size of array
    scanf("%d",&n);
    int arr[n]; //declaration of array
    for(int i=0;i<n;i++){
        printf("Enter element %d: ",i+1); //input of array elements and plus one to index 
        scanf("%d",&arr[i]);    
    }
    for(int i=0;i<n;i++){
        sum+=arr[i]; //adding each element to sum
    }
    printf("Sum of array elements is: %d",sum); //output of sum of array elements
    return 0;
}