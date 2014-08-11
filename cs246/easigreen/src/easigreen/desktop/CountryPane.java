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
 * A content pane for Sim city
 *
 * @version 0.2.1
 * @author Sam Graham
 * @author Haru McClellan
 * @author Larson Caldwell
 */ 
public class CountryPane
    extends ContentPane
{
    /**
     * Holds the country name
     */
    protected String mCountryName;

    /**
     * Holds a mapping to the labels from certain strings
     */
    Map<String, Label> mValues;

    /**
     * Retrieves a list of categories that can be displayed in this pane
     * @return an array of Strings
     */
    protected String[] getCategories()
    {
        return new String[] {"Nuclear Plants", "Fossil Fuel Plants", "Renewable Plants",
                             "",
                             "Energy Supplied", "Available Funds", "Public Approval", "Oil Consumption",
                             "",
                             "Total Profit", "Total Security", "Total Emissions"
                            };
    }

    /**
     * Holds an array of Strings containing the various categories
     */
    protected String[] mCategories;

    /**
     * Holds an array of labels 
     */
    protected Label[] mLabels;

    /**
     * Holds the title label
     */
    Label mTitle;

    /**
     * Holds the list of implemented technologies for the pane
     */
    protected ImplementedTechList mTechs;

    /**
     * Retrieves a list of Columns
     * @return an integer array of columns
     */
    protected int[] getColumns()
    {
        return new int[] {12, 6, 50, 20, 12};
    }

    /**
     * Get Rows
     * @return an integer array of Rows
     */
    protected int[] getRows()
    {
        return new int[] {16, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 28, 4};
    }

    /**
     * Gets the title of this pane
     * @return String title of the pane
     */
    protected String getTitle()
    {
        return "mCountryName";
    }

    /**
     * Constructor
     * @param pModel the current Simcity Model
     */
    public CountryPane(SimCity pModel)
    {
        super(pModel);
    }

    /**
     * Provides set up of the pane
     */
    protected void setup()
    {
        mCountryName = "Your Country";
        mTitle = getTitleLabel();
        initializeLabels();

        add(mTitle, 1, 0, 3, 1);
        int i;
        for (i = 0; i < mCategories.length; i++) {
            if (!mCategories[i].equals("")) {
                add(mLabels[i], 2, i + 1);
                add(mValues.get(mCategories[i]), 3, i + 1);
            }
        }
        add(new Label("Technologies Implemented:"), 2, ++i + 1);
        add(mTechs, 2, ++i + 1, 2, 1);
    }

    /**
     * Sets the country
     * @param pCountry a String
     */
    public void setCountry(String pCountry)
    {
        mCountryName = pCountry;
        update();
    }

    /**
     * Initialize the Labels
     */
    protected void initializeLabels()
    {
        mCategories = getCategories();
        mLabels = new Label[mCategories.length];
        mValues = new HashMap<String, Label>();
        for (int i = 0; i < mCategories.length; i++) {
            if (!mCategories[i].equals("")) {
                mLabels[i] = new Label(mCategories[i] + ":");
		Label newValue = new Label();
		setHalignment(newValue, HPos.RIGHT);
                mValues.put(mCategories[i], newValue);
            }
        }

        mTechs = new ImplementedTechList(mModel);
        update();
    }

    /**
     * Updater
     */
    protected void update()
    {
        mTitle.setText(mCountryName);
	
	mValues.get("Nuclear Plants"    ).setText("" + mModel.getEnergyManager().getNuclear  ().getAmount());
	mValues.get("Fossil Fuel Plants").setText("" + mModel.getEnergyManager().getFossil   ().getAmount());
	mValues.get("Renewable Plants"  ).setText("" + mModel.getEnergyManager().getRenewable().getAmount());
        mValues.get("Energy Supplied"   ).setText(String.format(FORMAT, mModel.getEnergyManager  ().getPower    ()                 ));
	mValues.get("Available Funds"   ).setText(String.format(FORMAT, mModel.getResourceManager().getFunds    ()                 ));
        mValues.get("Public Approval"   ).setText(String.format(FORMAT, mModel.getEnergyManager  ().getApproval ()                 ));
        mValues.get("Oil Consumption"   ).setText(String.format(FORMAT, mModel.getEnergyManager  ().getOil      ().getConsumption()));
        mValues.get("Total Profit"      ).setText(String.format(FORMAT, mModel.getEnergyManager  ().getProfit   ()                 ));
        mValues.get("Total Security"    ).setText(String.format(FORMAT, mModel.getEnergyManager  ().getSecurity ()                 ));
        mValues.get("Total Emissions"   ).setText(String.format(FORMAT, mModel.getEnergyManager  ().getEmissions()                 ));

        mTechs.update();
    }

}
