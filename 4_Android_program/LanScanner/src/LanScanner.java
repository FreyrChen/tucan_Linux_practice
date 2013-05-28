
import java.awt.*;
import javax.swing.*;
/**
 * 
 * @author tusion
 *
 */
public class LanScanner {

	public static void main( String[] args)
	{
		EventQueue.invokeLater( new Runnable()
		{
			public void run()
			{
				SimpleFrame frame = new SimpleFrame();
				frame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE);
				frame.setVisible(true);
				//frame.setLocation(100, 100);
			}
		});
	}
	
}

class SimpleFrame extends JFrame
{

	public SimpleFrame()
	{
		Toolkit kit = Toolkit.getDefaultToolkit();
		Dimension screenSize = kit.getScreenSize();
		int screenHeight = screenSize.height;
		int screenWidth = screenSize.width;
		
		setSize( screenWidth / 2, screenHeight / 2 );
		setLocationByPlatform( true);
		
		setTitle("tusionframe");
		
		NotHelloPanel panel =  new NotHelloPanel();
		add( panel );
	}
	
	//public static final int screenHeight = 300;
	//public static final int screenWidth = 200;
}

class NotHelloPanel extends JPanel
{
	public void paintComponet( Graphics g )
	{
		g.drawString("not a hello", 50, 50);
	}
}
