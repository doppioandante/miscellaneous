public class Q implements Queue
{
   class ListNode
   {
      private Object value;
      private ListNode next;
      private ListNode prev;

      public ListNode(Object value, ListNode next, ListNode prev)
      {
         this.value = value;
         this.next = next;
         this.prev = prev;
      }

      public ListNode getNext()
      {
         return this.next;
      }

      public void setNext(ListNode next)
      {
         this.next = next;
      }
      
      public ListNode getPrev()
      {
         return this.prev;
      }

      public void setPrev(ListNode prev)
      {
         this.prev = prev;
      }

      public void setValue(Object value)
      {
         this.value = value;
      }

      public Object getValue()
      {
         return this.value;
      }

   }

   private ListNode head;
   private ListNode tail;

   public Q()
   {
      head = new ListNode(null, null, null);
      tail = head;
   }

   public boolean isEmpty()
   {
      return head == tail;
   }

   public int size()
   {
      int result = 0;
      for (ListNode it = head; it != tail; it = it.getNext())
      {
         result++;
      }

      return result;
   }

   public void enqueue(Object x) throws IllegalArgumentException
   {
      if (x == null)
      {
         throw new IllegalArgumentException("Cannot enqueue null element");
      }

      // Insert at front
      ListNode newHead = new ListNode(null, head, null);
      head.setValue(x);
      head.setPrev(newHead);
      head = newHead;
   }

   public Object front() throws EmptyQueueException
   {
      if (isEmpty())
      {
         throw new EmptyQueueException("Queue is empty");
      }

      return head.getNext().getValue();
   }

   public Object dequeue() throws EmptyQueueException
   {
      if (isEmpty())
      {
         throw new EmptyQueueException("Queue is empty");
      }

      // Remove tail node
      Object tailValue = tail.getValue();
      ListNode newTail = tail.getPrev();
      tail.setPrev(null); // Avoid having dangling references
      newTail.setNext(null);

      tail = newTail;

      return tailValue;
   }

   public Object[] toArray()
   {
      Object[] content = new Object[size()]; // O(n)
      int i = 0;
      for (ListNode it = head.getNext(); it != null; it = it.getNext())
      {
         content[i++] = it.getValue();
      }

      return content;
   }
}
