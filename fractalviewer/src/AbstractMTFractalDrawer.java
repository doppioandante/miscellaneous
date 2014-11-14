import java.awt.geom.Point2D;
import java.awt.Dimension;

public abstract class AbstractMTFractalDrawer extends AbstractFractalDrawer
{
	public AbstractMTFractalDrawer(
			Point2D origin,
			double x0, double x1, double y0, double y1, // fractal plane boundaries, relative to center
			double zoom,
			int maxIterations,
			int numThreads)
	{
		super(
			origin,
			x0, x1, y0, y1,
			zoom,
			maxIterations);

		setThreads(numThreads);
	}

	public void setThreads(int numThreads)
	{
		this.numThreads = numThreads;
	}

	public int getThreads()
	{
		return this.numThreads;
	}

	private int numThreads;
}
