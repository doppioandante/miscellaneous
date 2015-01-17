public interface Queue //--ADT Coda
{  /**
      restituisce true se la coda e' vuota, false altrimenti
      @return true se la coda e' vuota, false altrimenti
   */ boolean isEmpty();

   /**
      restituisce il numero di elementi presenti nella coda
      @return il numero di elementi presenti nella coda
   */ int size();

   /**
      inserisce l'elemento specificato in coda
      @param x l'elemento specificato
   */ void enqueue(Object x);

   /**
      estrae l'elemento in fronte alla coda, se presente
      @return x l'elemento in fronte alla coda
      @throws EmptyQueueException se la coda e' vuota
   */ Object dequeue() throws EmptyQueueException;
}
