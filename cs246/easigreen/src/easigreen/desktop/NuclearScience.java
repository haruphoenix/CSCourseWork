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
 * Nuclear Science
 * @version 0.2.0
 * @author Haru McClellan
 */
public class NuclearScience
    extends UpgradeItem
{
    //////////////////////////////// Methods

    /**
     * Updater
     */
    protected void update()
    {
	mChange = 0;
	mTotalChange = mSaveChange;
        mValue.setText("" + mModel.getUpgradeManager().getNuclearScience());
    }

    //////////////////////////////// Getters
    
    /**
     * Get Title
     * @return String the Title
     */
    protected String getTitle()
    {
        return new String("Nuclear Science");
    }

    /**
     * Get Tips
     * @return String array
     */
    protected String[] getTips()
    {
        return new String[] {"+Nuclear Security", "+Nuclear Approval"};
    }

    //////////////////////////// Constructor
    
    /**
     * Constructor
     * @param pModel the current SimCity Model
     */
    public NuclearScience(SimCity pModel, Label pLabel)
    {
        super(pModel, pLabel);
    }

}
