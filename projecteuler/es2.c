#include <stdio.h>

int getEvenFibNumberSum( void )
{
   int m = 1;
   int n = 2;
   register unsigned int i;
   int tmp;
   int ret;
   
   ret = 0;
   do 
   {
      ret += n;
      for( i=0; i<3; i++ )
      {
         tmp = m;
         m = n;
         n = tmp+n;
      }

   } while( m < 4000000 );
   
   return ret;
}

int main( void )
{
   printf("%d\n", getEvenFibNumberSum() );
   return 0;
}
