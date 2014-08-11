package easigreen.service;

import easigreen.service.*;
import easigreen.system.*;

/**
 * The Oil Manager Manages Oil
 *
 * @version 0.1.0
 * @author Larson Caldwell
 * @author Sam Graham
 * @author Haru McClellan
 */
public class OilManager
{
    //////////////////// Variables

    /**
     * The Manager of upgrades
     */
    private UpgradeManager mUpgradeManager;

    /**
     * The actual upgrades
     */
    private UpgradeMerger mUpgrades;
	
    /**
     * The Oil Object
     */
    private Oil mOil;

    //////////////////// Constructor
	
    /**
     * Oil manager is created with a new upgrade manager
     *
     * @param pUpgradeManager the new upgrade manager
     */
    public OilManager(UpgradeManager pUpgradeManager)
    {
	mUpgradeManager = pUpgradeManager;
	mOil = new Oil();
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
     * Get the oil consumption
     *
     * @return consumption the oil consumption
     */
    public double getConsumption()
    {
	return mOil.getConsumption() + mUpgrades.getOilConsumption();
    }

    /**
     * Get the oil growth
     *
     * @return growth the oil growth
     */
    public double getGrowth()
    {
	return mOil.getGrowth() + mUpgrades.getOilGrowth();
    }

    /**
     * Get the emissions from oil
     *
     * @return emissions the emissions due to oil
     */
    public double getEmissions()
    {
	return mOil.getEmissions() * mOil.getConsumption();
    }

    /**
     * Get the oil security
     *
     * @return security the security of the oil
     */
    public double getSecurity()
    {
	return mOil.getSecurity() + mUpgrades.getOilSecurity();
    }

    /**
     * Get the total security of the oil
     *
     * @return totalSecurity the total security of the oil
     */
    public double getTotalSecurity()
    {
	return getSecurity() * getConsumption();
    }
}
