#ifndef MD5_H
#define MD5_H

/* author: lumo3c273@gmail.com
   license: LGPL
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstring>

class md5
{
   private:
      
      unsigned int  m_length;
      unsigned char m_string[64];
      unsigned int  m_state[4];
      unsigned char m_digest[16];

      bool m_bPerformed;
      
   public:
      
      md5( void );
      md5( const md5 &md );
      ~md5( void );
      
      void update( const std::string &string );
      void update( const std::ifstream &f_in );
      void update( unsigned char *buffer, unsigned int length );
      void update( const char *string );
      
      void perform( void );
      
      std::string hex_digest( void );
      void digest( unsigned char output[16] );
      
   private:
      
      static void decode( unsigned char* output, unsigned int *input, unsigned int length );
      static void encode( unsigned int* output, unsigned char *input, unsigned int length );
      
      static inline unsigned int F( unsigned int x, unsigned int y, unsigned int z );
      static inline unsigned int G( unsigned int x, unsigned int y, unsigned int z );
      static inline unsigned int H( unsigned int x, unsigned int y, unsigned int z );
      static inline unsigned int I( unsigned int x, unsigned int y, unsigned int z );
      static inline unsigned int rotate_left( unsigned int x, unsigned int n );

#define FF( F, a, b, c, d, x, s, t ) \
   a = b + md5::rotate_left((a + F(b,c,d) + x + t), s);

      void transform( unsigned int *in );
};


inline md5 &operator << ( md5& md, std::string& string )
{
   md.update( string );
   return md;
}

inline md5 &operator << ( md5 &md, std::ifstream &f_in )
{
   md.update( f_in );
   return md;
}


unsigned int md5::F( unsigned int x, unsigned int y, unsigned int z )
{
   return ( x & y ) | ( ~x & z );
}

unsigned int md5::G( unsigned int x, unsigned int y, unsigned int z )
{
   return ( x & z ) | ( y & ~z );
}

unsigned int md5::H( unsigned int x, unsigned int y, unsigned int z )
{
   return x^y^z;
}

unsigned int md5::I( unsigned int x, unsigned int y, unsigned int z )
{
   return y ^ ( x | ~z );
}

unsigned int md5::rotate_left( unsigned int x, unsigned int n )
{
   return ( x<<n ) | ( x>>(32-n) );
}

#endif
