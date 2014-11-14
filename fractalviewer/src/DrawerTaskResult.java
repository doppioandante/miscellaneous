import java.awt.Rectangle;
import java.awt.image.BufferedImage;

public class DrawerTaskResult
{
	DrawerTaskResult(BufferedImage data, Rectangle area)
	{
		this.data = data;
		this.area = area;
	}

	public BufferedImage getData() { return data; }
	public Rectangle getArea() { return area; }

	private BufferedImage data;
	private Rectangle area;
}
