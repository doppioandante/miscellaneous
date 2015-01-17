import java.util.Scanner;
public class QTester
{  public static void main(String[] args)
   {
      Scanner in = new Scanner(System.in);
      Q q = new Q();
      
      while (in.hasNext())
         q.enqueue(in.next());
      in.close();   
         
      System.out.println("size: " + q.size());
      
      int n = 0;
      while (!q.isEmpty())
         System.out.println(++n + ": " + q.dequeue());
      
       System.out.println("size: " + q.size());
       
       try{
          q.dequeue();
       }
       catch (EmptyQueueException e) {
          System.out.println("OK");       
       }      
       catch (EmptyDequeException e) {
          System.out.println("KO");
       }                      
   }
}
