public interface Dictionary  //--ADT Dizionario
{  /**@return numero di associazioni contenute nel dizionario
   */ int size();

   /**inserisce nel dizionario l'associazione di chiave e valore specificati.
      @param key la chiave specificata
      @param value il valore specificato
      @throws IllegalArgumentException se key o value valgono null
   */ void insert(Comparable key, Comparable value);
   
   /**rimuove dal dizionario una delle associazione di chiave specificata 
      @param key la chiave specificata
      @return il valore dell'associazione rimossa se la chiave specificata e' 
              presente, null altrimenti
   */ Object remove(Object key);
   
   /**restituisce il valore di una delle associazione di chiave specificata
      presenti nel dizionario 
      @param key la chiave specificata
      @return il valore di una delle associazione di chiave specificata se la
              chiave e' presente, null altrimenti
   */ Object find(Object key);         
   
   /**restituisce tutti valori associati nel dizionario alla chiave specificata
      @param key la chiave specificata
      @return un array contenente tutti i valori associati alla chiave
              specificata ordinati in senso lessicografico crescente se la
              chiave e' presente, un array di dimensione nulla altrimenti.
              L'array deve avere dimensione pari al numero di associazioni
              di chiave specificata presenti.
              NB per restituire un array di oggetti di dimensione nulla:
              return new Object[0];              
   */ Object[] findAll(Object key);

   /**rimuove dal dizionario tutte le associazioni di chiave specificata
      @param key la chiave specificata
      @return un array contenente tutti i valori delle associazioni rimosse 
              dal dizionario, ordinati in senso lessicografico crescente se la
              chiave e'presente, un array di dimensione nulla altrimenti
              L'array deve avere dimensione pari al numero di associazioni 
              rimosse di chiave specificata.              
              NB per restituire un array di oggetti di dimensione nulla:
                 return new Object[0];
   */ Object[] removeAll(Object key);   

   /**@return un array contenente le chiavi del dizionario in unico esemplare se
              la chiave e' multipla, ordinate in senso lessicografico crescente. 
   */ Object[] keys();
}
