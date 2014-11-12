import java.awt.geom.Point2D;
import java.awt.Rectangle;
import java.awt.Graphics2D;
import java.util.concurrent.Future;
import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;
import java.util.LinkedList;

public class 
{
	public MandelbrotDrawer(int width, int height, Point2D center, double zoom, Fractal set, int numThreads)
	{
		this.height = height;
		this.width = width;
		this.center = center;
		this.zoom = zoom;
		this.set = set;
		this.numThreads = numThreads;
	}

	public void draw(Graphics2D g)
	{
		ExecutorService executor = Executors.newFixedThreadPool(numThreads);
		LinkedList<Future<?>> tasks = new LinkedList<Future<?>>();

		int taskWidth = width / numThreads;
		for (int i = 0; i < numThreads; i++)
		{
			Rectangle area = new Rectangle(i * taskWidth, 0, taskWidth, height);
			if (i == numThreads - 1)
			{
				area.width += width % numThreads;
			}

			tasks.add(executor.submit(new MandelbrotDrawerTask(
						g, width, height,
						area,
						center,
						zoom,
						set)));
		}
		executor.shutdown();
		
		for (Future<?> task : tasks)
		{
			try
			{
				task.get();
			}
			catch(Exception e)
			{
				System.err.println(e.toString());
				e.printStackTrace();
			}
		}
	}

	private int height;
	private int width;
	private int numThreads;
	private Point2D center;
	private double zoom;
	private MandelbrotSet set;
}
