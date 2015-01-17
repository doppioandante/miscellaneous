/**
  * FONDAMENTI DI INFORMATICA - CANALE 4 - A.A. 2012-13
  * Prova di Programmazione - 30-01-2013
  *
  * interfaccia Queue - definisce una coda, ovvero un contenitore di elementi
  * generici avente modalita' di accesso FIFO (First In First Out)
  *
  * @author A. Luchetta
  * @version 17-01-2013
  */
public interface Queue  // ADT Coda
{
   /**
      @return true se la coda e' vuota, false altrimenti
   */
   boolean isEmpty();
   
   /**
      @return numero di elementi presenti nella coda
   */
   int size();
   
   /**
      inserisce l'elemento nella coda
      @param x l'elemento da inserire nella coda
      @throws java.lang.IllegalArgumentException se x vale null
   */   
   void enqueue(Object x);
   
   /**
      ispeziona l'elemento in fronte alla coda
      @return l'elemento in fronte alla coda
      @throws EmptyQueueException se la coda e' vuota
   */
   Object front() throws EmptyQueueException;
   
   /**
      rimuove l'elemento in fronte alla coda
      @return l'elemento in fronte alla coda
      @throws EmptyQueueException se la coda e' vuota
   */   
   Object dequeue() throws EmptyQueueException;
   
   /**
      @return un array pieno contenente gli elementi presenti nella coda,
      in sequenza FIFO, con l'ultimo elemento inserito nella coda posto
      all'indice 0 dell'array.
   */
   Object[] toArray();    
}
