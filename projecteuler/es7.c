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

long long int getPrimeAt( int pos )
{
   --pos;
   long long int p = 1;
   int cnt = 0;
   do 
   {
      p+=2;
      if ( isPrime( p ) )
      {
         ++cnt;
      }
   } while( cnt!=pos );
   
   return p;
}

int main( void )
{
   printf("%lld\n", getPrimeAt(10001) );
   return 0;
}
