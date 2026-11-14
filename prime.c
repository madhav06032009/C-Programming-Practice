#include <stdio.h>
int main()
{
	int a,i,s=0;
	printf("enter a number:");
	scanf("%d",&a);
	if (a>1)
		{
		for(i=2;i<=a;i=i+1)
			{
				if(a%i==0){
					s=s+1;}
				else{continue;}
			}
		if(s==1){printf("prime");}
		else{printf("not prime");}
		}
	else if(a==1)
	{printf("not prime");}
	else{printf("invalid");}
	return 0;
}
