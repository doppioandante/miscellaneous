#include <stdio.h>
/* thank to Master Gauss */
/*
   [ n(n+1) ]^2    [ n(n+1)(2n+1) ]
    ------       -   -----------    =
      2                   6
   [ n^2 + n ] ^2    [ n(n+1)(2n+1) ]
=   -----         -    -----------   =
      2                    6
      
=  ( n^4 + n^2 + 2n^3 )    (n^2 + n)(2n+1)
   -------------------- -  -------------- =
            4                    6
            
=  ( n^4 + n^2 + 2n^3 )    (2n^3 + n^2 + 2n^2 + n)
   -------------------- -  ----------------------- =
            4                         6
       3(n^4+n^2+2n^3) + 6(2n^3+3n^2+n)     
=    ------------------------------------- =
                        12
         3n^4 + 3n^2 + 6n^3 - 12n^3 - 18n^2 - 6n
=    ------------------------------------------- =
                        12
         3n^4 + 2n^3 - 3n^2 -2n
=    ------------------------------ =
                   12
         n( 3n^3 + 2n^2 - 3n - 2 )
=    ------------------------------
                  12
                   
   please Gauss, make it work *-*
*/

long long unsigned int squareMinusSum( long long unsigned int n )
{
   return (( n * ( 3*n*n*n + 2*n*n - 3*n -2 ) )/12);
}
            
int main( void )
{
  long long unsigned int n = 1000L;
  printf("%llud\n", squareMinusSum( n ) ); 
  return 0;
}

