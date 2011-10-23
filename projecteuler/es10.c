#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool isPrime( long long int x )
{
   //if ( !(x&1) ) return false;
   
   long long int i;
   const long long int lm = sqrt( (double)x );
   
   for ( i=3; i<=lm;i+=2 )
   {
      if ( x%i == 0 )
      {
         return false;
      }
   }
   
   return true;
}

int main( void )
{
   long long int sum;
   long long int p;
   
   sum = 2LL; 
   
   for( p=3; p<2000000; p+=2 )
   {
      if ( isPrime( p ) )
      {
         sum+=p;
      }
   }
   
   printf("%lld\n", sum );
   
   return 0;
}

