import java.awt.Dimension;
import java.awt.Point;
import java.awt.geom.Point2D;

import java.awt.Graphics;
import java.awt.Graphics2D;

import javax.swing.JPanel;
import javax.swing.SwingUtilities;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseWheelEvent;

public class FractalPanel extends JPanel
{
	public FractalPanel(Dimension dim, AbstractFractalDrawer drawer)
	{
		super(); // TODO: change?
		this.dimension = dim;
		this.drawer = drawer;
		
		setPreferredSize(dim);

		FractalPanelMouseListener listener = new FractalPanelMouseListener();
		addMouseListener(listener);
		addMouseMotionListener(listener);
		addMouseWheelListener(listener);
	}

	@Override
	protected void paintComponent(Graphics g)
	{
		super.paintComponent(g);

		getDrawer().draw((Graphics2D) g, dimension);
	}

	public void setDrawer()
	{
		this.drawer = drawer;
	}

	public AbstractFractalDrawer getDrawer()
	{
		return this.drawer;
	}

	private class FractalPanelMouseListener extends MouseAdapter
	{
		@Override
		public void mouseWheelMoved(MouseWheelEvent event)
		{
			int amount = event.getWheelRotation();
			final double factor = 0.5;
			
			Point2D zoomPoint = getDrawer().getScaledPoint(event.getPoint(), dimension);

			assert(getDrawer().getZoom() > 0.0);
			getDrawer().setZoom(getDrawer().getZoom() * Math.exp(-amount));

			Point2D origin = getDrawer().getOrigin();
			Point2D zoomPoint2 = getDrawer().getScaledPoint(event.getPoint(), dimension);

			origin.setLocation(
					origin.getX() + zoomPoint.getX() - zoomPoint2.getX(),
					origin.getY() + zoomPoint.getY() - zoomPoint2.getY());

			repaint();
		}

		@Override
		public void mouseDragged(MouseEvent event)
		{
			if(SwingUtilities.isLeftMouseButton(event))
			{
				Point2D scaledNewPos = getDrawer().getScaledPoint(event.getPoint(), dimension);
				Point2D scaledLastPos = getDrawer().getScaledPoint(lastMousePos, dimension);
				lastMousePos = event.getPoint();

				Point2D currentOrigin = getDrawer().getOrigin();
				currentOrigin.setLocation(
						currentOrigin.getX() + scaledLastPos.getX() - scaledNewPos.getX(),
						currentOrigin.getY() + scaledLastPos.getY() - scaledNewPos.getY());
				repaint();
			}
		}

		@Override
		public void mousePressed(MouseEvent event)
		{
			// TODO: check on event.getPoint() boundaries
			// TODO: better control, mouseReleased, mouse cursors change
			if(SwingUtilities.isLeftMouseButton(event))
			{
				lastMousePos = event.getPoint();
			}
		}

		private Point lastMousePos;
	}
	
	private Dimension dimension;
	private AbstractFractalDrawer drawer;
}

