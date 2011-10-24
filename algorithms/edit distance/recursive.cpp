/* RECURSIVE ALGORITHM */

// ritorna il minore tra a, b e c
template< class T >
inline static T min3( T a, T b, T c )
{
    return std::min( a, std::min( b, c ) );
}

uint32_t WLD_recusive::distance( const std::string& first, const std::string& second )
{
   return internal_distance( first.c_str(), second.c_str() );
}

uint32_t WLD_recusive::internal_distance( const char* first, const char* second )
{
   if( *first == '\0' )
   {
      // se la prima stringa è nulla, allora bisogna togliere tanti caratteri
      // quanti quelli nella seconda stringa
      return std::strlen( second ) * getDeletionW();
   }
   if ( *second == '\0' )
   {
      // se la seconda stringa è nulla, allora bisogna aggiungere tanti caratteri
      // quanti quelli nella prima stringa
      return std::strlen( first ) * getInsertionW();
   }
   
   const char* firstInc = first + 1;
   const char* secondInc = second + 1;
   
   // se i due caratteri combaciano, mismatch sarà uguale a 0
   // e quindi il costo di sostituzione non verrà calcolato
   // ( essendo 0 elemento assorbente rispetto a  * )
   bool mismatch = ( first[0] != second[0] );
   
   return min3
   ( 
      internal_distance( firstInc, secondInc ) + ( mismatch * getSubstitionW() ),
      internal_distance( firstInc, second    ) + getInsertionW(),
      internal_distance( first,    secondInc ) + getDeletionW()
   );
}
