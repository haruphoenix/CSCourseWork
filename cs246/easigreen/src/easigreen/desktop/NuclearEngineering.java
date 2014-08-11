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
 * Nuclear Engineering provides specific behaviour for 
 * @version 0.2.0
 * @author Haru McClellan
 */
public class NuclearEngineering
    extends UpgradeItem
{
    //////////////////////////// Constructor
    
    /**
     * Constructor
     * @param pModel the current SimCity Model
     */
    public NuclearEngineering(SimCity pModel, Label pLabel)
    {
        super(pModel, pLabel);
    }
    
    /////////////////////////////// Getters
    
    /**
     * Gets the title for this Content Component
     * @return String the title
     */
    protected String getTitle()
    {
        return new String("Nuclear Engineering");
    }

    /**
     * Gets the Tips
     * @return an array of Strings
     */
    protected String[] getTips()
    {
        return new String[] {"+Nuclear Security", "+Nuclear Energy Produced"};
    }
    
    //////////////////////////// Methods
    
    /**
     * Updater
     */
    protected void update()
    {
	mChange = 0;
	mTotalChange = mSaveChange;
        mValue.setText("" + mModel.getUpgradeManager().getNuclearEngineering());
    }
    
}
