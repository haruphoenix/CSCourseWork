/**
 * Exploration 5 Boldness
 * Instructor: Brother Neff
 * Author: Haru McClellan
 */
import javax.swing.*;
import java.awt.event.*;
import java.awt.*;

/**
 * Runnable Thread for Threads of Glory
 * Makes the Threads of Glory window randomly bounce around the screen
 */
class Bouncer extends Thread
{
    /**
     * Initial coordinates and dimensions of window and screen
     */
    private int mScreenHeight = (int)java.awt.Toolkit.getDefaultToolkit().getScreenSize().getHeight();
    private int mScreenWidth  = (int)java.awt.Toolkit.getDefaultToolkit().getScreenSize().getWidth();
    private int initialX      = (int)ThreadsOfGlory.getInstance().getScene().getWindow().getX();
    private int initialY      = (int)ThreadsOfGlory.getInstance().getScene().getWindow().getY();
    private int initialHeight = (int)ThreadsOfGlory.getInstance().getScene().getWindow().getHeight();
    private int initialWidth  = (int)ThreadsOfGlory.getInstance().getScene().getWindow().getWidth();
    
    /**
     * Variable coordinates and dimensions
     */
    private int mX;
    private int mY;
    private int mHeight;
    private int mWidth;
    
    /**
     * Increment speed every 10 iterations
     * counter keeps track of the iterations
     */
    private final int COUNT   = 10;
    private       int counter = 0;

    /**
     * Sleep for 10 miliseconds between each iteration
     */ 
    private final int SLEEP = 10;

    /**
     * The max distance per iteration a bounce can move
     */
    private final int MAX_DISTANCE = 10;

    /**
     * Speed and direction of bounce
     */
    private boolean falling = true;
    private int     speed   = 0;
    private boolean right    = true;
    private int     distance = 2;

    /**
     * The amount of spring the window will absorb before jumping again
     */
    private int spring  = 200;    

    /**
     * Contructor initializes coordinates and dimensions
     */
    public Bouncer()
    {
	mX = initialX;
	mY = initialY;
	mHeight = initialHeight;
	mWidth = initialWidth;
    }

    /**
     * While Threads of glory is running this thread, bounce the window around
     */
    public void run()
    {
	
	while (ThreadsOfGlory.getInstance().isRunning(this.getClass().getSimpleName()))
	{
	    try
	    {
		modifyY();
		modifyX();
		modifySize();
		
		ThreadsOfGlory.getInstance().getScene().getWindow().setY(mY);
		ThreadsOfGlory.getInstance().getScene().getWindow().setX(mX);
		ThreadsOfGlory.getInstance().getScene().getWindow().setWidth(mWidth);
		ThreadsOfGlory.getInstance().getScene().getWindow().setHeight(mHeight);
		Thread.sleep(SLEEP);
	    }
	    catch (Exception e)
	    {
	    }
	}
    }

    /**
     * Adjust the Y Coordinate of the Window
     */
    private void modifyY()
    {
	if (falling)
	{
	    mY += faster(true);
	    if (mY >= (mScreenHeight - initialHeight + spring))
	    {
		falling = false;
		// Bounce in a random direction
		int direction = (int)(Math.random() * 2);
		distance = (int)(Math.random() * MAX_DISTANCE);
		if (direction == 0)
		{
		    right = false;
		}
		else
		{
		    right = true;
		}
	    }
	}
	else
	{
	    mY -= faster(false);
	    if (speed <= 0)
	    {
		speed = 0;
		falling = true;
	    }
	}
    }

    /**
     * @param boolean isFaster - True to increase speed
     * false decreases speed
     * @return int speed
     */
    private int faster(boolean isFaster)
    {
	counter = (counter + 1) % COUNT;
	 if (counter == 0)
	 {
	     if (isFaster)
	     {
		 return ++speed;
	     }
	     else
	     {
		 return speed--;
	     }
	 }
	return speed;
    }

    /**
     * Adjust the x coordinate of the window.
     */
    private void modifyX()
    {
	if (right)
	{
	    mX = (mX + distance);
	    if (mX > mScreenWidth)
	    {
		mX = 0 - initialWidth;
	    }
	}
	else
	{
	    mX = mX - distance;
	    if (mX < (0 - initialWidth))
	    {
		mX = mScreenWidth;
	    }
	}

	if (mY > (mScreenHeight - initialHeight))
	{
	    if (falling)
	    {
		mX -= (speed / 2);
	    }
	    else
	    {
		mX += (speed / 2);
	    }
	}
    }

    /**
     * Adjust the height and width of the window during compression phase
     * the "spring"
     */
    private void modifySize()
    {
	if (mY >= (mScreenHeight - initialHeight))
	{
	    if (falling)
	    {
		mWidth  += speed;
		mHeight -= speed;
	    }
	    else
	    {
		mWidth  -= speed;
		if (mWidth < initialWidth)
		{
		    mWidth = initialWidth;
		}
		mHeight += speed;
		if (mHeight > initialHeight)
		{
		    mHeight = initialHeight;
		}
	    }
	}
    }

}
