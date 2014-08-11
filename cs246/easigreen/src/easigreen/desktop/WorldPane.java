package easigreen.desktop;

import easigreen.service.*;
import easigreen.system.*;

import java.util.*;

import javafx.application.*;
import javafx.event.*;
import javafx.geometry.*;
import javafx.scene.*;
import javafx.scene.control.*;
import javafx.scene.image.*;
import javafx.scene.layout.*;
import javafx.scene.text.*;
import javafx.stage.*;

/**
 * Upgrade Item
 * @version 0.2.0
 * @author Haru McClellan
 */
public class WorldPane
    extends ContentPane
{
    ///////////////////////////// Variables

    /**
     * Holds the Country List
     */
    protected CountryList mCountries;
    
    /**
     * Holds the Country Pane
     */
    protected CountryPane mCountryPane;
    
    /**
     * Holds the View Button
     */
    protected Button mView;

    /////////////////////// Getters
    
    /**
     * Gets the columns
     * @return integer array of columns
     */
    protected int[] getColumns()
    {
        return new int[] {20, 60, 20};
    }

    /**
     * Gets the rows
     * @return integer array of rows
     */
    protected int[] getRows()
    {
        return new int[] {12, 4, 70, 2, 6, 6};
    }

    /**
     * Gets the title
     * @return String title
     */
    protected String getTitle()
    {
        return "Country Rankings";
    }

    ///////////////////////// Methods
    
    /**
     * Initialize the Content
     */
    protected void init()
    {
        mCountryPane = new CountryPane(mModel);
        EventHandler<ActionEvent> newTradeEvent = new EventHandler<ActionEvent>() {
            public void handle(ActionEvent event) {
                mCountryPane.setCountry("Another Country");
                GUI.getInstance().getWindow().setCenter(mCountryPane);
            }
        };
        mView = new Button("View");
        mView.setOnAction(newTradeEvent);
    }

    /**
     * Sets up initial values
     */
    protected void setup()
    {
        mCountries = new CountryList(mModel);
        add(getTitleLabel(), 0, 0, 3, 1);
        add(mCountries, 1, 2, 1, 1);
        setHalignment(mView, HPos.CENTER);
        add(mView, 1, 4);
    }

    /**
     * Updates this Pane
     */
    protected void update()
    {
        mCountries.update();
    }
    
    /////////////////////// Constructor
    
    /**
     * Constructor
     * @param pModel the current SimCity Model
     */
    public WorldPane(SimCity pModel)
    {
        super(pModel);
    }
}
