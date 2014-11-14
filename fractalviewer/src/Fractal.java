import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import javax.swing.JPanel;
import javax.swing.JFrame;
import java.awt.geom.Point2D;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.text.NumberFormat;
//TODO: change import granularity

public class Fractal extends JFrame implements ActionListener//, ChangeListener
{
	public static void main(String[] args) throws Exception
	{
		try
		{
			UIManager.setLookAndFeel(
					UIManager.getSystemLookAndFeelClassName());
		}
		catch(UnsupportedLookAndFeelException|ClassNotFoundException e)
		{
			// just ignore this exception, the default look and feel will be ok
		}

		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				Fractal frame = new Fractal();
				frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

				frame.pack();
				frame.setVisible(true);
			}
		});
	}

	public Fractal()
	{
		super();

		this.drawer = new HistogramMTMandelbrotDrawer(
				new Point2D.Double(0.0, 0.0),
				-2.0, 1.0, -1.0, 1.0,
				1.0,
				512,
				Runtime.getRuntime().availableProcessors());

		createUI();
		this.panel = new FractalPanel(
				new Dimension(1024, 1024/3*2),
				this.drawer);

		add(this.panel, BorderLayout.CENTER);
	}

	private void createUI()
	{
		// toolbar = save + reset + threads
		JToolBar toolbar = new JToolBar(JToolBar.HORIZONTAL);
		toolbar.setFloatable(false);

		JButton saveButton = new JButton("Save");
		saveButton.setActionCommand("save");
		JButton resetButton = new JButton("Reset");
        resetButton.setActionCommand("reset");

		saveButton.addActionListener(this);
        resetButton.addActionListener(this);

		JLabel threadLabel = new JLabel("#Threads:");
		int processors = Runtime.getRuntime().availableProcessors();
		JSpinner threadSpinner = new JSpinner(
				new SpinnerNumberModel(processors, 1, processors, 1));
		JSpinner.DefaultEditor ed = (JSpinner.DefaultEditor)threadSpinner.getEditor();
		ed.getTextField().setColumns(5);
		//TODO: add change listener

		toolbar.add(saveButton);
		toolbar.add(resetButton);
		toolbar.add(Box.createGlue());
		toolbar.add(threadLabel);
		toolbar.add(threadSpinner);

		// info = x, y, zoom
		JToolBar info = new JToolBar(JToolBar.HORIZONTAL);
		info.setFloatable(false);
		//info.setLayout(new FlowLayout(FlowLayout.LEADING));

		JLabel xLabel = new JLabel("x:");
		JLabel yLabel = new JLabel("y:");
		JLabel zoomLabel = new JLabel("zoom:");
		JTextField xField = new JFormattedTextField(NumberFormat.getInstance());
		xField.setColumns(18);
		JTextField yField = new JFormattedTextField(NumberFormat.getInstance());
		yField.setColumns(18);
		JTextField zoomField = new JFormattedTextField(NumberFormat.getInstance());
		zoomField.setColumns(18);
		
		info.add(xLabel);
		info.add(xField);
		info.addSeparator();
		info.add(yLabel);
		info.add(yField);
		info.add(Box.createGlue());
		info.add(zoomLabel);
		info.add(zoomField);

		// top = toolbar / info
		JPanel top = new JPanel(new BorderLayout());
		top.add(toolbar, BorderLayout.PAGE_START);
		top.add(info, BorderLayout.PAGE_END);

		
		setLayout(new BorderLayout());
		add(top, BorderLayout.PAGE_START);

		setTitle("Fractal Viewer");
	}

	public void actionPerformed(ActionEvent event)
	{
		if(event.getActionCommand().equals("reset"))
		{
			this.drawer.setOrigin(new Point2D.Double(0.0, 0.0));
			this.drawer.setZoom(1.0);
			this.panel.repaint();
		}
		else if(event.getActionCommand().equals("save"))
		{
			String filename = "mandelbrot.jpg";
			try
			{
				FractalSaver.save(filename, this.drawer, this.panel.getSize());
				JOptionPane.showMessageDialog(this, "Fractal written to " + filename);
			}
			catch(Exception e)
			{
				// TODO: show an error dialog, more granularity on the exception
			}
		}
	}

	private AbstractMTFractalDrawer drawer;
	private FractalPanel panel;
}
