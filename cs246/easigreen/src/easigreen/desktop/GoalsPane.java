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
 * One of the content panes for SimCity
 *
 * @version 0.1.3
 * @author Larson Caldwell
 * @author Sam Graham
 * @author Haru McClellan
 */
public class GoalsPane
    extends ContentPane
{
    /////////////////////////// Variables

    /**
     * Holds the Label Names for the Goals Pane
     */
    protected static String[] mLabelNames = new String[] {"Power Demand"    , "Power Supply"   ,
            "Budget"          , "Total Spent"    ,
            "Minimum Approval", "Public Approval",
            "Target Emissions", "Total Emissions",
            "Target Security" , "Total Security" ,
            "Target Profit"   , "Total Profit"
                                                         };

    /**
     * Map from the array of strings to the labels
     */
    protected Map<String, Label> mLabels;
    
    /**
     * Map from the array of strings to the labels
     */
    protected Map<String, Label> mValues;
    
    /**
     * Map from the array of strings the the images
     */
    protected Map<String, ImageLabel> mImages;

    ///////////////////////////// Constructor
    
    /**
     * Constructor
     * @param pModel the current SimCity Model
     */
    public GoalsPane(SimCity pModel)
    {
        super(pModel);
    }

    ///////////////////////////// Methods
    
    /**
     * Setup
     */
    protected void setup()
    {
        setLabels();
        add(getTitleLabel(), 0, 0, 6, 1);

        add(mLabels.get("Short Term"      ), 1,  1, 2, 1);
        add(mLabels.get("Power Demand"    ), 2,  2, 1, 1);
        add(mLabels.get("Power Supply"    ), 2,  3, 1, 1);
        add(mLabels.get("Budget"          ), 2,  5, 1, 1);
        add(mLabels.get("Total Spent"     ), 2,  6, 1, 1);
        add(mLabels.get("Minimum Approval"), 2,  8, 1, 1);
        add(mLabels.get("Public Approval" ), 2,  9, 1, 1);
        add(mValues.get("Power Demand"    ), 3,  2, 1, 1);
        add(mValues.get("Power Supply"    ), 3,  3, 1, 1);
        add(mValues.get("Budget"          ), 3,  5, 1, 1);
        add(mValues.get("Total Spent"     ), 3,  6, 1, 1);
        add(mValues.get("Minimum Approval"), 3,  8, 1, 1);
        add(mValues.get("Public Approval" ), 3,  9, 1, 1);

        add(mLabels.get("Long Term"       ), 1, 11, 2, 1);
        add(mLabels.get("Target Emissions"), 2, 12, 1, 1);
        add(mLabels.get("Total Emissions" ), 2, 13, 1, 1);
        add(mLabels.get("Target Security" ), 2, 15, 1, 1);
        add(mLabels.get("Total Security"  ), 2, 16, 1, 1);
        add(mLabels.get("Target Profit"   ), 2, 18, 1, 1);
        add(mLabels.get("Total Profit"    ), 2, 19, 1, 1);
        add(mValues.get("Target Emissions"), 3, 12, 1, 1);
        add(mValues.get("Total Emissions" ), 3, 13, 1, 1);
        add(mValues.get("Target Security" ), 3, 15, 1, 1);
        add(mValues.get("Total Security"  ), 3, 16, 1, 1);
        add(mValues.get("Target Profit"   ), 3, 18, 1, 1);
        add(mValues.get("Total Profit"    ), 3, 19, 1, 1);

        add(mImages.get("Power Demand"    ), 4,  2, 1, 2);
        add(mImages.get("Budget"          ), 4,  5, 1, 2);
        add(mImages.get("Minimum Approval"), 4,  8, 1, 2);
        add(mImages.get("Target Emissions"), 4, 12, 1, 2);
        add(mImages.get("Target Security" ), 4, 15, 1, 2);
        add(mImages.get("Target Profit"   ), 4, 18, 1, 2);
    }

    /**
     * Set the Labels
     */
    protected void setLabels()
    {
        mLabels = new HashMap<String, Label>();
        mValues = new HashMap<String, Label>();
        mImages = new HashMap<String, ImageLabel>();
        int i = 0;
        for (String name : mLabelNames) {
            Label newLabel = new Label(name + ":");
            Label newValue = new Label();
            newLabel.setMinSize(0, 0);
            newValue.setMinSize(0, 0);
            setHalignment(newValue, HPos.CENTER);
            newLabel.setFont(new Font("Arial", 14));
            newValue.setFont(new Font("Arial", 14));
            mLabels.put(name, newLabel);
            mValues.put(name, newValue);
            if (i++ % 2 == 0) {
                mImages.put(name, new ImageLabel());
            }
        }

        Label shortTerm = new Label("Short Term");
        Label longTerm  = new Label("Long Term" );

        shortTerm.setFont(new Font("Arial", 18));
        longTerm .setFont(new Font("Arial", 18));

        mLabels.put("Short Term", shortTerm);
        mLabels.put("Long Term" , longTerm );

        update();
    }

    /**
     * Updater
     */
    protected void update()
    {
        mModel.getGoalManager().update();

	double powerDemand = mModel.getResourceManager().getDemand();
	double powerSupply = mModel.getEnergyManager  ().getPower ();
	double budget      = mModel.getResourceManager().getBudget();
	double totalSpent  = budget - mModel.getResourceManager().getFunds();
	double minApproval = mModel.getGoalManager    ().getTargetApproval();
	double actApproval = (mModel.getEnergyManager().getApproval() * 100);
	double targetEmit  = mModel.getGoalManager    ().getTargetEmissions();
	double actualEmit  = mModel.getEnergyManager  ().getEmissions();
	double targetSec   = mModel.getGoalManager    ().getTargetSecurity();
	double actualSec   = mModel.getEnergyManager  ().getSecurity();
	double targetProf  = mModel.getGoalManager    ().getTargetProfit();
	double actualProf  = mModel.getEnergyManager  ().getProfit();

        mValues.get("Power Demand"    ).setText(String.format(FORMAT, powerDemand));
        mValues.get("Power Supply"    ).setText(String.format(FORMAT, powerSupply));
        mValues.get("Budget"          ).setText(String.format(FORMAT, budget     ));
        mValues.get("Total Spent"     ).setText(String.format(FORMAT, totalSpent ));
        mValues.get("Minimum Approval").setText(String.format(FORMAT, minApproval));
        mValues.get("Public Approval" ).setText(String.format(FORMAT, actApproval));

        mValues.get("Target Emissions").setText(String.format(FORMAT, targetEmit ));
        mValues.get("Total Emissions" ).setText(String.format(FORMAT, actualEmit ));
        mValues.get("Target Security" ).setText(String.format(FORMAT, targetSec  ));
        mValues.get("Total Security"  ).setText(String.format(FORMAT, actualSec  ));
        mValues.get("Target Profit"   ).setText(String.format(FORMAT, targetProf ));
        mValues.get("Total Profit"    ).setText(String.format(FORMAT, actualProf ));

	String good = "good.png";
	String bad  = "bad.png";
	String imageName = "";
	imageName = (powerSupply >= powerDemand) ? good : bad;
        mImages.get("Power Demand"    ).setImage(imageName);
	imageName = (budget >= totalSpent) ? good : bad;
        mImages.get("Budget"          ).setImage(imageName);
	imageName = (actApproval >= minApproval) ? good : bad;
        mImages.get("Minimum Approval").setImage(imageName);
        imageName = (targetEmit >= actualEmit) ? good : bad;
	mImages.get("Target Emissions").setImage(imageName);
        imageName = (actualSec >= targetSec) ? good : bad;
	mImages.get("Target Security" ).setImage(imageName);
        imageName = (actualProf >= targetProf) ? good : bad;
	mImages.get("Target Profit"   ).setImage(imageName);
    }
    
    ///////////////////////////// Getters
    
    /**
     * Get the Columns
     * @return the integer array of columns
     */
    protected int[] getColumns()
    {
        return new int[] {12, 8, 33, 25, 10, 12};
    }

    /**
     * Get the Rows
     * @return the integer array of Rows
     */
    protected int[] getRows()
    {
        return new int[] {10, 6, 5, 5, 1, 5, 5, 1, 5, 5, 4, 6, 5, 5, 1, 5, 5, 1, 5, 5, 10};
    }

    /**
     * Get the Title
     * @return the String
     */
    protected String getTitle()
    {
        return "Goals";
    }
}
