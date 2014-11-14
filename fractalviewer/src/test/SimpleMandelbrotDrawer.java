import java.awt.geom.Point2D;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.Dimension;
import java.awt.Graphics2D;
import java.awt.Color;

public class SimpleMandelbrotDrawer extends AbstractFractalDrawer
{
	public SimpleMandelbrotDrawer(
			Point2D origin,
			double zoom,
			int maxIterations)
	{
		super(
				origin,
				-2.0, 1.0, -1.0, 1.0,
				zoom,
				maxIterations);
	}

	public void draw(Graphics2D g, Dimension dim)
	{
		for (int i = 0; i < dim.width; i++)
		{
			for (int j = 0; j < dim.height; j++)
			{
				Point2D setPoint = getScaledPoint(new Point(i, j), dim);
				g.setColor(new Color(rgbColorPoint(setPoint)));
				g.drawRect(i, j, i, j);
			}
		}
	}

	protected int getPointEscapeTime(Complex c)
	{
		int escapeTime;
		Complex z = c;
		for (escapeTime = 0; escapeTime < getMaxIterations(); escapeTime++)
		{
			z = z.squared().add(c);
			if(z.absSquared() > 4)
			{
				break;
			}
		}

		return escapeTime;
	}

	protected int rgbColorPoint(Point2D c)
	{
		int depth = getPointEscapeTime(new Complex(c.getX(), c.getY()));
		if (depth == getMaxIterations())
		{
			return 0;
		}
		
		return 0xFFFFFF;
	}
}
