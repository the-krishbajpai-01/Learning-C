//Porgram to make a right angeled triangle using asterisks
#include <stdio.h>
int main()
{
    int i,j,a;
    printf("Enter the number of rows: ");
    scanf("%d",&a);
    printf("Enter the number of columns: ");
    scanf("%d",&a);
    for(i=1;i<=a;i++)
    {
        for(j=1;j<=i;j++){
            {
                printf("*");
            }
        }
        printf("\n");
    }
    return 0;
}