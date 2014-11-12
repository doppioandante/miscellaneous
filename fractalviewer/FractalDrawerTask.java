import java.awt.geom.Point2D;
import java.awt.Rectangle;
import java.awt.Graphics;
import java.awt.image.BufferedImage;

public class MandelbrotDrawerTask implements Runnable 
{
	public MandelbrotDrawerTask(Graphics g, int width, int height, Rectangle drawRect, Point2D center, double zoom, MandelbrotSet set)
		{
		this.drawingBounds = drawRect;
		this.g = g;
		this.setImage = new BufferedImage(
			drawingBounds.width,
			drawingBounds.height,
			BufferedImage.TYPE_INT_RGB);

		this.center = center;
		this.zoom = zoom;
		this.set = set;
		this.width = width;
		this.height = height;
	}

	public void run()
	{
		double xCenter = center.getX();
		double yCenter = center.getY();
		double imgWidth = setImage.getWidth();
		double imgHeight = setImage.getHeight();

		for (int i = 0; i < imgWidth; i++)
		{
			double x = ((-2.0 + xCenter*zoom) + 3.0/width*(double)(i + drawingBounds.x))/zoom;
			for (int j = 0; j < imgHeight; j++)
			{
				double y = ((1.0 + yCenter*zoom) - 2.0/height*(double)(j + drawingBounds.y))/zoom;
				setImage.setRGB(i, j, set.rgbDepth(new Complex(x, y)));
			}
		}

		g.drawImage(
			setImage,
			drawingBounds.x,
			drawingBounds.y,
			null // no ImageObserver specified
		);
	}
	
	private BufferedImage setImage;
	private Rectangle drawingBounds;
	private Graphics g;
	private Point2D center;
	private double zoom;
	private MandelbrotSet set;
	private int width;
	private int height;
}
