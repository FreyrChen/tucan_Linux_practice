import java.awt.Toolkit;

import javax.swing.JOptionPane;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.*;
import javax.swing.Timer;

/**
 * 
 * @author tusion
 *
 */

public class TimerTest {

	public static void main( String[] args )
	{
		ActionListener listener = new TimerPrinter();
		
		Timer timer = new Timer( 10000, listener );
		timer.start();
		
		JOptionPane.showMessageDialog(null, "Quite program?");
		System.exit(0);
		
	}
}

class TimerPrinter implements ActionListener
{
	public void actionPerformed( ActionEvent event )
	{
		Date now = new Date();
		System.out.println(" at tone ,the time is :" + now );
		Toolkit.getDefaultToolkit().beep();
	}
}