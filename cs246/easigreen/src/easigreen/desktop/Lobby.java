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
 * Lobby
 *
 * @version 0.1.3
 * @author Larson Caldwell
 * @author Sam Graham
 * @author Haru McClellan
 */
public class Lobby
    extends UpgradeItem
{
    ///////////////////////////// Constructor

    /**
     * Constructor
     * @param pModel the current SimCity Model
     */
    public Lobby(SimCity pModel, Label pLabel)
    {
        super(pModel, pLabel);
    }

    ///////////////////////////// Methods
    
    /**
     * Updater
     */
    protected void update()
    {
	mChange = 0;
	mTotalChange = mSaveChange;
        mValue.setText("" + mModel.getUpgradeManager().getLobby());
    }
    
    ///////////////////////////// Getters

    /**
     * Gets the title
     * @returnt String the title
     */
    protected String getTitle()
    {
        return new String("Lobby");
    }

    /**
     * Gets the Tips
     * @returnt String array of tips
     */
    protected String[] getTips()
    {
        return new String[] {"+Funds", "-Approval"};
    }
}
