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
 * A content pane for SimCity
 *
 * @version 0.2.1
 * @author Sam Graham
 * @author Haru McClellan
 * @author Larson Caldwell
 */
public class EngineeringPane
    extends ContentPane
{
    //////////////////////////// Variables

    /**
     * Holds Nuclear Engineering object
     */
    protected NuclearEngineering   mNucEng;
    
    /**
     * Holds Fossil Engineering object
     */
    protected FossilEngineering    mFosEng;
    
    /**
     * Holds Renewable Engineering object
     */
    protected RenewableEngineering mRenEng;

    /**
     * Holds Label for the action label
     */
    protected Label   mActionLabel;
    
    /**
     * Holds Label for the action value
     */
    protected Label   mActionValue;
    
    /**
     * Holds Button for the action
     */
    protected Button  mActionButton;

    /////////////////////////// Methods
    
    /**
     * Initializer
     */
    protected void init()
    {
        mActionButton = new Button("Apply");

	    mActionButton.setOnAction(new EventHandler<ActionEvent>()
                                  {
                                      public void handle(ActionEvent event)
                                      {
                                          mModel.getUpgradeManager ().addNuclearEngineering  (mNucEng.getChange());
                                          mModel.getResourceManager().spendActionPoints      (Math.abs(mNucEng.getChange()));
                                          mModel.getUpgradeManager ().addFossilEngineering   (mFosEng.getChange());
                                          mModel.getResourceManager().spendActionPoints      (Math.abs(mFosEng.getChange()));
                                          mModel.getUpgradeManager ().addRenewableEngineering(mRenEng.getChange());
                                          mModel.getResourceManager().spendActionPoints      (Math.abs(mRenEng.getChange()));
					  mNucEng.saveChanges();
					  mFosEng.saveChanges();
					  mRenEng.saveChanges();
                                          update();
                                      }
                                  });

        setHalignment(mActionButton, HPos.LEFT);
    }

    /**
     * Sets the components, initializer of buttons, labels, etcetera 
     */
    protected void setComponents()
    {
        mActionValue = new Label();
        mNucEng = new NuclearEngineering  (mModel, mActionValue);
        mFosEng = new FossilEngineering   (mModel, mActionValue);
        mRenEng = new RenewableEngineering(mModel, mActionValue);
        mActionLabel = new Label("Action Points:");
        setHalignment(mActionLabel, HPos.RIGHT);
        setHalignment(mActionValue, HPos.CENTER);
        update();
    }

    /**
     * Set up of buttons, labels, etc. 
     */
    protected void setup()
    {
        setComponents();

        add(getTitleLabel(), 0, 0, 5, 1);
        add(mNucEng        , 1, 1, 3, 1);
        add(mFosEng        , 1, 2, 3, 1);
        add(mRenEng        , 1, 3, 3, 1);
        add(mActionLabel   , 1, 4, 1, 1);
        add(mActionValue   , 2, 4, 1, 1);
        add(mActionButton  , 3, 4, 1, 1);
    }
    
    /**
     * Updater
     */
    protected void update()
    {
	    mNucEng.update();
	    mFosEng.update();
	    mRenEng.update();
        mActionValue.setText("" + mModel.getResourceManager().getActionPoints());
    }

    ////////////////////// Getters
    
    /**
     * Gets the columns
     * @return integer array of columns
     */
    protected int[] getColumns()
    {
        return new int[] {12, 25, 26, 25, 12};
    }

    /**
     * Gets the rows
     * @return integer array of the rows
     */
    protected int[] getRows()
    {
        return new int[] {12, 25, 25, 25, 13};
    }

    /**
     * Retrieves the title for this Pane
     * @return String title of the pane
     */
    protected String getTitle()
    {
        return "Engineering Upgrades";
    }

    /////////////////////////// Constructor
    
    /**
     * Constructor
     * @param pModel the current SimCity Model
     */
    public EngineeringPane(SimCity pModel)
    {
        super(pModel);
    }
}
