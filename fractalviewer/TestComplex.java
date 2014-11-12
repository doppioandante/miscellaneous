public class TestComplex
{
	public static void main(String[] args)
	{
		Complex c = new Complex(3.0, 2.0);
		Complex d = c.squared();
		d.add(new Complex(5.0, 3.0));
		System.out.println(d.x + " " + d.y);
	}
}
