//Here is a simple program to generate prime numbers upto a given specific number
/*Prime No. from 1 to 50*/
/*By-Himanshu Rathee*/
#include<stdio.h>
#include<conio.h>
void main()
{
int i,j,n;
clrscr();
printf(" Enter the number upto which we have to find the prime number: ");
scanf("%d",&n);
printf("\n");
for(i=2;i<=n;i++)
{
for(j=2;j<=i-1;j++)
if(i%j==0)
break;
/*Number is divisble by some other number. So break out*/
if(i==j)
printf("\t%d",i);
/*Number was divisible by itself (that is, i was same as j)*/
}
/*Continue loop upto nth number*/
getch();
}


