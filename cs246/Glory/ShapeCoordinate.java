/**
 * Exploration 5, Boldness
 * Instructor: Brother Neff
 * Author: Haru McClellan
 */

/**
 * A simple class for holding the location of an object
 */
class ShapeCoordinate
{
    private int mX;
    private int mY;

    /**
     * Constructor sets the location
     * @param int pX
     * @param int pY
     */
    public ShapeCoordinate(int pX, int pY)
    {
	mX = pX;
	mY = pY;
    }

    /**
     * Sets the x coordinate
     * @param int pX
     */
    public void setX(int pX)
    {
	mX = pX;
    }
    
    /**
     * Sets the y coordinate
     * @param int pY
     */
    public void setY(int pY)
    {
	mY = pY;
    }

    /**
     * @return int mX
     */
    public int getX()
    {
	return mX;
    }

    /**
     * @return int mY
     */
    public int getY()
    {
	return mY;
    }
}
