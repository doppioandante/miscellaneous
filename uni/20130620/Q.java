public class Q implements Queue
{
   private Deque mDeque;
   
   public Q()
   {
      mDeque = new D();
   }
   
   @Override
   public boolean isEmpty()
   {
      return mDeque.isEmpty();
   }
   
   @Override
   public int size()
   {
      return mDeque.size();
   }
   
   @Override
   public void enqueue(Object value)
   {
      mDeque.addLast(value);
   }
   
   @Override
   public Object dequeue() throws EmptyQueueException
   {
      try
      {
         return mDeque.removeFirst();
      }
      catch (EmptyDequeException e)
      {
         throw new EmptyQueueException();
      }
   }
}
