//wap to find factorial of a number using function
#include<stdio.h>
int fact(int n){
int fact=1,i;
for(i=1;i<=n;i++){
fact=fact*i;}
return fact;
}
                      
//function to find factorial of a number
int main(){
    printf("Enter the number:");
    int n;
    scanf("%d",&n);
    int factorial = fact(n);
    printf("The factorial of the number %d is : %d",n,factorial);
    return 0;
}
    
                      
                      
                      