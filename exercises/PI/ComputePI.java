public class ComputePI
{
   public static void main(String[] args)
   {
      if(args.length < 1)
      {
         System.err.println("Usage: CalcoloPI <radius>; (the bigger the radius, the better the precision");
         System.exit(1);
      }      

      long precision = Long.parseLong(args[0]);
      double pi = MTAreaPI.getPI(precision);
      System.out.println(MTAreaPI.getPI(precision));
      System.out.println("Relative error: " + (1.0 - pi/Math.PI));
   }
}
