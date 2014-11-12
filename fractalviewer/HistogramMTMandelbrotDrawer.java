import java.awt.geom.Point2D;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.Dimension;
import java.awt.Graphics2D;
import java.awt.Color;

import java.awt.image.BufferedImage;

import java.util.concurrent.Callable;
import java.util.concurrent.CyclicBarrier;

import java.util.Arrays;

public class HistogramMTMandelbrotDrawer extends AbstractRegionMTFractalDrawer
{
	public HistogramMTMandelbrotDrawer(
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

		this.histogram = new int[maxIterations + 1];
		//this.total = new Integer(0);
		//this.barrier = new CyclicBarrier(numThreads, new ComputeTotal());
	}

	protected Callable<DrawerTaskResult> newDrawerTask(
			Graphics2D g,
			Dimension dim,
			Rectangle area)
	{
		return new Task(g, dim, area);
	}

	@Override
	public void draw(Graphics2D g, Dimension dim)
	{
		this.total = new Integer(0);
		this.barrier = new CyclicBarrier(getThreads(), new ComputeTotal());
		Arrays.fill(this.histogram, 0);

		super.draw(g, dim);
	}

	
	private class Task implements Callable<DrawerTaskResult>
	{
		private Graphics2D g;
		private Dimension dim;
		private Rectangle area;

		Task(
			Graphics2D g,
			Dimension dim,
			Rectangle area)
		{
			this.g = g;
			this.dim = dim;
			this.area = area;
		}

		public DrawerTaskResult call()
		{
			int[] iterations = new int[area.width * area.height];

			for (int i = 0; i < area.width; i++)
			{
				double x = getScaledX(area.x + i, dim);

				for (int j = 0; j < area.height; j++)
				{
					double y = getScaledY(j, dim);

					int depth = getPointEscapeTime(new Complex(x, y));
					iterations[i * area.height + j] = depth;
					synchronized(histogram)
					{
						histogram[depth]++;
					}
				}
			}

			try
			{
				barrier.await();
			}
			catch(Exception e)
			{
				e.printStackTrace();
				//TODO: do something here
				// maybe the overall computation should be discarded(rethrow the exception)
			}

			BufferedImage buffer = new BufferedImage(
					area.width,
					area.height,
					BufferedImage.TYPE_INT_RGB);

			for (int i = 0; i < area.width; i++)
			{
				for (int j = 0; j < area.height; j++)
				{

					buffer.setRGB(i, j, getRgbColoring(iterations[i * area.height + j]));
				}
			}

			return new DrawerTaskResult(buffer, area);
		}

		protected int getRgbColoring(int iterations)
		{
			int rgb;
			int accum = 0;
			for (int i = 0; i <= iterations; i++)
			{
				accum += histogram[i];
			}
			if(false)//iterations == getMaxIterations())
			{
				rgb = 0;
			}
			else
			{
				rgb = (int)Math.floor((double)0xFFD700*(1 - (double)iterations / (double)total));
			}
			return rgb;
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
	}

	private class ComputeTotal implements Runnable
	{
		public void run()
		{
			for(int i = 0; i < histogram.length; i++)
			{
				total += histogram[i];
			}
		}
	}
	

	private Integer total;
	private int[] histogram;
	private CyclicBarrier barrier;
}
