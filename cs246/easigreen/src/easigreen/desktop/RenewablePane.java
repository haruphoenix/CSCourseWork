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
 * One of the content panes for Sim City
 */
public class RenewablePane
    extends ContentPane
{
    private ContentPane mRenewableUpgradesPane;
    private Button      mRenewableUpgrades;
    private Button      mApply;
    private Button      mUp;
    private Button      mDown;

    protected static String[] mLabelNames = new String[] {"Plants in Operation", "Supply Provided",
            "Cost", "Public Approval", "Emissions",
            "Security", "Profit"
                                                         };
    protected static String mUpgradeName = new String("Renewable Upgrades");

    protected Map<String, Label> mLabels;
    protected Map<String, Label> mValues;

    protected int[] getColumns()
    {
        return new int[] {10, 34, 4, 10, 16, 16, 10};
    }

    protected int[] getRows()
    {
        return new int[] {12, 7, 7, 6, 5, 5, 5, 4, 5, 5, 5, 4, 27, 3};
    }

    protected String getTitle()
    {
        return "Renewable";
    }

    protected void init()
    {
        mRenewableUpgradesPane = new RenewableUpgradePane(mModel);
        EventHandler<ActionEvent> upgradeEvent = new PanelChangeEvent(mRenewableUpgradesPane);
        mRenewableUpgrades = new ImageButton("renewableupgrade.png", upgradeEvent);
        mApply = new Button("Apply");

	EventHandler<ActionEvent> applyEvent = new EventHandler<ActionEvent>()
        {
            public void handle(ActionEvent event)
            {
                mModel.getEnergyManager().getRenewable().setAmount(Integer.parseInt(mValues.get("Plants in Operation").getText()));
            }
        };

        EventHandler<ActionEvent> upEvent = new EventHandler<ActionEvent>()
        {
            public void handle(ActionEvent event)
            {
                mValues.get("Plants in Operation").setText("" +
                                                           (Integer.parseInt(mValues.get("Plants in Operation").getText()) + 1));
            }
        };

        EventHandler<ActionEvent> downEvent = new EventHandler<ActionEvent>()
        {
            public void handle(ActionEvent event)
            {
                if (Integer.parseInt(mValues.get("Plants in Operation").getText()) != 0)
                {
                    mValues.get("Plants in Operation").setText("" +
                                                               (Integer.parseInt(mValues.get("Plants in Operation").getText()) - 1));
                }
            }
        };

        mApply.setOnAction(applyEvent);
        mUp   = new ImageButton("up.png"  , upEvent);
        mDown = new ImageButton("down.png", downEvent);
        mUp  .setPrefSize(0, 0);
        mDown.setPrefSize(0, 0);
        setHalignment(mDown           , HPos.CENTER);
        setHalignment(mUp             , HPos.CENTER);
        setHalignment(mApply          , HPos.CENTER);
        setHalignment(mRenewableUpgrades, HPos.RIGHT);
    }

    /**
     * Constructor
     * @param SimCity pModel the current sim city Model
     */
    public RenewablePane(SimCity pModel)
    {
        super(pModel);
    }

    protected void setup()
    {
        //setGridLinesVisible(true);
        setLabels();
        add(getTitleLabel()   , 0, 0 , 7, 1);
        add(mApply            , 0, 3 , 7, 1);
        add(mRenewableUpgrades, 1, 12, 1, 1);
        add(mUp               , 5,  1, 1, 1);
        add(mDown             , 5,  2, 1, 1);

        add(mLabels.get("Plants in Operation"), 1,  1, 4, 2);
        add(mLabels.get("Supply Provided"    ), 1,  4, 3, 1);
        add(mLabels.get("Cost"               ), 1,  5, 3, 1);
        add(mLabels.get("Public Approval"    ), 1,  6, 3, 1);
        add(mLabels.get("Emissions"          ), 1,  8, 3, 1);
        add(mLabels.get("Security"           ), 1,  9, 3, 1);
        add(mLabels.get("Profit"             ), 1, 10, 3, 1);
        add(mLabels.get(mUpgradeName         ), 3, 12, 3, 1);

        add(mValues.get("Plants in Operation"), 4,  1, 1, 2);
        add(mValues.get("Supply Provided"    ), 5,  4, 1, 1);
        add(mValues.get("Cost"               ), 5,  5, 1, 1);
        add(mValues.get("Public Approval"    ), 5,  6, 1, 1);
        add(mValues.get("Emissions"          ), 5,  8, 1, 1);
        add(mValues.get("Security"           ), 5,  9, 1, 1);
        add(mValues.get("Profit"             ), 5, 10, 1, 1);
    }

    protected void setLabels()
    {
        mLabels = new HashMap<String, Label>();
        mValues = new HashMap<String, Label>();

        for (String name : mLabelNames) {
            Label newLabel1 = new Label(name);
            Label newLabel2 = new Label();
            newLabel1.setFont(new Font("Arial", 20));
            newLabel2.setFont(new Font("Arial", 20));
            mLabels.put(name, newLabel1);
            mValues.put(name, newLabel2);
        }

        Label upgradeLabel = new Label(mUpgradeName);
        upgradeLabel.setFont(new Font("Arial", 25));
        upgradeLabel.setWrapText(true);
        mLabels.put(mUpgradeName, upgradeLabel);

        update();
    }

    protected void update()
    {
	mValues.get("Plants in Operation").setText("" + mModel.getEnergyManager().getRenewable().getAmount   ());
        mValues.get("Supply Provided"    ).setText(String.format(FORMAT, mModel.getEnergyManager().getRenewable().getPower    ()));
        mValues.get("Cost"               ).setText(String.format(FORMAT, mModel.getEnergyManager().getRenewable().getCostBuild()));
        mValues.get("Public Approval"    ).setText(String.format(FORMAT, mModel.getEnergyManager().getRenewable().getApproval ()));
        mValues.get("Emissions"          ).setText(String.format(FORMAT, mModel.getEnergyManager().getRenewable().getEmissions()));
        mValues.get("Security"           ).setText(String.format(FORMAT, mModel.getEnergyManager().getRenewable().getSecurity ()));
        mValues.get("Profit"             ).setText(String.format(FORMAT, mModel.getEnergyManager().getRenewable().getProfit   ()));
    }
}
