package easigreen.desktop;

import easigreen.service.*;
import easigreen.system.*;

import java.util.*;

import javafx.application.*;
import javafx.collections.*;
import javafx.event.*;
import javafx.geometry.*;
import javafx.scene.*;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
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
public class OilPane
    extends ContentPane
{
    ///////////////////////////// Variables

    /**
     * Content Pane for upgrades
     */
    private ContentPane mOilUpgradesPane;
    
    /**
     * Button for upgrades
     */
    private Button      mOilUpgrades;

    /**
     * Label Names
     */
    protected static String[] mLabelNames = new String[] {"Oil Consumption", "Total Oil Emissions",
            "Oil Security per Million Barrels",
            "Total Oil Security"
                                                         };

    /**
     * Map for the labels
     */
    protected Map<String, Label> mLabels;
    
    /**
     * Map for the labels for the upgrades
     */
    protected Map<String, Label> mValues;

    /**
     * X Axis
     */
    protected NumberAxis mXAxis;
    
    /**
     * Y Axis
     */
    protected NumberAxis mYAxis;
    
    /**
     * Line Chart
     */
    protected LineChart<Number, Number> mLineChart;
    
    /**
     * Series for the XY Chart
     */
    protected XYChart.Series<Number, Number> mSeries;

    /**
     * String for the Label
     */
    protected static String mUpgradeLabelName = new String("Oil Upgrades");

    ///////////////////////////// Constructor
    
    /**
     * Constructor
     * @param pModel the current SimCity Model
     */
    public OilPane(SimCity pModel)
    {
        super(pModel);
    }
    
    /////////////////////////////  Methods

    /**
     * Initializer
     */
    protected void init()
    {
        mOilUpgradesPane = new OilUpgradePane(mModel);
        EventHandler<ActionEvent> upgradeEvent = new PanelChangeEvent(mOilUpgradesPane);
        mOilUpgrades = new ImageButton("oilupgrade.png", upgradeEvent);
        setHalignment(mOilUpgrades, HPos.RIGHT);
    }
    
    /**
     * Setup
     */
    protected void setup()
    {
        setChart();
        setLabels();
        add(getTitleLabel(), 0,  0, 6, 1);
        add(mOilUpgrades   , 1, 10, 1, 1);
        add(mLineChart     , 1,  2, 4, 1);

        add(mLabels.get("Oil Consumption"                 ), 1,  1, 3, 1);
        add(mLabels.get("Total Oil Emissions"             ), 1,  4, 3, 1);
        add(mLabels.get("Oil Security per Million Barrels"), 1,  6, 3, 1);
        add(mLabels.get("Total Oil Security"              ), 1,  8, 3, 1);
        add(mLabels.get(mUpgradeLabelName                 ), 3, 10, 2, 1);

        add(mValues.get("Oil Consumption"                 ), 4,  1, 1, 1);
        add(mValues.get("Total Oil Emissions"             ), 4,  4, 1, 1);
        add(mValues.get("Oil Security per Million Barrels"), 4,  6, 1, 1);
        add(mValues.get("Total Oil Security"              ), 4,  8, 1, 1);
    }


    /**
     * Setup Chart
     */
    protected void setChart()
    {
        mXAxis = new NumberAxis();
        mXAxis.setMinorTickVisible(false);
        mXAxis.setTickLabelsVisible(false);
        mYAxis = new NumberAxis();
        mYAxis.setMinorTickVisible(false);
        mYAxis.setTickLabelsVisible(false);
        mLineChart = new LineChart<Number, Number>(mXAxis, mYAxis);
        mLineChart.setPrefSize(50, 50);
        mLineChart.setCreateSymbols(false);
        mLineChart.setHorizontalZeroLineVisible(false);
        mLineChart.setVerticalZeroLineVisible(false);
        mLineChart.setHorizontalGridLinesVisible(false);
        mLineChart.setVerticalGridLinesVisible(false);
        mLineChart.setLegendVisible(false);
    }


    /**
     * Set the Labels
     */
    protected void setLabels()
    {
        mLabels = new HashMap<String, Label>();
        mValues = new HashMap<String, Label>();
        for (String name : mLabelNames) {
            Label label1 = new Label(name);
            Label label2 = new Label();
            label1.setFont(new Font("Arial", 18));
            label2.setFont(new Font("Arial", 18));
            mLabels.put(name, label1);
            mValues.put(name, label2);
        }
        Label oilUpgrade = new Label(mUpgradeLabelName);
        oilUpgrade.setFont(new Font("Arial", 25));
        oilUpgrade.setWrapText(true);
        mLabels.put(mUpgradeLabelName, oilUpgrade);
        update();
    }

    /**
     * Updater
     */
    @SuppressWarnings("unchecked")
    protected void update()
    {
        mSeries = new XYChart.Series<Number, Number>();
        mSeries.getData().add(new XYChart.Data<Number, Number>(0, 0));
        mSeries.getData().add(new XYChart.Data<Number, Number>(1, 1));
        mSeries.getData().add(new XYChart.Data<Number, Number>(2, 2));
        mSeries.getData().add(new XYChart.Data<Number, Number>(3, 4));
        mSeries.getData().add(new XYChart.Data<Number, Number>(4, 7));
        mSeries.getData().add(new XYChart.Data<Number, Number>(5, 11));
        mLineChart.getData().setAll(mSeries);

        mValues.get("Oil Consumption"                 ).setText(String.format(FORMAT, mModel.getEnergyManager().getOil().getConsumption  ()));
        mValues.get("Total Oil Emissions"             ).setText(String.format(FORMAT, mModel.getEnergyManager().getOil().getEmissions    ()));
        mValues.get("Oil Security per Million Barrels").setText(String.format(FORMAT, mModel.getEnergyManager().getOil().getSecurity     ()));
        mValues.get("Total Oil Security"              ).setText(String.format(FORMAT, mModel.getEnergyManager().getOil().getTotalSecurity()));
    }
    
    ///////////////////////////// Getters
    
    /**
     * Gets the Columns
     * @return integer array of elements
     */
    protected int[] getColumns()
    {
        return new int[] {10, 34, 4, 26, 16, 10};
    }

    /**
     * Gets the Rows
     * @return integer array of elements
     */
    protected int[] getRows()
    {
        return new int[] {12, 5, 29, 2, 5, 2, 5, 2, 5, 2, 28, 3};
    }

    /**
     * Gets the title
     * @return the title
     */
    protected String getTitle()
    {
        return "Oil";
    }
}
