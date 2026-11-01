#include <stdio.h>
int main()
{
	int arr[10][15],i,j,r,c,n;
	scanf ("%d %d",&r,&c);
	for (i=0;i<r;i++)
	{	for(j=0;j<c;j++)
		{	printf("%d",arr[i][j]);
		}
		printf("\n");
	}	
	return 0;
}