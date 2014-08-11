/**
 * Exploration 5, Boldness
 * Instructor: Brother Neff
 * Author: Haru McClellan
 */
import java.awt.*;
import javax.swing.*;
import com.sun.awt.AWTUtilities;
import java.util.List;
import java.util.ArrayList;

/**
 * Runnable for Threads of Glory. Creates a bunch of bubbles that float up the
 * screen on a transparent background
 */
class Bubbles implements Runnable
{
    /**
     * Constants relating to the size, color, sway and number of bubbles.
     */
    private static final int MIN_BUBBLE_SIZE = 10;
    private static final int MAX_BUBBLE_SIZE = 100;
    private static final int NUM_BUBBLES = 20;
    private static final int SWAY_TIME = 26;
    private static final Color[] COLORS = {Color.red, Color.orange, Color.yellow, 
					   Color.green, Color.blue, Color.magenta};

    /**
     * Height and width of the screen
     */
    int screenHeight;
    int screenWidth;
    
    /**
     * The frame and panel to paint the bubbles in
     */
    JFrame mainFrame;
    BubblesPanel bubblesPanel;

    /**
     * The information for the bubbles is stored in an oval object. 
     * This is the list of Ovals to paint
     */
    ArrayList<Oval> bubbles;

    /**
     * A timer for the sway of the bubbles
     */
    int swayTimer;

    /**
     * Constructor, initializes screen dimensions and oval list
     */
    public Bubbles()
    {
	screenHeight = (int)Toolkit.getDefaultToolkit().getScreenSize().getHeight();
	screenWidth  = (int)Toolkit.getDefaultToolkit().getScreenSize().getWidth();
	bubbles = new ArrayList<Oval>();
	swayTimer = 0;
    }

    /**
     * Animates Bubbles on the screen as long as Threads of Glory tells it to run
     */
    public void run()
    {
	start();
	try
	{
	    while (ThreadsOfGlory.getInstance().isRunning(this.getClass().getSimpleName()))
	    {
		bubblesPanel.repaint();
		updateBubbles();
		swayTimer = (swayTimer + 1) % SWAY_TIME;
		Thread.sleep(25);
	    }
	}
	catch (Exception e)
	{
	}
	mainFrame.dispose();
	bubbles.clear();
    }

    /**
     * Initializes the frame and bubbles
     */
    public void start()
    {
	mainFrame = new JFrame();
	mainFrame.setSize(screenWidth, screenHeight);
	mainFrame.setUndecorated(true);
	mainFrame.getContentPane().setLayout(new FlowLayout());
	bubblesPanel = new BubblesPanel();
	mainFrame.setGlassPane(bubblesPanel);
	mainFrame.getGlassPane().setVisible(true);
	AWTUtilities.setWindowOpaque(mainFrame, false);
	mainFrame.setVisible(true);
	addBubbles();
    }

    /**
     * Creates bubbles(Ovals) of random size, location, and color, and adds them to
     * the bubbles aray
     */
    public void addBubbles()
    {
	for (int i = 0; i < NUM_BUBBLES; i++)
	{
	    int   x     = (int)(Math.random() * screenWidth);
	    int   y     = (int)(Math.random() * screenHeight) + screenHeight;
	    int   size  = (int)(Math.random() * (MAX_BUBBLE_SIZE - MIN_BUBBLE_SIZE)) + MIN_BUBBLE_SIZE;
	    Color color = COLORS[(int)(Math.random() * 6)];
	    bubbles.add(new Circle(size, x, y, color));
	}
    }

    /**
     * Updates the location of the bubbles, calculates sway and speed based on bubble size
     */
    public void updateBubbles()
    {
	for (Oval bubble : bubbles)
	{
	    int bubbleSize = bubble.getRadii().getWidth();
	    int x          = bubble.getCoordinate().getX();
	    int y          = bubble.getCoordinate().getY();
	    int speed      = (MAX_BUBBLE_SIZE - (bubbleSize  - 10)) / 10;
	    int swayAmount = (speed / 2) + 1;
	    y = y - speed;
	    if (y < 0)
	    {
		y = screenHeight;
	    }
	    if (((swayTimer + speed) % SWAY_TIME) < SWAY_TIME / 2)
	    {
		swayAmount = -swayAmount;
	    }
	    x = x + swayAmount;
	    bubble.getCoordinate().setX(x);
	    bubble.getCoordinate().setY(y);
	}
    }

    /**
     * A panel for painting bubbles
     */
    class BubblesPanel extends JPanel
    {
	Graphics2D paintbrush;
	GradientPaint gradient;

	/**
	 * Constructor, sets the panel transparent
	 */
	BubblesPanel()
	{
	    setOpaque(false);
	}
	
	/**
	 * Receives a graphics object, assigns it to
	 * paintbrush and paints all the bubbles
	 */
	public void paintComponent(Graphics g)
	{
	    paintbrush = (Graphics2D) g;
	    paintBubbles();
	}

	/**
	 * Paints each bubble one at a time
	 */
	public void paintBubbles()
	{
	    for (Oval bubble : bubbles)
	    {
		paintBubble(bubble);
	    }
	}

	/**
	 * Paints a single bubble
	 * @param Oval bubble has the information needed to paint the bubble
	 */
	public void paintBubble(Oval bubble)
	{
	    gradient = new GradientPaint(bubble.getCoordinate().getX(), bubble.getCoordinate().getY(), bubble.getColor(), 
					 bubble.getCoordinate().getX() + bubble.getRadii().getWidth(),
					 bubble.getCoordinate().getY() + bubble.getRadii().getHeight(), Color.white);
	    paintbrush.setPaint(gradient);
	    paintbrush.fillOval(bubble.getCoordinate().getX(), bubble.getCoordinate().getY(), bubble.getRadii().getWidth(), bubble.getRadii().getHeight());
	}
    }
}
