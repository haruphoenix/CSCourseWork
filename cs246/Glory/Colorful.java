import javafx.scene.paint.Color;

class Colorful extends Thread
{
    Color paint;
    int[] color;


    public Colorful()
    {
	paint = Color.WHITE;
	color = new int[] {255, 255,255};
    }

    public void run()
    {	
	while (ThreadsOfGlory.getInstance().isRunning(this.getClass().getSimpleName()))
        {
	    try
	    {
	       changeColor();
	       paint = Color.rgb(color[0], color[1], color[2]);
	       ThreadsOfGlory.getInstance().getScene().setFill(paint);
	       Thread.sleep(1000);
	    }
	    catch (Exception e)
	    {
	    }
	}
	
	paint = Color.WHITE;
	ThreadsOfGlory.getInstance().getScene().setFill(paint);
    }

    public void changeColor()
    {
	for (int i = 0; i < 3; i++)
	{
	    color[i] += (int)(Math.random() * 3) - 1;
	    color[i] %= 255;
	    color[i] =  Math.abs(color[i]);
	}
    }
}
