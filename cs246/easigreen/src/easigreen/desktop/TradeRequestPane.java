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
 * Trade Request Pane
 * @version 0.2.0
 * @author Haru McClellan
 */
public class TradeRequestPane
    extends TradeBasePane
{
    //////////////////////////////// Methods

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
        mTechs           = new AllTechList(mModel);
        mInsert          = new TextArea();
        mInsert.setMinSize(0, 0);
        mInsert.setWrapText(true);
        mInsert.setEditable(false);
        mAdd             = new Button("Add");
    }
    
    ////////////////////////// Getters

    /**
     * Gets the title
     * @return the title a string
     */
    protected String getTitle()
    {
        return "Requesting";
    }

    ///////////////////////// Constructor
    
    /**
     * Constructor
     * @param pModel the current SimCity Model
     */
    public TradeRequestPane(SimCity pModel)
    {
        super(pModel);
    }
}
