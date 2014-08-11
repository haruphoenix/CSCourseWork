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
 * Upgrades Pane
 * @version 0.2.0
 * @author Haru McClellan
 */
public class UpgradesPane
    extends ContentPane
{
    ///////////////////////////// Variables

    /**
     * Holds the label names
     */
    protected static String[] mLabelNames = new String[] {"Nuclear Science", "Fossil Fuel Science",
            "Renewable Science", "Oil Science",
            "Nuclear Engineering", "Fossil Fuel Engineering",
            "Renewable Engineering", "Price Change",
            "Lobby", "Oil Drilling"
                                                         };

    /**
     * Holds the technology title
     */
    protected static String mTechTitle = new String("Implemented Technologies");

    /**
     * Holds the map of strings to labels
     */
    protected Map<String, Label> mLabels;
    
    /**
     * Holds the map of string to labels 
     */
    protected Map<String, Label> mValues;

    /**
     * Holds the implemented technology list
     */
    protected ImplementedTechList mTechList;

    ///////////////////////////// Methods
    
    /**
     * Setup of basic elements
     */
    protected void setup()
    {
        mTechList = new ImplementedTechList(mModel);
        setLabels();
        add(getTitleLabel(), 0, 0, 4, 1);

        int i = 1;
        for (String name : mLabelNames) {
            add(mLabels.get(name), 1, i  , 1, 1);
            add(mValues.get(name), 2, i++, 1, 1);
            if ((i == 5) || (i == 9)) {
                i++;
            }
        }
        add(mLabels.get(mTechTitle), 1, i++, 1, 1);
        add(mTechList              , 1, i  , 2, 1);
    }

    /**
     * Sets the Labels
     */
    protected void setLabels()
    {
        mLabels = new HashMap<String, Label>();
        mValues = new HashMap<String, Label>();

        for (String name : mLabelNames) {
            Label newLabel = new Label(name);
            Label newValue = new Label();
            newLabel.setFont(new Font("Arial", 16));
            newValue.setFont(new Font("Arial", 16));
            mLabels.put(name, newLabel);
            mValues.put(name, newValue);
        }

        Label techLabel = new Label(mTechTitle);
        techLabel.setFont(new Font("Arial", 16));
        mLabels.put(mTechTitle, techLabel);

        update();
    }

    /**
     * Update the object
     */
    protected void update()
    {
        mValues.get("Nuclear Science"        ).setText("" + mModel.getUpgradeManager().getNuclearScience());
        mValues.get("Fossil Fuel Science"    ).setText("" + mModel.getUpgradeManager().getFossilScience());
        mValues.get("Renewable Science"      ).setText("" + mModel.getUpgradeManager().getRenewableScience());
        mValues.get("Oil Science"            ).setText("" + mModel.getUpgradeManager().getOilScience());
        mValues.get("Nuclear Engineering"    ).setText("" + mModel.getUpgradeManager().getNuclearEngineering());
        mValues.get("Fossil Fuel Engineering").setText("" + mModel.getUpgradeManager().getFossilEngineering());
        mValues.get("Renewable Engineering"  ).setText("" + mModel.getUpgradeManager().getRenewableEngineering());
        mValues.get("Price Change"           ).setText("" + mModel.getUpgradeManager().getPriceChange());
        mValues.get("Lobby"                  ).setText("" + mModel.getUpgradeManager().getLobby());
        mValues.get("Oil Drilling"           ).setText("" + mModel.getUpgradeManager().getOilDrilling());
        mTechList.update();
    }
    
    ////////////////////////// Getters
    
    /**
     * Gets the Columns
     * @return integer array of columns
     */
    protected int[] getColumns()
    {
        return new int[] {12, 66, 10, 12};
    }

    /**
     * Holds the rows
     */
    protected int[] getRows()
    {
        return new int[] {12, 6, 6, 6, 6, 4, 6, 6, 6, 4, 6, 6, 6, 6, 12, 2};
    }

    /**
     * Holds the map names
     */
    protected String getTitle()
    {
        return "Upgrades";
    }
    
    ////////////////////////// Constructor
    
    /**
     * Constructor
     * @param pModel the current SimCity Model
     */
    public UpgradesPane(SimCity pModel)
    {
        super(pModel);
    }
}
