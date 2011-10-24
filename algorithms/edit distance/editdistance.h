#ifndef EDITDISTANCE_H
#define EDITDISTANCE_H

#include <iterator>
#include <algorithm>

typedef unsigned int uint;

template< class T >
inline static T min3( T a, T b, T c )
{
    return std::min( a, std::min( b, c ) );
}

template< class T = uint >
struct EditDistance
{
   typedef T       weight_type;

   // costruttore
   // sub: peso per la sostituzione
   // ins: peso per l'inserimento
   // del: peso per il cancellamento
   EditDistance( weight_type sub, weight_type ins, weight_type del ):
      m_sub( sub ),
      m_ins( ins ),
      m_del( del )
   { }

   weight_type getSubstitutionW() const
   {
      return m_sub;
   }

   weight_type getInsertionW() const
   {
      return m_ins;
   }

   weight_type getDeletionW() const
   {
      return m_del;
   }

   // implementazione della distanza di Levenshtein
   // beg1, end1: range del primo dato
   // beg2, end2: range del secondo dato
   
   template< class InputIterator >
   weight_type distance(
       InputIterator beg1, InputIterator end1,
       InputIterator beg2, InputIterator end2 )
   {
      typedef typename std::iterator_traits<InputIterator>::value_type value_type;
      
      // calcolo la lunghezza dei due dati
      // che per convenienza, chiameremo stringhe
      uint rowLength = std::distance( beg2, end2 );
      uint columnLength = std::distance( beg1, end1 );

      // se la prima stringa e' vuota
      if( columnLength == 0 )
      {
          // devo eliminare tanti caratteri quanti ce ne sono nella seconda stringa
          return rowLength * getDeletionW();
      }

      // se la seconda stringa e' vuota
      if( rowLength == 0 )
      {
          // devo aggiungere tanti caratteri quanti ce ne sono nella prima stringa
          return columnLength * getInsertionW();
      }

      // se le stringhe hanno la stessa lunghezza 
      // e la sostituzione pesa meno di un cancellamento + un inserimento
      if( columnLength == rowLength &&
          getSubstitutionW() < ( getInsertionW() + getDeletionW() )
        )
      {
          // ritorno la distanza di Hamming tra le due stringhe
          return hammingDistance( beg1, end1, beg2, end2 );
      }

      // se siamo arrivati qui, usiamo rowLength e columnLength come grandezze 
      // della tabella che useremo per calcolare la distanza
      ++rowLength;
      ++columnLength;

      // la tabella 2x2 e' stata spezzata per convenienza in due array
      weight_type* firstRow = new weight_type[ rowLength ];
      weight_type* secondRow = new weight_type[ rowLength ];

      uint i,j;

      firstRow[0] = 0;

      for( i=1; i < rowLength; i++ )
      {
         firstRow[ i ] = i * getDeletionW();
      }

      for( i=1; i < columnLength; i++ )
      {
         value_type currentCh = *beg1++;
         secondRow[ 0 ] = i * getInsertionW();

         InputIterator base = beg2;

         for( j=1; j < rowLength; j++ )
         {
            bool mismatch = ( currentCh != *base++ );

            secondRow[ j ] = min3
            (
               firstRow[ j-1 ]  + ( mismatch * getSubstitutionW() ),
               firstRow[ j   ]  + getInsertionW(),
               secondRow[ j-1 ] + getDeletionW()
            );
         }

         std::swap( firstRow, secondRow );
      }

      // prendiamo il risultato dalla prima riga per via dello scambio
      delete[] secondRow;
      weight_type result = firstRow[ j-1 ];
      delete[] firstRow;

      return result;
   }
   
private:
   
   // implementazione della distanza di Hamming
   template< class InputIterator >
   weight_type hammingDistance(
       InputIterator beg1, InputIterator end1,
       InputIterator beg2, InputIterator end2 )
   {
       weight_type result = 0;
       for( ; beg1 != end1; beg1++, beg2++ )
       {
           result += static_cast< weight_type >( *beg1 != *beg2 );
       }

       result *= getSubstitutionW();

       return result;
   }

private:
   weight_type m_sub;
   weight_type m_ins;
   weight_type m_del;
};

#endif

