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
 * Pane for Trade base
 * @version 0.2.0
 * @author Haru McClellan
 */
public class TradeBasePane
    extends ContentPane
{
    ////////////////////////// Variables
    
    /**
     * Holds the list of available techs
     */
    protected AppDataList mTechs;
    
    /**
     * Holds the text area
     */
    protected TextArea    mInsert;
    
    /**
     * Holds the button for adding a technology
     */
    protected Button      mAdd;

    /**
     * Holds a list of the various label names
     */
    protected static String[] mLabelNames = new String[] {"Currency", "Action Points",
            "Emission Credits", "Market Shares"
                                                         };

    /**
     * Maps the string to the labels
     */                                                     
    protected Map<String, Label>    mLabels;

    /**
     * Maps the string to the text field
     */
    protected Map<String, TextField> mValues;

    /////////////////////////////// Methods
    
    /**
     * Initialization
     */
    protected void init()
    {
        mTechs           = new AppDataList(mModel);
        mInsert          = new TextArea();
        mInsert.setMinSize(0, 0);
        mInsert.setWrapText(true);
        mInsert.setEditable(false);
        mAdd             = new Button("Add");
    }
    
    /**
     * Set up of the various GUI elements
     */
    protected void setup()
    {
        Label title = getTitleLabel();
        title.setFont(new Font("Arial", 25));
        setLabels();
        setHalignment(mAdd, HPos.CENTER);
        add(title,   0, 0, 6, 1);
        add(mTechs,  4, 1, 1, 4);
        add(mAdd,    4, 6, 1, 1);
        add(mInsert, 1, 8, 2, 1);
        add(mLabels.get("Currency"        ), 1, 1, 1, 1);
        add(mLabels.get("Action Points"   ), 1, 2, 1, 1);
        add(mLabels.get("Emission Credits"), 1, 3, 1, 1);
        add(mLabels.get("Market Shares"   ), 1, 4, 1, 1);
        add(mLabels.get("Technologies"    ), 1, 6, 2, 1);

        add(mValues.get("Currency"        ), 2, 1, 1, 1);
        add(mValues.get("Action Points"   ), 2, 2, 1, 1);
        add(mValues.get("Emission Credits"), 2, 3, 1, 1);
        add(mValues.get("Market Shares"   ), 2, 4, 1, 1);
    }

    /**
     * Set up the labels
     */
    protected void setLabels()
    {
        mLabels = new HashMap<String, Label>();
        mValues = new HashMap<String, TextField>();
        for (String name : mLabelNames) {
            mLabels.put(name, new Label(name + ":"));
            TextField field = new TextField();
            field.setMinSize(0, 0);
            mValues.put(name, field);
        }
        Label techs = new Label("Technologies");
        techs.setFont(new Font("Arial", 20));
        setHalignment(techs, HPos.CENTER);
        mLabels.put("Technologies", techs);
        update();
    }
    
    //////////////////////// Getters
    
    /**
     * Get Columns
     * @return integer array of columns
     */
    protected int[] getColumns()
    {
        return new int[] {4, 38, 14, 4, 36, 4};
    }

    /**
     * Get Rows
     * @return integer array of rows
     */
    protected int[] getRows()
    {
        return new int[] {15, 11, 11, 11, 11, 2, 15, 2, 20, 2};
    }

    /**
     * Get the title of the pane
     * @return String the columns
     */
    protected String getTitle()
    {
        return "Unknown";
    }
    
    ///////////////////////// Constructor

    /**
     * Constructor
     * @param pModel the current SimCity Model
     */
    public TradeBasePane(SimCity pModel)
    {
        super(pModel);
    }
}
