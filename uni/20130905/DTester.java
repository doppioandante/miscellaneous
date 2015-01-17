import java.util.Scanner; import java.io.FileReader; import java.io.IOException;
public class DTester
{  public static void main(String[] args) throws IOException
   {  Scanner in = new Scanner(new FileReader(args[0])); // per leggere da file
      Dictionary d = new D();                            // dizionario
      
      while (in.hasNext()) // lettura da file e inserimento associazioni
      {  Scanner tok = new Scanner(in.nextLine());
         String value= tok.next(); // giocatore
         String key = tok.next();  // squadra
         d.insert(key, value);                    // prova del metodo insert()     
      }
      
      System.out.println("size " + d.size());     // prova del metodo size()
      
      Object[] keys = d.keys();                   // prova del metodo keys()
      System.out.print("keys -->");
      for (int i = 0; i < keys.length; i++)
         System.out.print(" " + keys[i]);         
      System.out.println();
      
      System.out.println("find -- " + keys[0] + " --> " + d.find(keys[0])); // prova find()
      Object x = d.remove(keys[0]);
      System.out.println("remove-- " + keys[0] + " --> " + x); // prova remove()
      d.insert((Comparable) keys[0], (Comparable) x);    //re-inserimento  
      
      for (int i = 0; i < keys.length; i++)
      {  Object[] values = d.findAll(keys[i]);    // prova del metodo findAll()
         System.out.print("findAll -- " + keys[i] + " -->");
         for (int j = 0; j < values.length; j++)
            System.out.print(" " + values[j]);
         System.out.println();   
      }
      
      for (int i = 0; i < keys.length; i++)
      { Object[] values = d.removeAll(keys[i]);   // prova del metodo removeAll
         System.out.print("removeAll -- " + keys[i] + " -->");         
         for (int j = 0; j < values.length; j++)
            System.out.print(" " + values[j]);
         System.out.println();   
      }  
   
      System.out.println("size " + d.size());      // prova del metodo size()    
   }
}
