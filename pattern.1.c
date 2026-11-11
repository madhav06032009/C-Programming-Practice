#include <stdio.h>
int main()
{
	int a,i,n;
	printf("enter the number upto which pattern needed;");
	scanf("%d",&a);
	for(n=1;n<=a;n=n+1)
		{
			for(i=1;i<=n;i=i+1)
				{
					printf("%d",i);
				}
			printf("\n");
			
		}
	return 0;
}