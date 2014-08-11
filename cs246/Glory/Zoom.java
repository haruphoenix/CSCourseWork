/**
 * Exploration 5, Boldness
 * Instructor: Brother Neff
 * Author: Haru McClellan
 */
import javax.swing.*;
import java.awt.event.*;
import java.awt.*;

/**
 * Runnable for Threads of Glory
 * Animates the Threads of Glory window to zoom across the screen. Creates
 * another window to control the speed.
 */
class Zoom implements Runnable
{
    /**
     * Window will excellerate to the maximum speed. The window will move
     * no faster than this. The window will not move backwards.
     */
    private static final int MAX_SPEED = 200;
    private static final int MIN_SPEED = 0;

    /**
     * Speed the window moves
     */
    private int mSpeed = 1;

    /**
     * Stops window from naturally excellerating when set to true
     */
    private boolean manualSpeed = false;

    /**
     * The X-location of the window
     */
    private int mX = (int)ThreadsOfGlory.getInstance().getScene().getWindow().getX();
  
    /**
     * A controller to allow the user to speed up or slow down the window
     */
    JFrame frame;

    /**
     * Increases the x-coordinate of the Threads of glory window as long as this
     * thread is in its running threads list.
     */
    public void run()
    {
	setup();
	int newX;
	int width;
	int size = (int)java.awt.Toolkit.getDefaultToolkit().getScreenSize().getWidth();

	while (ThreadsOfGlory.getInstance().isRunning(this.getClass().getSimpleName()))
	{
	    width = (int)ThreadsOfGlory.getInstance().getScene().getWindow().getWidth();
	    if (!manualSpeed)
	    {
		mSpeed++;
		if (mSpeed >= MAX_SPEED)
		{
		    manualSpeed = true;
		}
	    }
	    try
	    {
		mX = (int)ThreadsOfGlory.getInstance().getScene().getWindow().getX();
		newX = ((mX + (mSpeed / 2) + width) % (size + width)) - width;
		ThreadsOfGlory.getInstance().getScene().getWindow().setX(newX);
		
		Thread.sleep(25);
	    }
	    catch (Exception e)
	    {
		break;
	    }
	}
	frame.dispose();
    }
    
    /**
     * Initializes speed controller. Adds three buttons, faster, slower, and stop
     */
    public void setup()
    {
	frame = new JFrame("Zoom");
	JButton minus = new JButton("Slower");
	minus.addActionListener(new ActionListener()
	{
	    public void actionPerformed(ActionEvent event)
	    {
		if (mSpeed > MIN_SPEED)
		{
		    mSpeed -= 10;
		}
		else
		{
		    mSpeed = MIN_SPEED;
		}
		manualSpeed = true;
	    }
	});

	JButton stop = new JButton("Stop");
	stop.addActionListener(new ActionListener()
	{
	    public void actionPerformed(ActionEvent event)
	    {
		mSpeed = 0;
		manualSpeed = true;
	    }
	});

	JButton plus  = new JButton("Faster");
	plus.addActionListener(new ActionListener()
	{
	    public void actionPerformed(ActionEvent event)
	    {
		if (mSpeed < MAX_SPEED)
		{
		    mSpeed += 10;
		}
		else
		{
		    mSpeed = MAX_SPEED;
		}
		manualSpeed = true;
	    }
	});

	frame.getContentPane().add(BorderLayout.EAST, plus);
	frame.getContentPane().add(BorderLayout.CENTER, stop);
	frame.getContentPane().add(BorderLayout.WEST, minus);
	frame.setSize(220, 100);
	frame.setResizable(false);
	frame.setVisible(true);
    }    
}
