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
 * Technology Entry for An upgrade
 * @version 0.2.0
 * @author Haru McClellan
 */
public class TechEntry
    extends TextArea
{
    /**
     * Holds reference to Sim City Model
     */
    private SimCity mModel;

    /**
     * Updater
     */
    protected void update(String pTechName)
    {
	Technology t = mModel.getUpgradeManager().getTechnologyManager().lookup(pTechName);
	if (t != null)
	{
	    String text = "";
	    if (t.getOther().getBudget   () != 0) text += "Budget: "          + t.getOther().getBudget   () + "\n";
	    if (t.getOther().getDemand   () != 0) text += "Energy Demand: "   + t.getOther().getDemand   () + "\n";
	    if (t.getOther().getEmissions() != 0) text += "Total Emissions: " + t.getOther().getEmissions() + "\n";

	    if (t.getNuclear().getPower    () != 0) text += "Nuclear Energy: "    + t.getNuclear().getPower    () + "\n";
	    if (t.getNuclear().getCost     () != 0) text += "Nuclear Cost: "      + t.getNuclear().getCost     () + "\n";
	    if (t.getNuclear().getApproval () != 0) text += "Nuclear Approval: "  + t.getNuclear().getApproval () + "\n";
	    if (t.getNuclear().getEmissions() != 0) text += "Nuclear Emissions: " + t.getNuclear().getEmissions() + "\n";
	    if (t.getNuclear().getSecurity () != 0) text += "Nuclear Security: "  + t.getNuclear().getSecurity () + "\n";
	    if (t.getNuclear().getProfit   () != 0) text += "Nuclear Profit: "    + t.getNuclear().getProfit   () + "\n";

	    if (t.getFossil().getPower    () != 0) text += "Fossil Fuel Energy: "    + t.getFossil().getPower    () + "\n";
	    if (t.getFossil().getCost     () != 0) text += "Fossil Fuel Cost: "      + t.getFossil().getCost     () + "\n";
	    if (t.getFossil().getApproval () != 0) text += "Fossil Fuel Approval: "  + t.getFossil().getApproval () + "\n";
	    if (t.getFossil().getEmissions() != 0) text += "Fossil Fuel Emissions: " + t.getFossil().getEmissions() + "\n";
	    if (t.getFossil().getSecurity () != 0) text += "Fossil Fuel Security: "  + t.getFossil().getSecurity () + "\n";
	    if (t.getFossil().getProfit   () != 0) text += "Fossil Fuel Profit: "    + t.getFossil().getProfit   () + "\n";

	    if (t.getRenewable().getPower    () != 0) text += "Renewable Energy: "    + t.getRenewable().getPower    () + "\n";
	    if (t.getRenewable().getCost     () != 0) text += "Renewable Cost: "      + t.getRenewable().getCost     () + "\n";
	    if (t.getRenewable().getApproval () != 0) text += "Renewable Approval: "  + t.getRenewable().getApproval () + "\n";
	    if (t.getRenewable().getEmissions() != 0) text += "Renewable Emissions: " + t.getRenewable().getEmissions() + "\n";
	    if (t.getRenewable().getSecurity () != 0) text += "Renewable Security: "  + t.getRenewable().getSecurity () + "\n";
	    if (t.getRenewable().getProfit   () != 0) text += "Renewable Profit: "    + t.getRenewable().getProfit   () + "\n";

	    if (t.getOil().getConsumption() != 0) text += "Oil Consumption: " + t.getOil().getConsumption() + "\n";
	    if (t.getOil().getSecurity   () != 0) text += "Oil Security: "    + t.getOil().getSecurity   () + "\n";
	    if (t.getOil().getGrowth     () != 0) text += "Oil Growth: "      + t.getOil().getGrowth     () + "\n";
	    setText(text);
	}
    }

    /**
     * Constructor
     * @param pModel the current SimCity Model
     */
    public TechEntry(SimCity pModel)
    {
        mModel = pModel;
	setWrapText(true);
    }
}
