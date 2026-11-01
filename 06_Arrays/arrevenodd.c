//wap to count even and odd elements in an array
#include<stdio.h>
int main(){
    int i,cev=0,cod=0,size;
    printf("Enter the size of the array :");
    scanf("%d",&size);
    int arr[size];
    printf("Enter the elements of the array:");
    for(i=0;i<size;i++){
    scanf("%d",&arr[i]);
    printf("The element at index %d is : %d\n",i,arr[i]);
    }
    for(i=0;i<size;i++){
    if(arr[i]%2==0){
    cev++;}
    else{
    cod++;
    }
    }
    printf("Number of even elements: %d\n",cev);
    printf("Number of odd elements: %d\n",cod);
    return 0;
    }