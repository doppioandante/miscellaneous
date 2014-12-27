/**
  * Tipo di dati astratto con modalita' di accesso LIFO
  * author Goodrich - Tamassia
  * @see Container
  * @see EmptyStackException
*/
public interface Stack extends Container
{  /**
      inserisce un elemento in cima alla pila
      @param obj l'elemento da inserire
   */
   void push(Object obj);

   /**
      rimuove l'elemento dalla cima della pila
      @return l'elemento rimosso
      @throws EmptyStackException se la pila e' vuota
   */  
   Object pop() throws EmptyStackException;

   /**
      ispeziona l'elemento in cima alla pila
      @return l'elemento in cima alla pila
      @throws EmptyStackException se la pila e' vuota
   */ 
   Object top() throws EmptyStackException;
}
