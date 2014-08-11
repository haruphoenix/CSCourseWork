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
public class RenewableEngineering
    extends UpgradeItem
{

    protected String getTitle()
    {
        return new String("Renewable Engineering");
    }

    protected String[] getTips()
    {
        return new String[] {"+Renewable Security", "+Renewable Energy Produced"};
    }

    /**
     * Constructor
     * @param SimCity pModel the current sim city Model
     */
    public RenewableEngineering(SimCity pModel, Label pLabel)
    {
        super(pModel, pLabel);
    }

    protected void update()
    {
	mChange = 0;
	mTotalChange = mSaveChange;
        mValue.setText("" + mModel.getUpgradeManager().getRenewableEngineering());
    }
}
