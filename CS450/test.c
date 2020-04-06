#include <stdio.h>
#include <math.h>

#define SIZE 1000

int status[SIZE];

void sieve()
{
 int i,j;
 for(i=0;i<SIZE;i++) status[i]= 0;
 int sq = sqrt(SIZE);
 for(i=4;i<=SIZE;i+=2) status[i] = 1;
 for(i=3;i<=sq;i+=2){
  if(status[i]==0) {
   for(j=2*i;j<=SIZE;j+=i) status[j]=1;
  }
 }
 status[1] = 1;
}

int main()
{
 int n;
 sieve();
 printf("Enter a number to check prime: ");
 scanf("%d",&n);
 if(status[n]==0) printf("%d is prime",n);
 else printf("%d is not prime.", n);
 return 0;
}