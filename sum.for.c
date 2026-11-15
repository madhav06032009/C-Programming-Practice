#include <stdio.h>
int main()
{
	int i,n,sum=0;
	printf("enter a number upto which sum wants:");
	scanf("%d",&n);
	for(i=1;i<=n;i++)
		{
			sum=sum+i; 
		}
	printf("sum of n natursl number is %d",sum);
	return 0;
}
