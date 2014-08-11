package easigreen.service;

import easigreen.service.*;
import easigreen.system.*;

/**
 * The PlantManager Manages Power Plants
 *
 * @version 0.1.0
 * @author Larson Caldwell
 * @author Sam Graham
 * @author Haru McClellan
 */
public abstract class PlantManager
{
    //////////////////// Variables

    /**
     * The Manager of upgrades
     */
    protected UpgradeManager mUpgradeManager;

    /**
     * The actual upgrades
     */
    protected UpgradeMerger mUpgrades;
	
    /**
     * The Plant Object
     */
    protected Energy mPlant;

    //////////////////// Constructor
	
    /**
     * The plant manager manager is created with a new upgrade manager
     *
     * @param pUpgradeManager the new upgrade manager
     */
    public PlantManager(UpgradeManager pUpgradeManager)
    {
	mUpgradeManager = pUpgradeManager;
	update();
    }

    //////////////////// Methods

    /**
     * Updates the system as the data changes
     */
    public void update()
    {
	mUpgrades = mUpgradeManager.update();
    }

    /**
     * Adds new plants the the manager
     *
     * @param num the number of new plants
     */
    public void add(int num)
    {
	mPlant.add(num);
    }

    /**
     * Removes existing plants form the manager
     *
     * @param num amount of plants to be removed
     */
    public void remove(int num)
    {
	mPlant.remove(num);
    }

    /**
     * Gets the amount of a plants
     *
     * @return amount the amount of plants
     */
    public int getAmount()
    {
	return mPlant.getAmount();
    }

    /**
     * Sets the amount of plants to a value
     *
     * @param num the new amount of plants
     */
    public void setAmount(int num)
    {
	mPlant.setAmount(num);
    }

    //////////////////// Abstract Methods

    /**
     * Gets the cost to build a plant
     */
    public abstract double getCostBuild     ();

    /**
     * Gets the approval rating for each plant
     */
    public abstract double getCostRemove    ();

    /**
     * Gets the net approval rating
     */
    public abstract double getApproval      ();

    /**
     * Gets the power production for each plant
     */
    public abstract double getTotalApproval ();

    /**
     * Gets the net power production
     */
    public abstract double getPower         ();

    /**
     * Gets the net power production
     */
    public abstract double getTotalPower    ();

    /**
     * Gets the emissions for each plant
     */
    public abstract double getEmissions     ();

    /**
     * Gets the net emissions
     */
    public abstract double getTotalEmissions();

    /**
     * Gets the security for each plant
     */
    public abstract double getSecurity      ();

    /**
     * Gets the net security
     */
    public abstract double getTotalSecurity ();

    /**
     * Gets the profit for each plant
     */
    public abstract double getProfit        ();

    /**
     * Gets the net profit
     */
    public abstract double getTotalProfit   ();
}
