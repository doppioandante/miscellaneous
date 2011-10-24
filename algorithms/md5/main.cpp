#include "md5.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace option
{
const char *help = "help";
const char *file = "file";
const char *string = "string";
const char *checksum = "checksum";
}

void help( void );

int main( int argc, char *argv[] )
{
   if ( argc < 2 )
   {
      help();
      return 1;
   }
   
   vector< string > args( argv+1, argv+argc );
   
   if ( args[0] == option::help )
   {
      help();
   }
   
   else if ( args[0] == option::file )
   {
      if ( argc < 3 )
      {
         help();
         return 1;
      }
      md5 hash;
      ifstream in;
      in.open( args[1].c_str(), ios::binary );
      hash << in;
      cout << "Result: " << hash.hex_digest() << endl;
   }
   
   else if( args[0] == option::string )
   {
      md5 hash;
      if ( argc == 2 )
      {
         string str;
         cin >> str;
         hash << str;
      }
      else
      {
         hash << args[1];
      }
      
      cout << "Result: " << hash.hex_digest() << endl;
   }
   
   else if( args[0] == option::checksum )
   {
      if ( argc < 4 )
      {
         help();
         return 1;
      }
      md5 hash;
      ifstream in;
      in.open( args[1].c_str(), ios::binary );
      hash << in;
      if ( hash.hex_digest() == args[2] )
      {
         cout << "The hashes correspond" << endl;
      }
      else
      {
         cout << "The hashes don't correspond" << endl;
      }
   }
   
   return 0;
}

void help()
{
   cout << "Option: " << endl;
   cout << "\thelp:   shows this help" << endl;
   cout << "\tstring <s>:   crypt <s> if specified; else, get crypt the string read from stdin" << endl;
   cout << "\tfile <f>:   crypt the file <f>" << endl;
   cout << "\tchecksum <file> <hash>:  perform checksum on the file and the hash" << endl;
}
