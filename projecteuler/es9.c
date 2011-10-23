#include <stdio.h>
#include <math.h>

int main( void )
{
   /*
    a = m^2 - n^2; b = 2mn; c = n^2 + m^2;  a<b<c
    
   m^2-n^2+2mn+n^2+m^2 = 1000
   2m^2+2mn = 1000
   2m(m+n)  = 1000
   m(m+n)   = 500; 
   n        = 500/m-m; n < m
    
   */

   int m, n, sqm, sqn;
   for( m=5; ; m+=5 )
   {
      if ( 500/m - m < m )
      {
         n = 500/m - m;
         break;
      }
   }
   
   sqm = m*m;
   sqn = n*n;
   
   
   printf("%d\n", (sqm-sqn) * 2 * m * n * (sqn+sqm)  );
   
   return 0;
}
