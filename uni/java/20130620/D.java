public class D implements Deque 
{
   class ListNode
   {
      private Object mValue;
      private ListNode mPrev;
      private ListNode mNext;
      
      public ListNode(Object value, ListNode prev, ListNode next)
      {
         mValue = value;
         mPrev = prev;
         mNext = next;
      }
      
      public void setNext(ListNode next)
      {
         mNext = next;
      }
      
      public ListNode getNext()
      {
         return mNext;
      }
      
      public void setPrev(ListNode prev)
      {
         mPrev = prev;
      }
      
      public ListNode getPrev()
      {
         return mPrev;
      }
      
      public void setValue(Object value)
      {
         mValue = value;
      }
      
      public Object getValue()
      {
         return mValue;
      }
   }

   private ListNode mHead, mTail;
   private int mSize;

   public D()
   {
      mHead = new ListNode(null, null, null);
      mTail = mHead;
      
      mSize = 0;
   }
   
   @Override
   public boolean isEmpty()
   {
      return mHead == mTail; // return size() == 0;
   }
   
   @Override
   public int size()
   {
      return mSize;
   }
   
   @Override
   public void addFirst(Object value)
   {
      ListNode newHead = new ListNode(null, null, mHead);

      mHead.setPrev(newHead);
      mHead.setValue(value);
      mHead = newHead;
      
      mSize++;
   }
   
   @Override
   public void addLast(Object value)
   {
      ListNode newNode = new ListNode(value, mTail, null);
      mTail.setNext(newNode);
      mTail = newNode;
      
      mSize++;
   }
   
   @Override
   public Object removeFirst() throws EmptyDequeException
   {
      if (isEmpty())
      {
         throw new EmptyDequeException();
      }
      
      ListNode toRemove = mHead.getNext();
      Object value = toRemove.getValue();
      mHead.setNext(toRemove.getNext());
      
      if (toRemove == mTail)
      {
         mTail = mHead;
      }
      else
      {
         toRemove.getNext().setPrev(mHead);
      }
      
      mSize--;
      
      return value;
   }
   
   @Override
   public Object removeLast() throws EmptyDequeException
   {
      if (isEmpty())
      {
         throw new EmptyDequeException();
      }
      
      ListNode newTail = mTail.getPrev();
      Object value = mTail.getValue();
      mTail = newTail;
      
      mSize--;
      return value;
   }
   
   private void print()
   {
      System.out.print("1: ");
      for (ListNode it = mHead; it != null; it = it.getNext())
      {
         System.out.print(it.getValue());
      }
      System.out.println();
      System.out.print("2: ");
      for (ListNode it = mTail; it != null; it = it.getPrev())
      {
         System.out.print(it.getValue());
      }
      System.out.println();
  }
}
