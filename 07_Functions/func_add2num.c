//wap to add two numbers using function
#include <stdio.h>
int add(int a, int b)
{
    return a + b;
}
int main()
{
    int a, b, sum;
    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);
    sum = add(a, b);
    printf("Sum of %d and %d is: %d\n", a, b, sum);
    return 0;
}