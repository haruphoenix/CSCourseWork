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
 * Trade Pane
 * @version 0.2.0
 * @author Haru McClellan
 */
public class TradePane
    extends ContentPane
{
    ////////////////////////// Variables

    /**
     * Holds the trade pane
     */
    protected ContentPane mNewTradePane;
    
    /**
     * Holds the button
     */
    protected Button      mNewTrade;
    
    /**
     * Holds the accept button
     */
    protected Button      mAccept;
    
    /**
     * Holds the trade list
     */
    protected TradeList   mTrades;

    /**
     * Holds the label names
     */
    protected static String[] mLabelNames = new String[] {"Currency", "Emission Credits",
            "Action Points", "Market Shares", "Technologies"
                                                         };

                                                         
    /**
     * Holds a map from strings to labels
     */
    protected Map<String, Label> mLabels;
    
    /**
     * Holds a map from strings to labels
     */
    protected Map<String, Label> mValues;

    

    ////////////////////////////// Methods
    
    /**
     * Initializer 
     */
    protected void init()
    {
        mNewTradePane = new NewTradePane(mModel);
        EventHandler<ActionEvent> newTradeEvent = new PanelChangeEvent(mNewTradePane);
        mNewTrade = new Button("New Trade");
        mNewTrade.setOnAction(newTradeEvent);
        mAccept = new Button("Accept");
        mAccept.setOnAction(new EventHandler<ActionEvent>() {
            public void handle(ActionEvent event) {

            }
        });
    }

    /**
     * Set up the object
     */
    protected void setup()
    {
        mTrades = new TradeList(mModel);
        initializeLabels();
        setHalignment(mNewTrade, HPos.CENTER);
        setHalignment(mAccept  , HPos.CENTER);

        add(getTitleLabel()                 , 0,  0, 6, 1);
        add(mTrades                         , 1,  1, 4, 1);
        add(mNewTrade                       , 1,  2, 4, 1);

        add(mValues.get("Selected"         ), 1,  3, 4, 1);

        add(mLabels.get("Offering"         ), 1,  4, 4, 1);
        add(mLabels.get("Currency"         ), 1,  5, 1, 1);
        add(mLabels.get("Emission Credits" ), 3,  5, 1, 1);
        add(mLabels.get("Action Points"    ), 1,  6, 1, 1);
        add(mLabels.get("Market Shares"    ), 3,  6, 1, 1);
        add(mLabels.get("Technologies"     ), 1,  7, 1, 1);
        add(mValues.get("Currency"         ), 2,  5, 1, 1);
        add(mValues.get("Emission Credits" ), 4,  5, 1, 1);
        add(mValues.get("Action Points"    ), 2,  6, 1, 1);
        add(mValues.get("Market Shares"    ), 4,  6, 1, 1);
        add(mValues.get("Technologies"     ), 2,  7, 3, 1);

        add(mLabels.get("Requesting"       ), 1,  8, 4, 1);
        add(mLabels.get("Currency2"        ), 1,  9, 1, 1);
        add(mLabels.get("Emission Credits2"), 3,  9, 1, 1);
        add(mLabels.get("Action Points2"   ), 1, 10, 1, 1);
        add(mLabels.get("Market Shares2"   ), 3, 10, 1, 1);
        add(mLabels.get("Technologies2"    ), 1, 11, 1, 1);
        add(mValues.get("Currency2"        ), 2,  9, 1, 1);
        add(mValues.get("Emission Credits2"), 4,  9, 1, 1);
        add(mValues.get("Action Points2"   ), 2, 10, 1, 1);
        add(mValues.get("Market Shares2"   ), 4, 10, 1, 1);
        add(mValues.get("Technologies2"    ), 2, 11, 3, 1);

        add(mAccept, 1, 12, 4, 1);
    }

    /**
     * Initializer of the labels
     */
    protected void initializeLabels()
    {
        mLabels = new HashMap<String, Label>();
        mValues = new HashMap<String, Label>();
        for (String name : mLabelNames) {
            mLabels.put(name, new Label(name + ":"));
            mValues.put(name, new Label());
            mLabels.put(name + "2", new Label(name + ":"));
            mValues.put(name + "2", new Label());
        }
        Label offer    = new Label("Offering"  );
        Label request  = new Label("Requesting");
        Label selected = new Label("Selected Trade");
        setHalignment(offer,    HPos.CENTER);
        setHalignment(request,  HPos.CENTER);
        setHalignment(selected, HPos.CENTER);
        offer   .setFont(new Font("Arial", 20));
        request .setFont(new Font("Arial", 20));
        selected.setFont(new Font("Arial", 30));
        mLabels.put("Offering"  , offer   );
        mLabels.put("Requesting", request );
        mValues.put("Selected"  , selected);
        update();
    }

    /**
     * Updater
     */
    protected void update()
    {
        mValues.get("Selected").setText("Selected Trade");

        mValues.get("Currency"         ).setText("0");
        mValues.get("Emission Credits" ).setText("0");
        mValues.get("Action Points"    ).setText("0");
        mValues.get("Market Shares"    ).setText("0");
        mValues.get("Technologies"     ).setText("None");

        mValues.get("Currency2"        ).setText("0");
        mValues.get("Emission Credits2").setText("0");
        mValues.get("Action Points2"   ).setText("0");
        mValues.get("Market Shares2"   ).setText("0");
        mValues.get("Technologies2"    ).setText("None");
    }
    
    ///////////////////////////////// Getters
    
    /**
     * Gets the Columns
     * @return the array list of columns
     */
    protected int[] getColumns()
    {
        return new int[] {12, 30, 8, 30, 8, 12};
    }

    /**
     * Gets the rows
     * @return the array list of rows
     */
    protected int[] getRows()
    {
        return new int[] {12, 16, 12, 9, 6, 4, 4, 4, 6, 4, 4, 4, 12, 3};
    }

    /**
     * Gets the title
     * @return the title a string
     */
    protected String getTitle()
    {
        return "Trade";
    }
    
    ////////////////////////// Constructor
    
    /**
     * Constructor
     * @param pModel the current SimCity Model
     */
    public TradePane(SimCity pModel)
    {
        super(pModel);
    }   
}
