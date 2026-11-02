//wap to swap two numbers using function
#include<stdio.h>
int swap(int a , int b, int c){
    b=a;
    c=b;
    a=c;
}
                      
//function to swap values of two numbers
int main(){
    printf("Enter the number a and b:");
    int a, b, c;
    scanf("%d%d",&a,&b);
    int swapval=swap(a,b,c);
    printf("The value of a is %d and value of b is %d",b,a);
    return 0;
}
    
                      
                      
                      