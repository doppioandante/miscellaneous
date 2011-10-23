#include <stdio.h>
#include <math.h>

int main( void )
{
   long long int n = 600851475143;
   int k = floor( pow( n, 1.0/3.0 ) );
   if ( k%2 == 0 ) --k;
   for ( k; k>0; k-=2 )
   {
      if ( n % k == 0 ) // *-*
      {
         printf( "%d\n", k );
         break;
      }
   }
   return 0;
}

   