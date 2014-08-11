package easigreen.desktop;

import easigreen.service.*;
import easigreen.system.*;

import java.util.*;

import javafx.application.*;
import javafx.beans.value.*;
import javafx.event.*;
import javafx.geometry.*;
import javafx.scene.*;
import javafx.scene.control.*;
import javafx.scene.image.*;
import javafx.scene.layout.*;
import javafx.scene.text.*;
import javafx.stage.*;

/**
 * Content Pane for Renewable Upgrades
 * @version 0.2.0
 * @author Haru McClellan
 */
public class RenewableUpgradePane
    extends ContentPane
{
    /**
     * Gets the Columns
     * @return integer list of columns
     */
    protected int[] getColumns()
    {
        return new int[] {10, 10, 10, 10, 20, 10, 10, 10, 10};
    }

    /**
     * Gets the Rows
     * @return integer list of rows
     */
    protected int[] getRows()
    {
        return new int[] {10, 16, 16, 8, 8, 20, 15, 10, 2};
    }

    /**
     * Get the title of the Pane
     * @return string of the title
     */
    protected String getTitle()
    {
        return "Renewable Upgrades";
    }

    /**
     * Holds the renewable sciences
     */
    protected RenewableScience     mRenewSci;
    
    /**
     * Holds the renewable engineering
     */
    protected RenewableEngineering mRenewEng;
    
    /**
     * Holds the action label
     */
    protected Label                mActionLabel;
    
    /**
     * Holds the action value
     */
    protected Label                mActionValue;
    
    /**
     * Holds the button for the action
     */
    protected Button               mActionButton;
    
    /**
     * Holds the label for the tech area
     */
    protected Label                mTechLabel;
    
    /**
     * Holds the list of renewable technologies
     */
    protected RenewableTechList    mTechList;
    
    /**
     * Holds the text area for the technologies
     */
    protected TechEntry            mTechEntry;
    
    /**
     * Holds the label for the code area
     */
    protected Label                mCodeLabel;
    
    /**
     * Holds the text area for entering the codes
     */
    protected TextField            mCodeValue;
    
    /**
     * Holds the button for entering the codes
     */
    protected Button               mCodeButton;

    /**
     * Constructor
     * @param SimCity pModel the current sim city Model
     */
    public RenewableUpgradePane(SimCity pModel)
    {
        super(pModel);
    }

    /**
     * Sets up the various GUI related underpinnings
     */
    protected void setup()
    {
        //setGridLinesVisible(true);

        initializeComponents();

        add(getTitleLabel(), 0, 0, 9, 1);
        add(mRenewSci      , 1, 1, 7, 1);
        add(mRenewEng      , 1, 2, 7, 1);
        add(mActionLabel   , 1, 3, 3, 1);
        add(mActionValue   , 4, 3, 1, 1);
        add(mActionButton  , 5, 3, 2, 1);
        add(mTechLabel     , 1, 4, 4, 1);
        add(mTechList      , 1, 5, 7, 1);
        add(mTechEntry     , 2, 6, 5, 1);
        add(mCodeLabel     , 0, 7, 3, 1);
        add(mCodeValue     , 3, 7, 2, 1);
        add(mCodeButton    , 5, 7, 2, 1);
    }

    /**
     * Initializer for the visible objects
     */
    protected void init()
    {
        mActionButton = new Button("Apply");
        mCodeButton   = new Button("Apply");

	mActionButton.setOnAction(new EventHandler<ActionEvent>()
                                  {
                                      public void handle(ActionEvent event)
                                      {
                                          mModel.getUpgradeManager().addRenewableScience    (mRenewSci.getChange());
                                          mModel.getResourceManager().spendActionPoints     (Math.abs(mRenewSci.getChange()));
                                          mModel.getUpgradeManager().addRenewableEngineering(mRenewEng.getChange());
                                          mModel.getResourceManager().spendActionPoints     (Math.abs(mRenewEng.getChange()));
					  mRenewSci.saveChanges();
					  mRenewEng.saveChanges();
                                          update();
                                      }
                                  });

        mCodeButton.setOnAction(new EventHandler<ActionEvent>()
				{
				    public void handle(ActionEvent event)
				    {
					mModel.getUpgradeManager().getTechnologyManager().addTechnology(mCodeValue.getText());
                                        mCodeValue.setText("");
                                        update();
				    }
				});

        mTechList = new RenewableTechList(mModel);
        mTechList.getSelectionModel().selectedItemProperty()
            .addListener(new ChangeListener<String>()
                         {
                             public void changed(ObservableValue<?
                                                 extends String> observable,
                                                 String oldValue, String newValue)
                             {
                                 mTechEntry.update(newValue);
                             }
                         });


        setHalignment(mCodeButton, HPos.CENTER);
    }

    /**
     * Initializer for the various non-visible components
     */
    protected void initializeComponents()
    {
        mActionValue = new Label               ();
        mRenewSci    = new RenewableScience    (mModel, mActionValue);
        mRenewEng    = new RenewableEngineering(mModel, mActionValue);
        mActionLabel = new Label               ("Action Points:");
        mTechLabel   = new Label               ("Renewable Technologies");
        mTechEntry   = new TechEntry           (mModel);
        mCodeLabel   = new Label               ("Tech Code:");
        mCodeValue   = new TextField           ();

        setHalignment(mActionLabel, HPos.RIGHT);
        setHalignment(mActionValue, HPos.CENTER);
        setHalignment(mCodeLabel  , HPos.RIGHT);
        setHalignment(mTechEntry  , HPos.CENTER);
        setHalignment(mTechList   , HPos.CENTER);
        setValignment(mTechEntry  , VPos.CENTER);
        setValignment(mTechList   , VPos.CENTER);

        mTechEntry.setEditable(false);
        mTechEntry.setWrapText(true);
        mTechEntry.setMinSize(0, 0);

        mTechList.setMinSize(0, 0);
        mTechList.setMaxSize(350, 100);
        mTechEntry.setMaxSize(250, 75);

        mTechLabel  .setFont(new Font("Arial", 20));
        mActionLabel.setFont(new Font("Arial", 16));
        mActionValue.setFont(new Font("Arial", 16));

        mCodeValue.setMinSize(0, 0);

        update();
    }

    /**
     * Updater
     */
    protected void update()
    {
	mTechList.update();
	mRenewSci.update();
	mRenewEng.update();
        mActionValue.setText("" + mModel.getResourceManager().getActionPoints());
    }
}
