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
 * Oil Drilling
 *
 * @version 0.1.3
 * @author Larson Caldwell
 * @author Sam Graham
 * @author Haru McClellan
 */
public class OilDrilling
    extends UpgradeItem
{
    ///////////////////////////// Updater
    
    /**
     * Updater
     */
    protected void update()
    {
	mChange = 0;
	mTotalChange = mSaveChange;
        mValue.setText("" + mModel.getUpgradeManager().getOilDrilling());
    }

    ///////////////////////////// Getters

    /**
     * Gets the title
     * @return the title a string
     */
    protected String getTitle()
    {
        return new String("Oil Drilling");
    }
    
    /**
     * Gets the tips
     * @return tips array of Strings
     */
    protected String[] getTips()
    {
        return new String[] {"+Short Term Security", "-Long Term Security", "+Emissions"};
    }

    ///////////////////////////// Constructor
    
    /**
     * Constructor
     * @param pModel the current SimCity Model
     */
    public OilDrilling(SimCity pModel, Label pLabel)
    {
        super(pModel, pLabel);
    }
}
