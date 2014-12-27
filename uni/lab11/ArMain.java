import java.io.FileReader;
import java.io.PrintWriter;
import java.util.Scanner;
import java.io.IOException;

public class ArMain
{
    public static void main(String[] args) throws IOException
    {
	if (args.length < 3)
	{
            System.out.println("uso: $ java ArMain input output1 output2");
            System.exit(1);
	}

	Scanner in = new Scanner(new FileReader(args[0]));

	Stack pila = new ArStack();
	Queue coda = new ArQueue();

	while (in.hasNextLine())
	{
	    Scanner lineTokenizer = new Scanner(in.nextLine());

	    while (lineTokenizer.hasNext())
	    {
		String token = lineTokenizer.next();

		pila.push(token);
		coda.enqueue(token);
	    }
	    lineTokenizer.close();
	}

	in.close();


	PrintWriter writer = new PrintWriter(args[1]);
	while (!pila.isEmpty())
	{
	    writer.println((String) pila.pop());
	}

	writer.close();
	writer = new PrintWriter(args[2]);
	while (!coda.isEmpty())
	{
	    writer.println((String) coda.dequeue());
	}
	writer.close();
    }
}
