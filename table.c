#include <stdio.h>
int main()
{
	int a,r,sum=0;
	printf("enter the number:");
	scanf("%d",&a);
	while(a>=1)
	{	r=a%10;
		sum=sum+r;
		a=a/10;
	}
	printf("%d",sum);
		 
	return 0;
}