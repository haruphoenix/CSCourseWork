package easigreen.desktop;

import easigreen.service.*;
import easigreen.system.*;
import easigreen.desktop.*;

import javafx.event.*;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseEvent;

/**
 * Image Label
 *
 * @version 0.1.3
 * @author Larson Caldwell
 * @author Sam Graham
 * @author Haru McClellan
 */
public class ImageLabel extends Label
{
    ///////////////////////////// Constructor

    /**
     * Constructor for Image Button
     *
     * @param imageurl the url for an image the Label will look like
     */
    public ImageLabel(String imageurl)
    {
        setImage(imageurl);
    }

    /**
     * Default Constructor 
     */
    public ImageLabel()
    {
    }

    /**
     * Set the URL for the Image
     * @param imageurl the String identifying the string 
     */
    public void setImage(String imageurl)
    {
        Image     image = ImageGetter.getImage(imageurl);
        ImageView graphic = new ImageView(image);

        setGraphic(graphic);
    }
}
