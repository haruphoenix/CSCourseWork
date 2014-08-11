/**
 * Exploration 5, Boldness
 * Instructor: Brother Neff
 * Author: Haru McClellan
 * Collaborators: Larson Caldwell
 */
import java.awt.Color;

/**
 * Interface for an oval. Implementing classes must override
 * getRadii(), getCoordinate(), and getColor.
 */
interface Oval
{
    public ShapeDimension  getRadii();
    public ShapeCoordinate getCoordinate();
    public Color           getColor();
}
