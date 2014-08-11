/**
 * Exploration 5, Boldness
 * Instructor: Brother Neff
 * Author: Haru McClellan
 */
import java.awt.Color;

/**
 * A simple circle class
 */
class Circle implements Oval
{
    int mRadius;
    ShapeCoordinate mCoordinate;
    Color mColor;
    
    /**
     * Constructor initializes circle with radius, location, and color
     */
    public Circle(int pRadius, int x, int y, Color pColor)
    {
	mRadius = pRadius;
	mCoordinate = new ShapeCoordinate (x, y);
	mColor = pColor;
    }

    /**
     * @return int Circle Radius
     */
    public int getRadius()
    {
	return mRadius;
    }

    /**
     * @param int radius
     * Sets the circle radius
     */
    public void setRadius(int pRadius)
    {
	mRadius = pRadius;
    }

    /**
     * @return ShapeDimension, the Radii of the circle
     */
    public ShapeDimension getRadii()
    {
	return new ShapeDimension(mRadius, mRadius);
    }

    /**
     * @return ShapeCoordinate the Location of the circle
     */
    public ShapeCoordinate getCoordinate()
    {
	return mCoordinate;
    }
    
    /**
     * @return Color, the Color of the circle
     */
    public Color getColor()
    {
	return mColor;
    }
}
