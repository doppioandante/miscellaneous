public class ME extends M
{  
   public ME() 
   {
       super();
   }
   
   public void put(String key, Object value)
   {
       try
       {
           Object old = super.remove(key);
           super.put(key, old + " " + value);
       }
       catch (java.util.NoSuchElementException e)
       {
           super.put(key, value);
       }
   }
   
   @Override
   public void put(Comparable key, Object value)
   {
       if (key instanceof String)
       {
           put((String) key, value);
       }
       else
       {
           throw new IllegalArgumentException();
       }
   }
   
   public Object[] sortedKeys()
   {
       Object[] array = keys();
       mergeSort(array);
       return array;
   }
    
   public Object[] values()
   {
       return super.values();
   }
   
   private static void mergeSort(Object[] array)
   {
       if (array.length <= 1)
       {
           return;
       }
       
       int mid = array.length / 2;
       
       Object[] left = new Object[mid];
       Object[] right = new Object[array.length - mid];
       
       System.arraycopy(array, 0, left, 0, left.length);
       System.arraycopy(array, mid, right, 0, right.length);
       
       mergeSort(left);
       mergeSort(right);
       
       merge(array, left, right);
   }
   
   private static void merge(Object[] array, Object[] left, Object[] right)
   {
       final int mid = array.length / 2;
       
       int leftIndex = 0;
       int rightIndex = 0;
       int i = 0;
       
       while (leftIndex < mid && rightIndex < (array.length - mid))
       {
           Comparable cp = (Comparable) left[leftIndex];
           if (cp.compareTo(right[rightIndex]) <= 0)
           {
               array[i++] = left[leftIndex++];
           }
           else
           {
               array[i++] = right[rightIndex++];
           }
       }
       
       while (leftIndex < mid)
       {
           array[i++] = left[leftIndex++];
       }
       
       while (rightIndex < (array.length - mid))
       {
           array[i++] = right[rightIndex++];
       }
    }
}
