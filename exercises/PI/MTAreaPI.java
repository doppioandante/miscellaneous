import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Callable;
import java.util.concurrent.Future;
import java.util.LinkedList;

public class MTAreaPI implements Callable<Long>
{
   private long xstart;
   private long xend;
   private long radius;

   MTAreaPI(long radius, long xstart, long xend)
   {
      this.xstart = xstart;
      this.xend = xend;
      this.radius = radius;
   }

   @Override
   public Long call()
   {
      long rsquared = radius * radius;
      long count = 0; 
      long j = radius;
      for(long i = xstart; i < xend; i++)
      {
         for(; j >= 0; j--) 
         {
            if(vector2Length(i, j) <= rsquared)
            {
               count += j;
               break;
            }
         }
      }

      return count;
   }

   public static double getPI(long precision)
   {
      int parallelism = Runtime.getRuntime().availableProcessors();
      ExecutorService pool = Executors.newFixedThreadPool(parallelism);
      
      LinkedList<Future<Long>> futures = new LinkedList<Future<Long>>();
      long taskSize = precision / parallelism;
      int i;
      for(i = 0; i < parallelism - 1; i++)
      {
          futures.add(pool.submit(new MTAreaPI(precision, i * taskSize, (i+1) * taskSize)));
      }
      futures.add(pool.submit(new MTAreaPI(precision, i * taskSize, precision)));

      pool.shutdown();

      long discreteArea = 0;
      try
      {
         for(Future<Long> f: futures)
	 {
	    discreteArea += f.get().longValue();
	 }
      }
      catch(Exception e)
      {
         System.err.println("die badly");
      }

      return 4.0*((double)discreteArea/precision/precision);
   }
   
   private static long vector2Length(long x, long y)
   {
      return x*x + y*y;
   }
}
