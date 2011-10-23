#include <stdio.h>
#include <math.h>
#include <stdbool.h>


inline int gauss( int n )
{
   return (n * (n+1))/2;
}

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

int getDivisors( int n )
{
   long long int p = 3;
   int c,cnt = 1;
   if ( !(n%2) )
   {
      c=1;
      n/=2;
      while( !(n%2) ) { ++c; n/=2; } 
      cnt*=(c+1);
   }
   do 
   {
      if ( isPrime( p ) && !(n%p)  )
      {
         c=1;
         n/=p;
         while ( !(n%p) ) { ++c; n/=p; }
         cnt*=(c+1);
      }
      p+=2;
   } while( n>1 );
   
   return cnt;
}




int main( void )
{
   int t=0;
   int i=0;
   
   while( true )
   {
      t+=++i;
      if( getDivisors(t) >= 500 )
      {
         break;
      }
   }
   printf("%d\n", t);
   
   return 0;
}
