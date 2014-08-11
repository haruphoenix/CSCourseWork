package easigreen.desktop;

import easigreen.service.*;

import easigreen.system.*;

import java.util.List;
import java.util.ArrayList;

import javafx.application.*;

import javafx.event.*;

import javafx.geometry.*;

import javafx.scene.*;
import javafx.scene.control.*;
import javafx.scene.image.*;
import javafx.scene.layout.*;

import javafx.stage.*;

/**
 * Navigation Pane
 *
 * @version 0.1.3
 * @author Larson Caldwell
 * @author Sam Graham
 * @author Haru McClellan
 */
public class NavPane
    extends VBox
{
    ///////////////////////////// Variables

    /**
     * The list of buttons to add to the navigation pane
     */
    private List<Button> buttons;

    //////////////////////////// Constructor
    
    /**
     * Creates a new Navigation Pane object.
     */
    public NavPane()
    {
        super();
        buttons = new ArrayList<Button>();
    }

    ///////////////////////////// Methods
    
    /**
     * Adds a button to the Navigation Pane
     * @param url the URL for the Button, a String
     * @param event the EventHandler
     */
    public void addButton(String url, EventHandler<ActionEvent> event)
    {
        Button button = new ImageButton(url + ".png", event);
        buttons.add(button);
    }

    /**
     * Adds the buttons to the Navigation Pane
     */
    public void initialize()
    {
        for (Button button : buttons) {
            getChildren().add(button);
        }
    }

    /**
     * Enables the Navigation making it visible
     */
    public void enable()
    {

    }

}
