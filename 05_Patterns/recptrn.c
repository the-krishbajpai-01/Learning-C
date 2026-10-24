//Wap to make rectangle pattern
#include <stdio.h>
int main()
{
    int i,j,row,col;
    printf("Enter the number of rows and columns: ");
    scanf("%d%d",&row,&col);
    for(i=1;i<=row;i++)
    {
        for(j=1;j<=col;j++)
        {
            printf("*");
        }
        printf("\n");
    }
    return 0;
}