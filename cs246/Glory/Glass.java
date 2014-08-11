import javax.swing.*;
import java.awt.event.*;
import java.awt.*;

class Glass implements Runnable
{
    private static final String CSS_FILE   = "glass.css";
    JFrame frame;

    public void run()
    {
	String stylesheet = "";
	for (int i = 0; i < 3; i++)
	{
	   try
	   {
	       stylesheet = ThreadsOfGlory.class.getResource(CSS_FILE).toExternalForm();
	       ThreadsOfGlory.getInstance().getScene().getStylesheets().add(stylesheet);
	       ThreadsOfGlory.getInstance().getScene().getWindow().setOpacity(0);
	       break;
           }
	   catch (Exception e)
	   {
	   }
	}

	while (ThreadsOfGlory.getInstance().isRunning(this.getClass().getSimpleName()))
	{
	    try
	    {
		Thread.sleep(200);
	    }
	    catch (Exception e)
	    {
	    }
	}

	for (int i = 0; i < 3; i++)
	{
	   try
	   {
	      ThreadsOfGlory.getInstance().getScene().getStylesheets().remove(stylesheet);
	      
	       ThreadsOfGlory.getInstance().getScene().getWindow().setOpacity(1);
	      break;
	   }
	   catch (Exception e)
	   {
	   }
	}
    }
}
