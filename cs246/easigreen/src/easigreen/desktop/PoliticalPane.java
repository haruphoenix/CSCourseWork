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
public class PoliticalPane
    extends ContentPane
{
    protected Map<String, Label> mValues;

    protected static String[] mMainNames = new String[] {"Funds", "Market Shares", "Emission Credits", "Action Points"};
    protected static String[] mTipNames  = new String[] {"Remaining budget for this round",
            "Modify your country's energy demand",
            "Modify your country's emissions score",
            "Use these to apply upgrades"
                                                        };

    protected int[] getColumns()
    {
        return new int[] {12, 60, 16, 12};
    }

    protected int[] getRows()
    {
        return new int[] {12, 4, 7, 14, 7, 14, 7, 14, 7, 14};
    }

    protected String getTitle()
    {
        return "Political Resources";
    }

    /**
     * Constructor
     * @param SimCity pModel the current sim city Model
     */
    public PoliticalPane(SimCity pModel)
    {
        super(pModel);
    }

    protected void setup()
    {
        add(getTitleLabel(), 0, 0, 4, 1);
        initLabels();
    }

    protected void initLabels()
    {
        mValues = new HashMap<String, Label>();
        String space = "         ";
        for (int i = 0; i < mMainNames.length; i++) {
            Label main  = new Label(mMainNames[i] + ":");
            Label value = new Label();
            Label tip   = new Label(space + mTipNames[i]);
            tip.setWrapText(true);
            main .setFont(new Font("Arial", 28));
            value.setFont(new Font("Arial", 28));
            tip  .setFont(new Font("Times New Roman", 20));
            setValignment(main,  VPos.TOP);
            setValignment(value, VPos.TOP);
            setValignment(tip,   VPos.TOP);
            mValues.put(mMainNames[i], value);
            add(main , 1, (2 * i) + 2);
            add(value, 2, (2 * i) + 2);
            add(tip  , 1, (2 * i) + 3, 2, 1);
        }
        update();
    }

    protected void update()
    {
        mValues.get("Funds"           ).setText("" + mModel.getResourceManager().getFunds());
        mValues.get("Market Shares"   ).setText("" + mModel.getResourceManager().getMarketShares());
        mValues.get("Emission Credits").setText("" + mModel.getResourceManager().getEmitCredits());
        mValues.get("Action Points"   ).setText("" + mModel.getResourceManager().getActionPoints());
    }
}
