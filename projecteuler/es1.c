#include <stdio.h>
#include <math.h>

#define GAUSS( n ) ((n)*((n)+1)/2)

int sum( int n )
{
   return 3 * GAUSS( floor( n/3 ) ) + 5 * GAUSS( floor( n/5 ) ) - 15 * GAUSS( floor(n/15) );
}


int main( void )
{
   printf( "%d\n", sum( 999 ) );
   return 0;
}
 
