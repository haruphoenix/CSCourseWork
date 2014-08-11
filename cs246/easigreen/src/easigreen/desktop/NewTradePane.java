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
 * New Trade Pane
 *
 * @version 0.1.3
 * @author Larson Caldwell
 * @author Sam Graham
 * @author Haru McClellan
 */
public class NewTradePane
    extends ContentPane
{
    ///////////////////////////// Variables
  
    /**
     * Button for Submit
     */
    protected Button mSubmit;

    /**
     * Pane for the Offer
     */
    protected TradeBasePane mOffer;
    
    /**
     * Pane for the Request
     */
    protected TradeBasePane mRequest;

    ///////////////////////////// Getters
    
    /**
     * Get the Columns
     * @return integer array of columns
     */
    protected int[] getColumns()
    {
        return new int[] {12, 76, 12};
    }

    /**
     * Get the rows
     * @return integer array of rows
     */
    protected int[] getRows()
    {
        return new int[] {10, 40, 40, 10};
    }

    /**
     * Get the title
     * @return title a string
     */
    protected String getTitle()
    {
        return "New Trade";
    }

    ///////////////////////////// Methods
    
    /**
     * Initializer
     */
    protected void init()
    {
        mOffer   = new TradeOfferPane(mModel);
        mRequest = new TradeRequestPane(mModel);
        mSubmit  = new Button("Submit");
        setHalignment(mSubmit, HPos.CENTER);
        mSubmit.setOnAction(new EventHandler<ActionEvent>() {
            public void handle(ActionEvent event) {
            }
        });
    }

    /**
     * Updates the pane
     */
    protected void update()
    {
	mOffer.update();
	mRequest.update();
    }
    
    /**
     * Setup
     */
    protected void setup()
    {
        add(getTitleLabel(), 1, 0);
        add(mOffer         , 1, 1);
        add(mRequest       , 1, 2);
        add(mSubmit        , 1, 3);
    }
    
    ///////////////////////////// Constructor

    /**
     * Constructor
     * @param pModel the current SimCity Model
     */
    public NewTradePane(SimCity pModel)
    {
        super(pModel);
    }    
}
