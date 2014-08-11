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
 * Trade Offer Pane
 * @version 0.2.0
 * @author Haru McClellan
 */
public class TradeOfferPane
    extends TradeBasePane
{
    ////////////////////////////// Methods
    
    /**
     * Updater
     */
    public void update()
    {
	mTechs.update();
    }
    
    /**
     * Initializer
     */
    protected void init()
    {
        mTechs           = new AvailableTechList(mModel);
        mInsert          = new TextArea();
        mInsert.setMinSize(0, 0);
        mInsert.setWrapText(true);
        mInsert.setEditable(false);
        mAdd             = new Button("Add");
    }
    
    ////////////////////////////// Getters
    
    /**
     * Get title
     * @return the title
     */
    protected String getTitle()
    {
        return "Offering";
    }
    
    ////////////////////////////// Constructor

    /**
     * Constructor
     * @param pModel the current SimCity Model
     */
    public TradeOfferPane(SimCity pModel)
    {
        super(pModel);
    }
}
