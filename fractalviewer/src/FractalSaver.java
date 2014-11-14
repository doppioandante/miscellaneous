import javax.imageio.ImageIO;

import java.awt.Dimension;
import java.awt.image.BufferedImage;

import java.io.File;

public class FractalSaver
{
	public static void save(String filename, AbstractFractalDrawer drawer, Dimension dim) throws Exception
	{
		BufferedImage img = new BufferedImage(
				dim.width,
				dim.height,
				BufferedImage.TYPE_INT_RGB);

		drawer.draw(img.createGraphics(), dim);

		// TODO: rename file if existing(and maybe move this code in another class)
		ImageIO.write(img, "jpg", new File(filename));
	}
}
