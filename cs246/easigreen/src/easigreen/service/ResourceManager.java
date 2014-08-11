package easigreen.service;

/**
 * The ResourceManager Manages Resources
 *
 * @version 0.1.2
 * @author Larson Caldwell
 * @author Sam Graham
 * @author Haru McClellan
 */
public class ResourceManager
{
    //////////////////// Variables
    
    /**
     * A Manager to hold base values depending on round
     */
    private BaseManager mBaseManager;

    /**
     * A Manager to hold all the upgrades
     */
    private UpgradeManager mUpgradeManager;

    /**
     * The number of action points
     */
    private int mActionPoints;

    /**
     * The number of emission credits
     */
    private int mEmitCredits;

    /**
     * The number of market shares
     */
    private int mMarketShares;

    /**
     * The total amount of funds (in billions)
     */
    private double mFunds;

    /**
     * The Total Demand with Market shares and upgrades taken into account
     */
    private double mDemand;

    /**
     * The Total Budget with regards to upgrades
     */
    private double mBudget;

    //////////////////// Constructors

    /**
     * Sets the member variables to default values
     *
     * @param pBaseManager the programs base manager
     * @param pUpgradeManager the programas upgrade manager
     */
    public ResourceManager(BaseManager pBaseManager, 
                           UpgradeManager pUpgradeManager)
    {
	mBaseManager    = pBaseManager;
	mUpgradeManager = pUpgradeManager;
	mActionPoints   = mBaseManager.getActionPoints();
	mEmitCredits    = 0;
	mMarketShares   = 0;
	mBudget         = mBaseManager.getBudget();
	mFunds          = mBaseManager.getBudget();
	mDemand         = mBaseManager.getDemand();
    }

    //////////////////// Methods

    /**
     * Returns the budget for this round
     *
     * @return mBudget the total budget
     */
    public double getBudget()
    {
	return mBudget + mUpgradeManager.update().getBudgetChange();
    }

    /**
     * Returns the modified energy demand
     *
     * @return mDemand a Double holding the demand
     */
    public double getDemand()
    {
	return mDemand + mMarketShares 
           + mUpgradeManager.update().getDemandChange();
    }

    /**
     * Emission credits are gained here
     *
     * @param credits the number of credits being bought
     */
    public void buyEmissionCredits(int credits)
    {
        mEmitCredits +=  credits;
    }

    /**
     * Emission credits are spent here
     *
     * @param credits the number of credits being sold
     */
    public void sellEmissionCredits(int credits)
    {
        mEmitCredits -=  credits;
    }

    /**
     * Market shares are gained here
     *
     * @param shares the amount of shares being bought
     */
    public void buyMarketShares(int shares)
    {
        mMarketShares += shares;
    }

    /**2
     * Market shares are spent here
     *
     * @param shares the amount of shares being sold
     */
    public void sellMarketShares(int shares)
    {
        mMarketShares += shares;
    }

    /**
     * Money is spent here
     *
     * @param amount the amount of money being spent
     */
    public void spendMoney(double amount)
    {
        mFunds -= amount;
    }

    /**
     * Money is earned here
     *
     * @param amount the amount of money being earned
     */
    public void earnMoney(double amount)
    {
        mFunds += amount;
    }

    /**
     * Action Points are spent here
     *
     * @param amount of action points being used
     */
    public void spendActionPoints(int amount)
    {
        mActionPoints -= amount;
    }

    /**
     * Action Points are gained here
     *
     * @param amount of action points being gained
     */
    public void earnActionPoints(int amount)
    {
        mActionPoints += amount;
    }

    /**
     * Action points can be traded for money here
     *
     * @param actions amount of action points to trade for cash
     */
    public void cashInActionPoints(int amount)
    {
        mActionPoints -= amount;
        mFunds += (amount * .5);
    }

    /**
     * Technologies can be traded for money with this method
     *
     * @param techs amount of technologies to trade for cash
     */
    public void cashInTechnologies(int techs)
    {
        mFunds += (techs * .5);
    }

    //////////////////// Getters

    /**
     * Gets the action points
     *
     * @return mActionPoints the action points
     */
    public int getActionPoints()
    {
        return mActionPoints;
    }

    /**
     * Gets the emission credits
     *
     * @return mEmitCredits the emission credits
     */
    public int getEmitCredits()
    {
        return mEmitCredits;
    }

    /**
     * Gets the market shares
     *
     * @return mMarketShares the market shares
     */
    public int getMarketShares()
    {
        return mMarketShares;
    }

    /**
     * Gets the budget
     *
     * @return mBudget the budget
     */
    public double getFunds()
    {
        return mFunds;
    }

    //////////////////// Setters

    /**
     * Sets the action points to a new value
     *
     * @param amount the new amount of action points
     */
    public void setActionPoints(int amount)
    {
        mActionPoints = amount;
    }

    /**
     * Sets the emission credits to a new amount
     *
     * @param amount the new amount of emission credits
     */
    public void setEmitCredits(int amount)
    {
        mEmitCredits = amount;
    }

    /**
     * Sets the number of market shares to a new amount
     *
     * @param amount the new amount of market shares
     */
    public void setMarketShares(int amount)
    {
        mMarketShares = amount;
    }

    /**
     * Sets the budget to a new value
     *
     * @param pBudget the new budget value
     */
    public void setFunds(double pFunds)
    {
        mFunds = pFunds;
    }
}
