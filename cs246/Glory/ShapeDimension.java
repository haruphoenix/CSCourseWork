/**
 * Exploration 5, Boldness
 * Instructor: Brother Neff
 * Author: Haru McClellan
 */

/**
 * A simple class for holding the height and width of an object
 */
class ShapeDimension
{
    private int mWidth;
    private int mHeight;

    /**
     * Constructor sets the width and height
     * @param int pWidth
     * @param int pHeight
     */
    public ShapeDimension(int pWidth, int pHeight)
    {
	mWidth = pWidth;
	mHeight = pHeight;
    }

    /**
     * @param int pWidth
     * Sets the width of the object
     */
    public void setWidth(int pWidth)
    {
	mWidth = pWidth;
    }
    
    /**
     * @param int pHeight
     * Sets the height of the object
     */
    public void setHeight(int pHeight)
    {
	mHeight = pHeight;
    }

    /**
     * @return int mWidth
     */
    public int getWidth()
    {
	return mWidth;
    }

    /**
     * @return int mHeight
     */
    public int getHeight()
    {
	return mHeight;
    }
}
