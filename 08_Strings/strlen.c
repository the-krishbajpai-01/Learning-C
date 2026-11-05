//wap to calculate the length of a string using strlen function
#include <stdio.h>
#include <string.h>

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin); // Read string input
    int length = strlen(str); // Calculate length using strlen
    printf("Length of the string is: %d\n", length - 1); // Subtract 1 to exclude newline character
    return 0;
}