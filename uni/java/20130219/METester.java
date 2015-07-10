/**
  * FONDAMENTI DI INFORMATICA - CANALE 4 - A.A. 2012-13
  * Prova di Programmazione - 19-02-2013
  *
  * classe METester - classe di prova
  *
  * @author A. Luchetta
  * @version 4-02-2013
  */
import java.util.Scanner;
public class METester
{
   public static void main(String[] args) throws java.io.IOException
   {
      ME m = new ME();
      Scanner in = new Scanner(new java.io.FileReader(args[0]));
      
      while (in.hasNextLine())
      {
         Scanner tok = new Scanner(in.nextLine());
         m.put(tok.next(), tok.next());         
      }
      in.close();
      
      Object[] k = m.sortedKeys();
      Object[] v = m.values();       
 
      System.out.println("size " + m.size() + "\n");

      for (int i = 0; i < k.length; i++) 
         System.out.println("key " + i + " " + k[i]);
      System.out.println();
              
      for (int i = 0; i < v.length; i++) 
         System.out.println("val " + i + " " + v[i]);   
      System.out.println();
          
      int i = 0;
      while (!m.isEmpty())
      {
         System.out.println("get " + i + " " + k[i] + "-> " + m.get(k[i]));
         System.out.println("rem " + i + " " + k[i] + "-> " + m.remove(k[i++]));
      }
      
      System.out.println("\nsize " + m.size());      
   }
}
