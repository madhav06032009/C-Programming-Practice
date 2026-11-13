#include <stdio.h>
int main()
{
	int i,sum=0;
		for(i=0;i<=40;i+=2)
		{
			sum=sum+i;
			printf("the pattern %d  ",sum);
		}
	/* printf("sum of pattern is %d \n",sum); */
	return 0;
}