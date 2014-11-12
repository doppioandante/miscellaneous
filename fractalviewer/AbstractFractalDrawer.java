import java.awt.geom.Point2D;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.Dimension;
import java.awt.Graphics2D;

public abstract class AbstractFractalDrawer
{
	public AbstractFractalDrawer(
			Point2D origin,
			double x0, double x1, double y0, double y1, // fractal plane boundaries, relative to center
			double zoom,
			int maxIterations)
	{
		setOrigin(origin);
		setBoundaries(x0, x1, y0, y1); // for internal use only
		setZoom(zoom);
		setMaxIterations(maxIterations);
	}
	
	public abstract void draw(
			Graphics2D g, // rendering context
			Dimension dimension); // width and height of the rendering area

	public final double getScaledX(int i, Dimension dim)
	{
		return origin.getX() + (x0 + ((x1 - x0)/(double)dim.width) * (double)i) / zoom;
	}

	public final double getScaledY(int j, Dimension dim)
	{
		return origin.getY() + (y0 + ((y1 - y0)/(double)dim.height) * (double)j) / zoom;
	}

	// Gets the pixel value in the fractal set scale
	public final Point2D getScaledPoint(Point point, Dimension dim)
	{
		return new Point2D.Double(
				getScaledX(point.x, dim),
				getScaledY(point.y, dim));
	}

	public void setOrigin(Point2D origin)
	{
		this.origin = origin;
	}

	public Point2D getOrigin()
	{
		return this.origin;
	}

	public void setZoom(double zoom)
	{
		// should be an exception..
		assert(zoom > 0.0);
		this.zoom = zoom;
	}

	public double getZoom()
	{
		return this.zoom;
	}

	public void setMaxIterations(int maxIterations)
	{
		// limit maxIterations?
		this.maxIterations = maxIterations;
	}

	public int getMaxIterations()
	{
		return this.maxIterations;
	}

	protected void setBoundaries(double x0, double x1, double y0, double y1)
	{
		assert(x0 < x1);
		assert(y0 < y1);

		this.x0 = x0;
		this.x1 = x1;
		this.y0 = y0;
		this.y1 = y1;
	}

	private int maxIterations;
	private double x0, x1, y0, y1;
	private double zoom;
	private Point2D origin;
}
