/**
  * FONDAMENTI DI INFORMATICA - CANALE 4 - A.A. 2012-13
  * Simulazione della Prova di Programmazione - 17-01-2013
  *
  * classe QETester - classe di prova
  * 
  * @author A. Luchetta
  * @version 15-01-2013
  */
import java.util.Scanner;
public class QETester
{
   public static void main(String[] args)  
   {
      Scanner in = new Scanner(System.in);
      QE q = new QE();
   
      // prova del metodo push()
      while (in.hasNextLine())
         q.enqueue(in.nextLine());
      
      in.close();
         
      // prova del metodo size()
      System.out.println("\nsize: " + q.size());
          
      Object[] a = q.toArray();
      Object[] b = q.toSortedArray();
      Object[] c = q.toSet();   
      
      // prova dei metodi top() e pop()
      int j = 0;
      while (!q.isEmpty())
      {
         System.out.println("front: " + q.front());
         System.out.println("dequeue: " + q.dequeue());
      }
      System.out.println();

      // prova del metodo size()
      System.out.println("size: " + q.size());
      System.out.println();      
   
      // prova del metodo toArray
      for (int i = 0; i < a.length; i++)
         System.out.println("toArray: " + i + " " + a[i]);
      System.out.println();   
         
      // prova del metodo toSortedArray
      for (int i = 0; i < b.length; i++)
         System.out.println("toSortedArray: " + i + " " + b[i]);         
      System.out.println();
      
       // prova del metodo toSet
      System.out.println("toSet size" + " " +c.length);
      for (int i = 0; i < c.length; i++)
         System.out.println("toSet: " + i + " " + c[i]);
      System.out.println();  
   }     
}  
