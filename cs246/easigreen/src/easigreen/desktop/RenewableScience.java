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
 * Renewable Science Item
 * @version 0.2.0
 * @author Haru McClellan
 */
public class RenewableScience
    extends UpgradeItem
{
    /**
     * Gets the title
     * @return String the title
     */
    protected String getTitle()
    {
        return new String("Renewable Science");
    }

    /**
     * Retrieves a list of tips
     * @return array of Strings
     */
    protected String[] getTips()
    {
        return new String[] {"+Renewable Security", "+Renewable Approval"};
    }

    /**
     * Constructor
     * @param SimCity pModel the current sim city Model
     */
    public RenewableScience(SimCity pModel, Label pLabel)
    {
        super(pModel, pLabel);
    }

    /**
     * Updater
     */
    protected void update()
    {
	mChange = 0;
	mTotalChange = mSaveChange;
        mValue.setText("" + mModel.getUpgradeManager().getRenewableScience());
    }
}
