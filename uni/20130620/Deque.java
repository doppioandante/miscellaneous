public interface Deque  // ADT Coda Doppia
{  /**
      @return true se la coda doppia e' vuota, false altrimenti
   */ boolean isEmpty();
   
   /**
      @return numero di elementi presenti nella coda doppia
   */ int size();
   
   /**
      inserisce l'elemento specificato come primo elemento della coda doppia 
      @param x elemento specificato
   */ void addFirst(Object x);
   
   /**
      inserisce l'elemento specificato come ultimo elemento della coda doppia
      @param x elemento specificato
   */ void addLast(Object x); 
   
   /**
      estrae il primo elemento della coda doppia, se presente
      @return l'elemento al primo posto della coda doppia, se presente
      @throws EmptyDequeException se la coda e' vuota
   */ Object removeFirst() throws EmptyDequeException;
   
   /**
      estrae l'ultimo elemento della coda doppia, se presente
      @return l'elemento all'ultimo posto della coda doppia, se presente
      @throws EmptyDequeException se la coda doppia e' vuota
   */ Object removeLast() throws EmptyDequeException;               
}
