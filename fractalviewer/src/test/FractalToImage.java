import java.awt.image.BufferedImage;
import java.awt.geom.Point2D;
import java.awt.Rectangle;
import java.awt.Dimension;
import javax.imageio.ImageIO;
import java.io.File;

public class FractalToImage
{
	public static void main(String[] args) throws Exception
	{
		final int HEIGHT = 682;
		final int WIDTH = 1024;
		BufferedImage img = new BufferedImage(
			WIDTH,
			HEIGHT,
			BufferedImage.TYPE_INT_RGB);

		AbstractFractalDrawer drawer = new HistogramMTMandelbrotDrawer(
			new Point2D.Double(0.0, 0.0),
			-2.0, 1.0, -1.0, 1.0,
			1.0,
			1024,
			2);

		drawer.draw(img.createGraphics(), new Dimension(WIDTH, HEIGHT));
		ImageIO.write(img, "jpg", new File("mandelbrot.jpg"));
	}
}
