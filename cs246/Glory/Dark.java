/**
 * Exploration 5 Boldness
 * Instructor: Brother Neff
 * Author: Haru McClellan
 */

/**
 * A runnable for Threads of Glory
 * Adds a css file to change the background to a wood texture
 */
class Dark implements Runnable
{
    /**
     * The css file to add
     */
    private static final String CSS_FILE   = "dark.css";

    /**
     * Overloads the run method to add a css file and remains idle until
     * ThreadsOfGlory says to no longer run.
     */
    public void run()
    {
	String stylesheet = "";
	for (int i = 0; i < 3; i++)
	{
	   try
	   {
	       stylesheet = ThreadsOfGlory.class.getResource(CSS_FILE).toExternalForm();
	       ThreadsOfGlory.getInstance().getScene().getStylesheets().add(stylesheet);
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
	      break;
	   }
	   catch (Exception e)
	   {
	   }
	}
    }
}
