#include<stdio.h>
#include<math.h>
int main()
{
int a,j,number;
scanf("%d",&number);
if(number<=1)
return 0;
if(number%2==0)
return 0;
for(j=3;j<=(int)sqrt(number);j+=2)
{
a=number%j;
}
if(a==0)
return 0;
else
printf("prime\n");

return 0;
}


