///An array contains distinct even number from sequence starting from 2 but one number is missing find missing number

#include <stdio.h>
int main( )
{
	int n,i,j;
	int a[n];
	printf("enter the number upto which table is given:");
	scanf("%d",&n);
	for(i=1;i<n;i++)
	{ scanf("%d",&a[i]);}
	for(j=0;j<n;j++)
	{for(i=2;i<2*n;i=i+2)
		{if(a[j] == i)
		{ printf("Missing even number = %d",i);}}
	}
	return 0;
}	