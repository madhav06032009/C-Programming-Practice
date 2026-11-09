#include <stdio.h>
void  sidhi(int n, int a[])
{ for(int i=0;i<n;i++)
	{printf("%d",a[i]);}
printf("\n");}
void ulta(int n,int a[])
{for(int i=0;i<n;i++)
{printf("%d",a[n-i-1]);}}
int main()
{
	int n;
	scanf("%d",&n);
	int a[n];
	for(int i=0;i<n;i++)
	{scanf("%d",&a[i]);}
	sidhi(n,a);
	ulta(n,a);
    
return 0;
}