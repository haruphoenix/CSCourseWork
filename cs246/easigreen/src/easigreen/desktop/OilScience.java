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
 *
 */
public class OilScience
    extends UpgradeItem
{

    protected String getTitle()
    {
        return new String("Oil Science");
    }

    protected String[] getTips()
    {
        return new String[] {"+Oil Security", "-Oil Consumption"};
    }

    /**
     * Constructor
     * @param SimCity pModel the current sim city Model
     */
    public OilScience(SimCity pModel, Label pLabel)
    {
        super(pModel, pLabel);
    }

    protected void update()
    {
	mChange = 0;
	mTotalChange = mSaveChange;
        mValue.setText("" + mModel.getUpgradeManager().getOilScience());
    }
}
