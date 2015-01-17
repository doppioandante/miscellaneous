public class QE extends Q
{
   public QE()
   {
      super();    
   }

   public Object[] toSortedArray()
   {
      Object[] array = toArray();
      mergeSort(array);
      return array;
   }

   public void enqueue(Object x)
   {
      if (x instanceof Comparable)
      {
         super.enqueue(x);
      }
      else
      {
         throw new IllegalArgumentException();
      }
   }

   public Object[] toSet()
   {
      Object[] sorted = toSortedArray();
      if (sorted.length == 0)
      {
         return sorted;
      }

      Object[] set = new Object[sorted.length];

      set[0] = sorted[0];
      int setIndex = 1;
      for (int i=1; i < sorted.length; i++)
      {
         if (!sorted[i].equals(set[setIndex-1]))
         {
            set[setIndex++] = sorted[i];
         }
      }

      Object[] result = new Object[setIndex];
      System.arraycopy(set, 0, result, 0, result.length);

      return result;
   }

   private static void mergeSort(Object[] array)
   {
      if (array.length <= 1)
      {
         return;
      }
      int mid = array.length / 2;

      Object[] left = new Object[mid];
      System.arraycopy(array, 0, left, 0, left.length);
      Object[] right = new Object[array.length-mid];
      System.arraycopy(array, mid, right, 0, right.length);
      mergeSort(left);
      mergeSort(right);
      
      // merging
      int leftIndex = 0;
      int rightIndex = 0;
      int i = 0;
      while (leftIndex < left.length && rightIndex < right.length)
      {
         Object toStore;
         if (((Comparable)left[leftIndex]).compareTo(right[rightIndex]) <= 0)
         {
            // we want the smallest element
            toStore = left[leftIndex++];
         }
         else
         {
            toStore = right[rightIndex++];
         }
         array[i++] = toStore;
      }

      while (leftIndex < left.length)
      {
         array[i++] = left[leftIndex++];
      }

      while (rightIndex < right.length)
      {
         array[i++] = right[rightIndex++];
      }
   }
}
