/**
  * FONDAMENTI DI INFORMATICA - CANALE 4 - A.A. 2012-13
  * Prova di Programmazione - 19-02-2013
  *
  * interfaccia Map - definisce una mappa, ovvero un contenitore di associazioni
  * chiave/valore con chiave univoca.
  *
  * @author A. Luchetta
  * @version 4-02-2013
  */
public interface Map  // ADT Mappa
{
   /**
      @return true se la mappa e' vuota, false altrimenti
   */
   boolean isEmpty();
   
   /**
      @return numero di associazioni presenti nella mappa
   */
   int size();
   
   /**
      inserisce nella mappa l'associazione di chiave e valore specificati 
      @param key chiave specificata
      @param value valore specificato
      @throws java.lang.IllegalArgumentException se key vale null
   */  
   void put(Comparable key, Object value);
   
   /**
      @param key chiave specificata
      @return il valore associato alla chiave specificata, se un'associazione
              di chiave specificata e' presente nella mappa.
      @throws java.util.NoSuchElementException se l'associazione di chiave
              specificata non e' presente nella mappa.
   */
   Object get(Object key) throws java.util.NoSuchElementException;
   
   /**
      rimuove l'associazione di chiave specificata, se presente
      @param key chiave specificata
      @return il valore associato alla chiave specificata, se presente
      @throws java.util.NoSuchElementException se l'associazione di chiave
              specificata non e' presente nella mappa.
   */   
   Object remove(Object key) throws java.util.NoSuchElementException;
   
   /**
      @return un array contenente le chiavi presenti nella mappa. La dimensione
              dell'array e' pari al numero di associazioni presenti nella mappa
   */
   Object[] keys();    
}
