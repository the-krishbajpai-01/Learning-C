//wap to find the length of string without using strlen function
#include <stdio.h>
int main(){
    int i=0;
    char str[100];
    printf("Enter a string: ");
    scanf("%s", str);
    while(str[i]!='\0'){
        i++;
    }
    printf("Length of string is: %d", i);
    return 0;
}