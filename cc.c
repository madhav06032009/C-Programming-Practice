#include<stdio.h>
//febonacci series unsing recursion 
//0,1,1,2,3,5,8...
int febo(int n)
{	if (n == 0)
	return 0;
	if (n == 1) 
	return 1;
	else 
	{return febo(n-1)+febo(n-2);}
}

int main()
{
int n,i;
printf("enter number: ");
scanf("%d",&n);
for(i=0;i<=n;i++){
printf("%d ",febo(i));
}

return 0;
}