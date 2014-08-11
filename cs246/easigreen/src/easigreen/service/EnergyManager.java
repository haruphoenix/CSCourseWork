package easigreen.service;

/**
 * The EnergyManager contains the information for each form of energy, 
 * including fossil plants, nuclear plants, and renewable plants.
 *
 * @version 0.1.0
 * @author Larson Caldwell
 * @author Sam Graham
 * @author Haru McClellan
 */
public class EnergyManager
{
    //////////////////// Variables

    /**
     * The Manager of upgrades
     */
    private UpgradeManager mUpgradeManager;

    /**
     * The upgrades
     */
    private UpgradeMerger mUpgrades;

    /**
     * The Nuclear Plant Object
     */
    private NuclearManager mNuclear;

    /**
     * The Fossil Plant Object
     */
    private FossilManager mFossil;

    /**
     * The Renewable Plant Object
     */
    private RenewableManager mRenewable;

    /**
     * The Oil Object
     */
    private OilManager mOil;

    //////////////////// Constructor

    /**
     * All the array lists are set up and wired to the upgrade manager.
     *
     * @param pUpgradeManager the upgrade manager
     */
    public EnergyManager(UpgradeManager pUpgradeManager)
    {
        mUpgradeManager = pUpgradeManager;
        mNuclear        = new NuclearManager  (mUpgradeManager);
        mFossil         = new FossilManager   (mUpgradeManager);
        mRenewable      = new RenewableManager(mUpgradeManager);
        mOil            = new OilManager      (mUpgradeManager);
	update();
    }

    /**
     * Gets the nuclear plants
     *
     * @return mNuclear the nuclear plants
     */
    public NuclearManager getNuclear()
    {
	mNuclear.update();
        return mNuclear;
    }

    /**
     * Gets the fossil plants
     *
     * @return mFossil the fossil plants
     */
    public FossilManager getFossil()
    {
	mFossil.update();
        return mFossil;
    }

    /**
     * Gets the renewable plants
     *
     * @return mRenewable the renewable plants
     */
    public RenewableManager getRenewable()
    {
	mRenewable.update();
        return mRenewable;
    }

    /**
     * Gets the oil data
     *
     * @return mOil the oil data
     */
    public OilManager getOil()
    {
	mOil.update();
        return mOil;
    }

    /**
     * Applies upgrade and technology effects to the plants and oil
     */
    public void update()
    {
	mUpgrades = mUpgradeManager.update();
    }


    /**
     * Gets the total power produced with all the plants together
     *
     * @return power the power produced from all the plants
     */
    public double getPower()
    {
	return mNuclear.getTotalPower() + mFossil.getTotalPower() 
                  + mRenewable.getTotalPower();
    }

    /**
     * Gets the security of all the plants together
     *
     * @return security the security of all the plants combined
     */
    public double getSecurity()
    {
	return mNuclear.getTotalSecurity() + mFossil.getTotalSecurity() +
	    mRenewable.getTotalSecurity() + mOil.getSecurity();
    }

    /**
     * Gets the amount of all the plants together
     *
     * @return amount the number of all the plants total
     */
    public int getAmount()
    {
	return mNuclear.getAmount() + mFossil.getAmount() 
           + mRenewable.getAmount();
    }

    /**
     * Gets the approval of all the plants together
     *
     * @return approval the aproval of all the plants together
     */
    public double getApproval()
    {
	return ((mNuclear.getApproval() + mFossil.getApproval() 
           + mRenewable.getApproval()) / (double)getAmount());
    }

    /**
     * Gets the emissions of all the plants together
     *
     * @return emissions the emissions released from all of the plants together
     */
    public double getEmissions()
    {
	return mNuclear.getTotalEmissions() + mFossil.getTotalEmissions() + 
	    mRenewable.getTotalEmissions() + mOil.getEmissions();
    }

    /**
     * Gets the profit of all the plants together
     *
     * @return profit the profit from all of the plants
     */
    public double getProfit()
    {
	return mNuclear.getTotalProfit() + mFossil.getTotalProfit() 
           + mRenewable.getTotalProfit();
    }
}
