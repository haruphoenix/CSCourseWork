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
 * Fossil Science
 *
 * @version 0.1.2
 * @author Larson Caldwell
 * @author Sam Graham
 * @author Haru McClellan
 */
public class FossilScience
    extends UpgradeItem
{
    //////////////////////// Methods

    /**
     * Updater
     */
    protected void update()
    {
	mChange = 0;
	mTotalChange = mSaveChange;
        mValue.setText("" + mModel.getUpgradeManager().getFossilScience());
    }

    /////////////////////// Getters

    /**
     * Gets the title
     * @return String the title
     */
    protected String getTitle()
    {
        return new String("Fossil Fuel Science");
    }

    /**
     * Gets the title
     * @return String array of tips
     */
    protected String[] getTips()
    {
        return new String[] {"+Fossil Fuel Security", "+Fossil Fuel Approval"};
    }
    
    //////////////////////// Constructor
    
    /**
     * Constructor
     * @param pModel the current SimCity Model
     */
    public FossilScience(SimCity pModel, Label pLabel)
    {
        super(pModel, pLabel);
    }
}
