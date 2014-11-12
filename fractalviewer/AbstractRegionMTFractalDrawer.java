import java.awt.geom.Point2D;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.Dimension;
import java.awt.Graphics2D;
import java.awt.Color;

import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;
import java.util.concurrent.Callable;
import java.util.concurrent.CyclicBarrier;

import java.util.LinkedList;


public abstract class AbstractRegionMTFractalDrawer extends AbstractMTFractalDrawer
{
	public AbstractRegionMTFractalDrawer(
			Point2D origin,
			double x0, double x1, double y0, double y1,
			double zoom,
			int maxIterations,
			int numThreads)
	{
		super(
				origin,
				x0, x1, y0, y1,
				zoom,
				maxIterations,
				numThreads);
	}

	public void draw(Graphics2D g, Dimension dim)
	{
		ExecutorService executor = Executors.newFixedThreadPool(getThreads());
		LinkedList<Future<DrawerTaskResult>> tasks = new LinkedList<Future<DrawerTaskResult>>();

		int taskWidth = dim.width / getThreads();
		for (int i = 0; i < getThreads(); i++)
		{
			Rectangle area = new Rectangle(i * taskWidth, 0, taskWidth, dim.height);
			if (i == getThreads() - 1)
			{
				area.width += dim.width % getThreads();
			}

			tasks.add(executor.submit(newDrawerTask(
						g,
						dim,
						area)));
		}
		executor.shutdown();
		
		for (Future<DrawerTaskResult> task : tasks)
		{
			try
			{
				// TODO: Is this fast enough and clean?
				DrawerTaskResult result = task.get();
				Rectangle area = result.getArea();

				g.drawImage(result.getData(), area.x, area.y, area.width, area.height, null);
			}
			catch(Exception e)
			{
				System.err.println(e.toString());
				e.printStackTrace();
			}
		}
	}

	protected abstract Callable<DrawerTaskResult> newDrawerTask(
			Graphics2D g,
			Dimension dim,
			Rectangle area);
}

