#include <stdio.h>
#include <stdbool.h>

inline bool isPalindromic( int n )
{
   int a = n;
   int b = 0;
   do
   {
      b = b*10 + a%10;
      a /= 10;
      if( a == b )
         return true;
   } while( a>b );
   
   return false;
}

int main( void )
{
   int i, j, p, pal = 0;
   for ( i=100; i < 1000; i++ )
   {
      for ( j=100; j < 1000; j++ )
      {
         p = i * j;
         if( isPalindromic( p ) && p > pal)
         {
            pal = p;
         }
      }
   }
   printf( "%d\n", pal );
   return 0;
}
         