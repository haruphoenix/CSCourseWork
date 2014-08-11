package easigreen.desktop;

import easigreen.service.*;
import easigreen.system.*;

import java.util.*;

import javafx.application.*;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.*;
import javafx.geometry.*;
import javafx.scene.*;
import javafx.scene.chart.*;
import javafx.scene.control.*;
import javafx.scene.image.*;
import javafx.scene.layout.*;
import javafx.scene.text.*;
import javafx.stage.*;

/**
 * A content pane for SimCity
 *
 * @version 0.2.2
 * @author Sam Graham
 * @author Haru McClellan
 * @author Larson Caldwell
 */ 
public class EnergyPane
    extends ContentPane
{
    ////////////////////////// Variables

    /**
     * Holds the main labels for this pane
     */
    protected static String[] mMainLabelNames = new String[] {"Energy Demand"   , "Energy Supplied"};

    /**
     * Holds subsequent labels for this pane 
     */
    protected static String[] mSubLabelNames = new String[] {"Nuclear Plants"    , "Nuclear Energy",
            "Fossil Fuel Plants", "Fossil Fuel Energy",
            "Renewable Plants"  , "Renewable Energy"
                                                            };

    /**
     * Holds the name for the oil
     */
    protected static String mOilName  = new String("Oil");
    
    /**
     * Holds the name for the oil label
     */
    protected static String mOilLabel = new String("Millions of Barrels per Day");

    /**
     * Mapping from the Strings to the Labels
     */
    protected Map<String, Label> mLabels;
    
    /**
     * Mapping from the Strings to the Values
     */
    protected Map<String, Label> mValues;

    /**
     * Holds the pie chart list
     */
    protected ObservableList<PieChart.Data> mPieChartData;
    
    /**
     * Holds the PieChart
     */
    protected PieChart mPieChart;

    ///////////////////////// Constructor
    
    /**
     * Constructor
     * @param pModel the current SimCity Model
     */
    public EnergyPane(SimCity pModel)
    {
        super(pModel);
    }
    
    ///////////////////////// Methods

    /**
     * Provides set up of the pane
     */
    protected void setup()
    {
        //setGridLinesVisible(true);
        setChart();
        setLabels();

        add(getTitleLabel(), 0, 0, 5, 1);

        add(mLabels.get("Energy Demand"     ), 1,  1, 2, 1);
        add(mLabels.get("Energy Supplied"   ), 1,  2, 2, 1);
        add(mLabels.get("Nuclear Plants"    ), 2,  3, 2, 1);
        add(mLabels.get("Nuclear Energy"    ), 2,  4, 2, 1);
        add(mLabels.get("Fossil Fuel Plants"), 2,  6, 2, 1);
        add(mLabels.get("Fossil Fuel Energy"), 2,  7, 2, 1);
        add(mLabels.get("Renewable Plants"  ), 2,  9, 2, 1);
        add(mLabels.get("Renewable Energy"  ), 2, 10, 2, 1);
        add(mLabels.get(mOilName)            , 1, 12, 1, 1);
        add(mLabels.get(mOilLabel)           , 1, 13, 3, 1);

        add(mValues.get("Energy Demand"     ), 3,  1, 2, 1);
        add(mValues.get("Energy Supplied"   ), 3,  2, 2, 1);
        add(mValues.get("Nuclear Plants"    ), 4,  3, 1, 1);
        add(mValues.get("Nuclear Energy"    ), 4,  4, 1, 1);
        add(mValues.get("Fossil Fuel Plants"), 4,  6, 1, 1);
        add(mValues.get("Fossil Fuel Energy"), 4,  7, 1, 1);
        add(mValues.get("Renewable Plants"  ), 4,  9, 1, 1);
        add(mValues.get("Renewable Energy"  ), 4, 10, 1, 1);
        add(mValues.get(mOilLabel)           , 4, 13, 1, 1);

        add(mPieChart, 0, 4, 2, 6);

    }

    /**
     * Sets the labels
     */
    protected void setLabels()
    {
        mLabels = new HashMap<String, Label>();
        mValues = new HashMap<String, Label>();
        // Set main labels
        for (String name : mMainLabelNames) {
            Label newLabel1 = new Label(name + ":");
            Label newLabel2 = new Label();
            newLabel1.setFont(new Font("Arial", 20));
            newLabel2.setFont(new Font("Arial", 20));
            mLabels.put(name, newLabel1);
            mValues.put(name, newLabel2);
        }
        // Set sub labels
        for (String name : mSubLabelNames) {
            Label newLabel1 = new Label(name + ":");
            Label newLabel2 = new Label();
            mLabels.put(name, newLabel1);
            mValues.put(name, newLabel2);
        }
        // Set Oil labels
        Label oilHeading = new Label(mOilName);
        Label oilLabel   = new Label(mOilLabel + ":");
        Label oilValue   = new Label();
        oilHeading.setFont(new Font("Arial", 25));
        oilLabel  .setFont(new Font("Arial", 20));
        oilValue  .setFont(new Font("Arial", 20));
        mLabels.put(mOilName,  oilHeading);
        mLabels.put(mOilLabel, oilLabel);
        mValues.put(mOilLabel, oilValue);
        update();
    }

    /**
     * Set up a chart
     */
    protected void setChart()
    {
        mPieChartData = FXCollections.observableArrayList(
                            new PieChart.Data("Nuclear"     , 34),
                            new PieChart.Data("Fossil Fuels", 33),
                            new PieChart.Data("Renewable"   , 33));
        mPieChart        = new PieChart(mPieChartData);
        //mPieChart.setTitle("Energy Distribution");
        mPieChart.setLabelsVisible(false);
        mPieChart.setLegendSide(Side.RIGHT);
        setHalignment(mPieChart, HPos.LEFT);
    }

    /**
     * Updater
     */
    protected void update()
    {
	double energySupplied  = mModel.getEnergyManager().getPower    ();
	double nuclearEnergy   = mModel.getEnergyManager().getNuclear  ().getTotalPower();
	double fossilEnergy    = mModel.getEnergyManager().getFossil   ().getTotalPower();
	double renewableEnergy = mModel.getEnergyManager().getRenewable().getTotalPower();
	double energyDemand    = mModel.getBaseManager  ().getDemand   ();
	int    nuclearPlants   = mModel.getEnergyManager().getNuclear  ().getAmount();
	int    fossilPlants    = mModel.getEnergyManager().getFossil   ().getAmount();
	int    renewablePlants = mModel.getEnergyManager().getRenewable().getAmount();
	double oil             = mModel.getEnergyManager().getOil      ().getConsumption();

	mValues.get("Energy Demand"     ).setText(String.format(FORMAT, energyDemand   ));
        mValues.get("Energy Supplied"   ).setText(String.format(FORMAT, energySupplied ));
        mValues.get("Nuclear Plants"    ).setText("" + nuclearPlants  );
        mValues.get("Nuclear Energy"    ).setText(String.format(FORMAT, nuclearEnergy  ));
        mValues.get("Fossil Fuel Plants").setText("" + fossilPlants   );
        mValues.get("Fossil Fuel Energy").setText(String.format(FORMAT, fossilEnergy   ));
        mValues.get("Renewable Plants"  ).setText("" + renewablePlants);
        mValues.get("Renewable Energy"  ).setText(String.format(FORMAT, renewableEnergy));
        mValues.get(mOilLabel           ).setText(String.format(FORMAT, oil));

        mPieChartData.setAll(new PieChart.Data("Nuclear"     , (nuclearEnergy   / energySupplied)),
                             new PieChart.Data("Fossil Fuels", (fossilEnergy    / energySupplied)),
                             new PieChart.Data("Renewable"   , (renewableEnergy / energySupplied)));
    }
    
    //////////////////////////// Getters
    
    /**
     * Retrieves the Columns
     * @return integer array of Columns     
     */
    protected int[] getColumns()
    {
        return new int[] {12, 42, 18, 14, 14};
    }

    /**
     * Retrieves the rows
     * @return integer array of the rows
     */
    protected int[] getRows()
    {
        return new int[] {12, 10, 10, 4, 4, 3, 4, 4, 3, 4, 4, 4, 8, 8, 18};
    }

    /**
     * Gets the title of this pane
     * @return String title of the pane
     */
    protected String getTitle()
    {
        return "Energy Sources";
    }
}
