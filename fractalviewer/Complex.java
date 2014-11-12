public class Complex
{
	Complex(double x, double y)
	{
		this.x = x;
		this.y = y;
	}

	Complex squared()
	{
		return new Complex(x*x - y*y, 2*x*y);
	}
	double absSquared()
	{
		return x*x + y*y;
	}

	Complex add(Complex c)
	{
		x += c.x;
		y += c.y;

		return this;
	}

	public double x;
	public double y;
}
