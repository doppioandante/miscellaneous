
/**
 * Aggiungi qui una descrizione della classe LinkedList
 * 
 * @author (il tuo nome) 
 * @version (un numero di versione o una data)
 */
public class MLinkedList
{
    // variabili d'istanza - sostituisci l'esempio che segue con il tuo
    private ListNode head;
    private ListNode tail;

    /**
     * Costruttore degli oggetti di classe  LinkedList
     */
    class ListNode
    {
        private Object key, value;
        private ListNode next;
        
        public ListNode(Object key, Object value, ListNode next)
        {
            setKey(key);
            setValue(value);
            setNext(next);
        }
        
        public void setKey(Object key)
        {
            this.key = key;
        }
        
        public Object getKey()
        {
            return this.key;
        }
    
        public void setValue(Object value)
        {
            this.value = value;
        }
        
        public Object getValue()
        {
            return this.value;
        }
        
        public void setNext(ListNode next)
        {
            this.next = next;
        }
        
        public ListNode getNext()
        {
            return this.next;
        }
    }
    
    public MLinkedList() 
    {
        this.head = new ListNode(null, null, null);
        this.tail = head;
    }
    
    public void insertFront(Object key, Object value)
    {
        head.setValue(value);
        head.setKey(key);
        ListNode newHead = new ListNode(null, null, head);
        head = newHead;
    }
    
    public Object findKey(Object key)
    {
        for (ListNode it = head.getNext(); it != null; it = it.getNext())
        {
            if (it.getKey().equals(key))
            {
                return it.getValue();
            }
        }
        
        return null;
    }
    
    public Object removeKey(Object key)
    {
        ListNode previous = head;
        Object entryValue = null;

        for (ListNode it = head.getNext(); it != null; it = it.getNext())
        {
            if (it.getKey().equals(key))
            {
                previous.setNext(it.getNext());
                it.setNext(null);
                entryValue = it.getValue();
                break;
            }
            
            previous = it;
        }
      
        
        return entryValue;
    }
    
    public int storeTo(Object[] array, int offset, int what)
    {
        for (ListNode it = head.getNext(); it != null; it = it.getNext())
        {
            Object toStore = null;
            if (what == STORE_KEY)
            {
                toStore = it.getKey();
            }
            else if (what == STORE_VALUE)
            {
                toStore = it.getValue();
            }
            else
            {
                assert(false);
            }
            array[offset++] = toStore;
        }
        
        return offset;
    }
    
    public static int STORE_KEY = 1;
    public static int STORE_VALUE = 2;
}
