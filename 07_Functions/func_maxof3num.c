//wap to find max of three numbers using function
#include <stdio.h>
int max(int a, int b ,int c)
{
    if(a>b && a>c)
    {
        return a;
    }
    else if(b>a && b>c)
    {
        return b;
    }
    else
    {
        return c;
    }
}
int main()
{
    int a, b, c , maximum;
    printf("Enter three numbers: ");
    scanf("%d %d %d", &a, &b,&c);
    maximum = max(a,b,c);
    printf("max of %d,%d and %d is: %d\n", a, b, c ,maximum);
    return 0;
}