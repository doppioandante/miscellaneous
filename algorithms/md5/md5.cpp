#include "md5.h"
#include <cstdlib>

/* author: lumo3c273@gmail.com
   license: LGPL
*/

/* padding bytes */
static unsigned char s_padding[64] =
{
   0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


/* sin table */
static unsigned int s_table[64] =                                          
{                                                                          
   0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,                         
   0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,                         
   0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,                         
   0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,                         
   0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
   0xd62f105d, 0x2441453,  0xd8a1e681, 0xe7d3fbc8,
   0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
   0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
   0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
   0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
   0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x4881d05,
   0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
   0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
   0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
   0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
   0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

static int s_round[16] =
{
   7, 12, 17, 22,
   5,  9, 14, 20,
   4, 11, 16, 23,
   6, 10, 15, 21
};


md5::md5( void ):
   m_bPerformed( false )
{
   /* inizialize m_state */
   m_state[0] = 0x67452301;
   m_state[1] = 0xefcdab89;
   m_state[2] = 0x98badcfe;
   m_state[3] = 0x10325476;
   

   m_length = 0 ;
   *(m_string) = '\0';
}

md5::md5( const md5& other ):
   m_bPerformed( other.m_bPerformed )
{
   std::memcpy( m_state, other.m_state, sizeof( m_state ) );
   // rather than a string, m_string is an unsigned char array
   std::memcpy( m_string, other.m_string, sizeof( m_string) );

   m_length = other.m_length;
}


md5::~md5( void )
{ }


void md5::update( unsigned char *buffer, unsigned int length )
{
   unsigned int in[16];
   unsigned int pos;
   unsigned int cnt;
   
   cnt = 0;
   pos = m_length & 0x3f; // length % 64
   m_length += length;
   
   // TODO: optimize
   
   while ( cnt < length )
   {
      m_string[ pos++ ] = buffer[ cnt++ ];
      if ( pos == 64 ) // reached the end of m_string
      {
         md5::encode( in, m_string, 16 );
         this->transform( in );
         pos = 0;
      }
   }
   
   m_bPerformed = false;
   
}

void md5::update( const char *string )
{
   int length;
   unsigned char *buff;
   
   length = strlen( string );
   buff = new unsigned char[ length ];
   
   /* copy the string into an unsigned char buffer */
   memcpy( buff, string, sizeof(char)*length );
   this->update( buff, length );
   
   delete[] buff;
}

void md5::update( const std::string &string )
{
   this->update( string.c_str() );
}

void md5::update( const std::ifstream &f_in )
{
   std::stringstream ss;
   
   ss << f_in.rdbuf(); // read the file and save into ss
   
   this->update( ss.str() );
}


void md5::perform( void )
{
   unsigned int in[16];
   unsigned int padding_length;
   unsigned int length;
   
   /* get the length = 448 mod 512 */
   length = m_length; // save the original length
   padding_length = m_length & 0x3f; // length % 64
   padding_length = ( padding_length < 56 ) ? ( 56 - padding_length ) : ( 120 - padding_length );
   
   this->update( s_padding, padding_length ); // append padding bytes
   
   /* the lastest two bytes are used for the length */
   in[14] = length << 3;  // length * 8
   in[15] = length >> 29;
   md5::encode( in, m_string, 14 ); // pos 14 and 15 used for length
   
   this->transform( in );
   md5::decode( m_digest, m_state, 4 ); // save m_state in m_digest
   
   m_bPerformed = true;
}


void md5::transform( unsigned int *in )
{
   /* save m_state in a,b,c,d */
   unsigned int a = m_state[0];
   unsigned int b = m_state[1];
   unsigned int c = m_state[2];
   unsigned int d = m_state[3];

   /* lets go */
   
   /* round 1 */
   FF ( md5::F, a, b, c, d, in[ 0 ],  s_round[ 0 ], s_table[ 0  ] );
   FF ( md5::F, d, a, b, c, in[ 1 ],  s_round[ 1 ], s_table[ 1  ] );
   FF ( md5::F, c, d, a, b, in[ 2 ],  s_round[ 2 ], s_table[ 2  ] );
   FF ( md5::F, b, c, d, a, in[ 3 ],  s_round[ 3 ], s_table[ 3  ] );
   FF ( md5::F, a, b, c, d, in[ 4 ],  s_round[ 0 ], s_table[ 4  ] );
   FF ( md5::F, d, a, b, c, in[ 5 ],  s_round[ 1 ], s_table[ 5  ] );
   FF ( md5::F, c, d, a, b, in[ 6 ],  s_round[ 2 ], s_table[ 6  ] );
   FF ( md5::F, b, c, d, a, in[ 7 ],  s_round[ 3 ], s_table[ 7  ] );
   FF ( md5::F, a, b, c, d, in[ 8 ],  s_round[ 0 ], s_table[ 8  ] );
   FF ( md5::F, d, a, b, c, in[ 9 ],  s_round[ 1 ], s_table[ 9  ] );
   FF ( md5::F, c, d, a, b, in[ 10 ], s_round[ 2 ], s_table[ 10 ] );
   FF ( md5::F, b, c, d, a, in[ 11 ], s_round[ 3 ], s_table[ 11 ] );
   FF ( md5::F, a, b, c, d, in[ 12 ], s_round[ 0 ], s_table[ 12 ] );
   FF ( md5::F, d, a, b, c, in[ 13 ], s_round[ 1 ], s_table[ 13 ] );
   FF ( md5::F, c, d, a, b, in[ 14 ], s_round[ 2 ], s_table[ 14 ] );
   FF ( md5::F, b, c, d, a, in[ 15 ], s_round[ 3 ], s_table[ 15 ] );

   /* round 2 */
   FF ( md5::G, a, b, c, d, in[ 1  ], s_round[ 4 ], s_table[ 16 ] );
   FF ( md5::G, d, a, b, c, in[ 6  ], s_round[ 5 ], s_table[ 17 ] );
   FF ( md5::G, c, d, a, b, in[ 11 ], s_round[ 6 ], s_table[ 18 ] );
   FF ( md5::G, b, c, d, a, in[ 0  ], s_round[ 7 ], s_table[ 19 ] );
   FF ( md5::G, a, b, c, d, in[ 5  ], s_round[ 4 ], s_table[ 20 ] );
   FF ( md5::G, d, a, b, c, in[ 10 ], s_round[ 5 ], s_table[ 21 ] );
   FF ( md5::G, c, d, a, b, in[ 15 ], s_round[ 6 ], s_table[ 22 ] );
   FF ( md5::G, b, c, d, a, in[ 4  ], s_round[ 7 ], s_table[ 23 ] );
   FF ( md5::G, a, b, c, d, in[ 9  ], s_round[ 4 ], s_table[ 24 ] );
   FF ( md5::G, d, a, b, c, in[ 14 ], s_round[ 5 ], s_table[ 25 ] );
   FF ( md5::G, c, d, a, b, in[ 3  ], s_round[ 6 ], s_table[ 26 ] );
   FF ( md5::G, b, c, d, a, in[ 8  ], s_round[ 7 ], s_table[ 27 ] );
   FF ( md5::G, a, b, c, d, in[ 13 ], s_round[ 4 ], s_table[ 28 ] );
   FF ( md5::G, d, a, b, c, in[ 2  ], s_round[ 5 ], s_table[ 29 ] );
   FF ( md5::G, c, d, a, b, in[ 7  ], s_round[ 6 ], s_table[ 30 ] );
   FF ( md5::G, b, c, d, a, in[ 12 ], s_round[ 7 ], s_table[ 31 ] );

   /* round 3 */
   FF ( md5::H, a, b, c, d, in[ 5  ], s_round[ 8  ], s_table[ 32 ] );
   FF ( md5::H, d, a, b, c, in[ 8  ], s_round[ 9  ], s_table[ 33 ] );
   FF ( md5::H, c, d, a, b, in[ 11 ], s_round[ 10 ], s_table[ 34 ] );
   FF ( md5::H, b, c, d, a, in[ 14 ], s_round[ 11 ], s_table[ 35 ] );
   FF ( md5::H, a, b, c, d, in[ 1  ], s_round[ 8  ], s_table[ 36 ] );
   FF ( md5::H, d, a, b, c, in[ 4  ], s_round[ 9  ], s_table[ 37 ] );
   FF ( md5::H, c, d, a, b, in[ 7  ], s_round[ 10 ], s_table[ 38 ] );
   FF ( md5::H, b, c, d, a, in[ 10 ], s_round[ 11 ], s_table[ 39 ] );
   FF ( md5::H, a, b, c, d, in[ 13 ], s_round[ 8  ], s_table[ 40 ] );
   FF ( md5::H, d, a, b, c, in[ 0  ], s_round[ 9  ], s_table[ 41 ] );
   FF ( md5::H, c, d, a, b, in[ 3  ], s_round[ 10 ], s_table[ 42 ] );
   FF ( md5::H, b, c, d, a, in[ 6  ], s_round[ 11 ], s_table[ 43 ] );
   FF ( md5::H, a, b, c, d, in[ 9  ], s_round[ 8  ], s_table[ 44 ] );
   FF ( md5::H, d, a, b, c, in[ 12 ], s_round[ 9  ], s_table[ 45 ] );
   FF ( md5::H, c, d, a, b, in[ 15 ], s_round[ 10 ], s_table[ 46 ] );
   FF ( md5::H, b, c, d, a, in[ 2  ], s_round[ 11 ], s_table[ 47 ] );

   /* round 4 */
   FF ( md5::I, a, b, c, d, in[ 0  ], s_round[ 12 ], s_table[ 48 ] ); 
   FF ( md5::I, d, a, b, c, in[ 7  ], s_round[ 13 ], s_table[ 49 ] ); 
   FF ( md5::I, c, d, a, b, in[ 14 ], s_round[ 14 ], s_table[ 50 ] ); 
   FF ( md5::I, b, c, d, a, in[ 5  ], s_round[ 15 ], s_table[ 51 ] ); 
   FF ( md5::I, a, b, c, d, in[ 12 ], s_round[ 12 ], s_table[ 52 ] );
   FF ( md5::I, d, a, b, c, in[ 3  ], s_round[ 13 ], s_table[ 53 ] );
   FF ( md5::I, c, d, a, b, in[ 10 ], s_round[ 14 ], s_table[ 54 ] );
   FF ( md5::I, b, c, d, a, in[ 1  ], s_round[ 15 ], s_table[ 55 ] );
   FF ( md5::I, a, b, c, d, in[ 8  ], s_round[ 12 ], s_table[ 56 ] );
   FF ( md5::I, d, a, b, c, in[ 15 ], s_round[ 13 ], s_table[ 57 ] );
   FF ( md5::I, c, d, a, b, in[ 6  ], s_round[ 14 ], s_table[ 58 ] );
   FF ( md5::I, b, c, d, a, in[ 13 ], s_round[ 15 ], s_table[ 59 ] );
   FF ( md5::I, a, b, c, d, in[ 4  ], s_round[ 12 ], s_table[ 60 ] );
   FF ( md5::I, d, a, b, c, in[ 11 ], s_round[ 13 ], s_table[ 61 ] );
   FF ( md5::I, c, d, a, b, in[ 2  ], s_round[ 14 ], s_table[ 62 ] );
   FF ( md5::I, b, c, d, a, in[ 9  ], s_round[ 15 ], s_table[ 63 ] );   

   
   /* add a, b, c, d to m_state */
   m_state[0] += a;
   m_state[1] += b;
   m_state[2] += c;
   m_state[3] += d;
}


std::string md5::hex_digest( void )
{
   int i;
   std::stringstream result;
   
   result.setf( std::ios::hex, std::ios::basefield );
   result.width( 2 );
   result.fill( '0' );
   
   if ( ! m_bPerformed )
   {
      this->perform();
   }
   
   for (i = 0; i < 16; i++)
   {
      result << (unsigned int)( m_digest[i] );
   }
  
  return result.str();
}


void md5::digest( unsigned char output[16] )
{
   if ( ! m_bPerformed )
   {
      this->perform();
   }
   
   memcpy( output, m_digest, sizeof(char)*16 );
}


void md5::decode ( unsigned char* output, unsigned int *input, unsigned int length )
{
   unsigned int i, j;

   for (i = 0, j = 0; i < length; i++, j += 4) 
   {
      output[j]   = (unsigned char)( input[i] & 0xFF );
      output[j+1] = (unsigned char)((input[i] >> 8 ) & 0xFF );
      output[j+2] = (unsigned char)((input[i] >> 16) & 0xFF );
      output[j+3] = (unsigned char)((input[i] >> 24) & 0xFF );
  }
  
}

void md5::encode( unsigned int* output, unsigned char *input, unsigned int length )
{
   unsigned int i,j;
   
   for (i = 0, j = 0; i < length; i++, j += 4)
   {
       output[i] = ( 
         ((unsigned int)( input[j])) |
         ((unsigned int)( input[j+1] << 8  )) |
         ((unsigned int)( input[j+2] << 16 )) |
         ((unsigned int)( input[j+3] << 24 )) 
      );
  }
}
   
   
   
