//wap for string input and output 
#include<stdio.h>
int main(){
    char String[100];
    printf("Enter a string:");
    fgets(String, sizeof(String), stdin);//to read string with spaces
    printf("You entered: %s",String);
    return 0;
}