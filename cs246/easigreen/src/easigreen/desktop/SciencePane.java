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
 * Content Pane for Science Pane
 * @version 0.2.0
 * @author Haru McClellan
 */
public class SciencePane
    extends ContentPane
{
    /**
     * Holds the NuclearScience Object
     */ 
    protected NuclearScience   mNucSci;
    
    /**
     * Holds the FossilScience Object
     */ 
    protected FossilScience    mFosSci;
    
    /**
     * Holds the Renewable Science Object
     */ 
    protected RenewableScience mRenSci;
    
    /**
     * Holds the OilScience Object
     */ 
    protected OilScience       mOilSci;

    /**
     * Label for the action 
     */
    protected Label            mActionLabel;
    
    /**
     * Label displaying the action
     */
    protected Label            mActionValue;
    
    /**
     * Button for the action
     */
    protected Button           mActionButton;

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
					  mModel.getUpgradeManager().addNuclearScience  (mNucSci.getChange());
					  mModel.getResourceManager().spendActionPoints (Math.abs(mNucSci.getChange()));
					  mModel.getUpgradeManager().addFossilScience   (mFosSci.getChange());
					  mModel.getResourceManager().spendActionPoints (Math.abs(mFosSci.getChange()));
					  mModel.getUpgradeManager().addRenewableScience(mRenSci.getChange());
					  mModel.getResourceManager().spendActionPoints (Math.abs(mRenSci.getChange()));
					  mModel.getUpgradeManager().addOilScience      (mOilSci.getChange());
					  mModel.getResourceManager().spendActionPoints (Math.abs(mOilSci.getChange()));
					  mNucSci.saveChanges();
					  mFosSci.saveChanges();
					  mRenSci.saveChanges();
					  mOilSci.saveChanges();
					  update();
				      }
				  });

        setHalignment(mActionButton, HPos.LEFT);
    }

    /**
     * Set up non GUI components
     */
    protected void setComponents()
    {
        mActionValue = new Label();
        mNucSci = new NuclearScience  (mModel, mActionValue);
        mFosSci = new FossilScience   (mModel, mActionValue);
        mRenSci = new RenewableScience(mModel, mActionValue);
        mOilSci = new OilScience      (mModel, mActionValue);
        mActionLabel = new Label("Action Points:");
        setHalignment(mActionLabel, HPos.RIGHT);
        setHalignment(mActionValue, HPos.CENTER);
        update();
    }

    /**
     * Updater
     */
    protected void update()
    {
	mNucSci.update();
	mFosSci.update();
	mRenSci.update();
	mOilSci.update();
        mActionValue.setText("" + mModel.getResourceManager().getActionPoints());
    }

    /**
     * Gets a list of the columns
     * @return integer array of columns
     */
    protected int[] getColumns()
    {
        return new int[] {12, 25, 26, 25, 12};
    }

    /**
     * Gets a list of the rows
     * @return integer array of rows
     */
    protected int[] getRows()
    {
        return new int[] {12, 19, 19, 19, 19, 12};
    }

    /**
     * Gets the title of the Pane
     * @return the title as a string
     */
    protected String getTitle()
    {
        return "Science Upgrades";
    }

    /**
     * Constructor
     * @param SimCity pModel the current sim city Model
     */
    public SciencePane(SimCity pModel)
    {
        super(pModel);
    }

    /**
     * Set up the visible elements
     */
    protected void setup()
    {
        //setGridLinesVisible(true);
        setComponents();

        add(getTitleLabel(), 0, 0, 5, 1);
        add(mNucSci        , 1, 1, 3, 1);
        add(mFosSci        , 1, 2, 3, 1);
        add(mRenSci        , 1, 3, 3, 1);
        add(mOilSci        , 1, 4, 3, 1);
        add(mActionLabel   , 1, 5, 1, 1);
        add(mActionValue   , 2, 5, 1, 1);
        add(mActionButton  , 3, 5, 1, 1);
    }
}
