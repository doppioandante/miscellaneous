/**
  realizza l'interfaccia Stack usando internamente un array riempito parzialmente a ridimensionamento dinamico
  @author Adriano Luchetta
  @version 16-Nov-2003
  @version 27-Nov-2004
  @version 21-Nov-2005
  @version 10-Gen-2009
 */

public class ArStack implements Stack
{
   //parte privata
   private Object[] v;
   private int vSize;
   
   public ArStack()
   {
      v = new Object[1];
      vSize = 0;
   }
   
   /**
     O(1)
   */
   public boolean isEmpty()
   {
      return vSize == 0;
   }

   /**
     O(1)
   */
   public int size()
   {
      return vSize;
   }

   /**
     in media O(1)
   */
   public void push(Object obj)
   {
      if (vSize == v.length)
      {
         Object[] newv = new Object[2 * v.length];
         for (int i = 0; i < v.length; i++)
            newv[i] = v[i];
         v = newv;
      }
            
      v[vSize] = obj;
      vSize++;
   }

   /**
     O(1)
   */
   public Object top() throws EmptyStackException
   {
      if (isEmpty())
         throw new EmptyStackException();

      return v[vSize - 1];
   }

   /**
     O(1)
   */
   public Object pop() throws EmptyStackException
   {
      Object obj = top();
      v[vSize-1] = null;
      vSize--;
      return obj;
   }
}

