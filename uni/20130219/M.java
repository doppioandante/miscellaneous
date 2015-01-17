import java.util.NoSuchElementException;

public class M implements Map  // ADT Mappa
{  
    private MLinkedList[] table;
    private int size;
    
    public M() 
    {
        table = new MLinkedList[HASHTABLE_DIM];
        for (int i = 0; i < table.length; i++)
        {
            table[i] = new MLinkedList();
        }
        this.size = 0;
    }
    
    public boolean isEmpty()
    {
        return size() == 0;
    }
    
    public int size()
    {
        return this.size;
    }

    public void put(Comparable key, Object value)
    {
        if (key == null)
        {
            throw new IllegalArgumentException();
        }
        
        int index = hash(key);
        table[index].insertFront(key, value);
        size++;
    }
    
    public Object get(Object key) throws NoSuchElementException
    {
        int index = hash(key);
        Object value = table[index].findKey(key);
        if (value == null)
        {
            throw new NoSuchElementException();
        }
        
        return value;
    }
    
    public Object remove(Object key) throws java.util.NoSuchElementException
    {
        int index = hash(key);
        Object value = table[index].removeKey(key);
        if (value == null)
        {
            throw new NoSuchElementException();
        }
        
        size--;
        return value;
    }
    
    public Object[] keys()
    {
        Object[] result = new Object[size()];
        
        int index = 0;
        for (MLinkedList list : table)
        {
            index = list.storeTo(result, index, MLinkedList.STORE_KEY);
        }
        
        return result;
    }
    
    protected Object[] values()
    {
        Object[] result = new Object[size()];
        
        int index = 0;
        for (MLinkedList list : table)
        {
            index = list.storeTo(result, index, MLinkedList.STORE_VALUE);
        }
        
        return result;
    }
    
    private static int hash(Object o)
    {
        int hashCode = o.hashCode();
        if (hashCode < 0) hashCode = -hashCode;
       
        return hashCode % HASHTABLE_DIM;
    }
    
    private static int HASHTABLE_DIM = 10;
}  
