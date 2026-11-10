/*
Q2 WAP TO FIND TOTAL NUMBER OF PALLINDROME IN A RANGE ?
*/


#include <stdio.h>
int main()
{
    int start, end, num, temp, rev, rem, count = 0;
	printf("Enter starting and ending number: ");
    scanf("%d%d", &start, &end);
	if (start > end)
    {
        printf("Invalid Range");
        return 0;
    }
	for (num = start; num <= end; num++)
    {
        if (num < 0)
            continue;      // Skip negative numbers
		temp = num;
        rev = 0;
		if (num == 0)
        {
            printf("0 ");
            count++;
            continue;
        }
		while (temp > 0)
        {
            rem = temp % 10;
            rev = rev * 10 + rem;
            temp = temp / 10;
        }
		if (num == rev)
        {
            printf("%d ", num);
            count++;
        }
    }
	printf("\nTotal Palindrome Numbers = %d", count);
	return 0;
}
