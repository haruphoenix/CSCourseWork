package easigreen.desktop;

import easigreen.service.*;

import java.util.*;

import javafx.scene.control.*;
import javafx.scene.layout.*;

import javafx.event.*;
import javafx.geometry.*;
import javafx.scene.*;
import javafx.scene.image.*;
import javafx.scene.text.*;

/**
 * A content pane for Sim City
 *
 * @version 0.2.1
 * @author Sam Graham
 * @author Haru McClellan
 * @author Larson Caldwell
 */
public class FossilEngineering
    extends UpgradeItem
{
    ///////////////////////// Constructor

    /**
     * Constructor
     * @param pModel the current SimCity Model
     */
    public FossilEngineering(SimCity pModel, Label pLabel)
    {
        super(pModel, pLabel);
    }

    //////////////////////// Methods
    
    /**
     * Updates the change
     */
    protected void update()
    {
	mChange = 0;
	mTotalChange = mSaveChange;
        mValue.setText("" + mModel.getUpgradeManager().getFossilEngineering());
    }
    
    ////////////////////// Getters

    /**
     * Gets the title
     * @return String the title
     */
    protected String getTitle()
    {
        return new String("Fossil Fuel Engineering");
    }

    /**
     * Gets the tips 
     * @return String array of tips
     */
    protected String[] getTips()
    {
        return new String[] {"+Fossil Fuel Security", "+Fossil Fuel Energy Produced"};
    }
}
