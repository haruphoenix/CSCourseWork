package easigreen.service;

import easigreen.service.*;
import easigreen.system.*;

/**
 * The FossilManager contains imortaint information about the fossil plants
 *
 * @version 0.1.0
 * @author Larson Caldwell
 * @author Sam Graham
 * @author Haru McClellan
 */
public class FossilManager extends PlantManager
{
    //////////////////// Constructors
	
    /**
     * Creates a new fossil plant object using the upgrade manager
     *
     * @param pUpgradeManager the upgrade manager to be called
     */
    public FossilManager(UpgradeManager pUpgradeManager)
    {
	super(pUpgradeManager);
	mPlant = new Fossil();
    }

    //////////////////// Methods

    /**
     * Gets the cost to remove a plant
     *
     * @return costRemove the cost to remove a plant
     */
    public double getCostRemove()
    {
	return mPlant.getCostRemove();
    }

    /**
     * Gets the cost to build a plant
     *
     * @return costBuild the cost to build a plant
     */
    public double getCostBuild()
    {
	return mPlant.getCostBuild() + mUpgrades.getFossilCost();
    }

    /**
     * Gets the approval rating for each plant
     *
     * @return approval the approval rating for each plant 
     */
    public double getApproval()
    {
	return mPlant.getApproval() + mUpgrades.getFossilApproval();
    }

    /**
     * Gets the net approval rating
     *
     * @return totalApproval the net approval rating
     */
    public double getTotalApproval()
    {
	return getApproval() * (double)getAmount();
    }

    /**
     * Gets the power production for each plant
     *
     * @return power the power production for each plant
     */
    public double getPower()
    {
	return mPlant.getPower() + mUpgrades.getFossilPower();
    }

    /**
     * Gets the net power production
     *
     * @return totalPower the net power production
     */
    public double getTotalPower()
    {
	return getPower() * (double)getAmount();
    }

    /**
     * Gets the emissions for each plant
     *
     * @return emissions the emissions for each plant 
     */
    public double getEmissions()
    {
	return mPlant.getEmissions() + mUpgrades.getFossilEmissions();
    }

    /**
     * Gets the net emissions
     *
     * @return totalEmissions the net emissions  
     */
    public double getTotalEmissions()
    {
	return getEmissions() * (double)getAmount();
    }

    /**
     * Gets the security for each plant
     *
     * @return security the security for each plant  
     */
    public double getSecurity()
    {
	return mPlant.getSecurity() + mUpgrades.getFossilSecurity();
    }

    /**
     * Gets the net security
     *
     * @return totalSecurity the net security
     */
    public double getTotalSecurity()
    {
	return getSecurity() * (double)getAmount();
    }

    /**
     * Gets the profit for each plant
     *
     * @return profit the profit for each plant
     */
    public double getProfit()
    {
	return mPlant.getProfit() + mUpgrades.getFossilProfit();
    }

    /**
     * Gets the net profit
     *
     * @return totalProfit the new profit
     */
    public double getTotalProfit()
    {
	return getProfit() * (double)getAmount();
    }
}
