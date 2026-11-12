
#include <stdio.h>
int main()
{
	int a,i,n;
	printf("enter the number upto which pattern needed;");
	scanf("%d",&a);
	for(n=a;n>=1;n=n-1)
		{
			for(i=1;i<=n;i=i-1)
				{
					printf("%d",n);
				}
			printf("\n");
			
		}
	return 0;
}