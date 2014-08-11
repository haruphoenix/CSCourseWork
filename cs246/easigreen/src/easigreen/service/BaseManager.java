package easigreen.service;

/**
 * The BaseManager Manages base values that will be used as a referance when
 * accessing different round information.
 *
 * @version 0.1.2
 * @author Larson Caldwell
 * @author Sam Graham
 * @author Haru McClellan
 */
public class BaseManager
{
    //////////////////// Variables

    /**
     * The current round number
     */
    private int mRoundNumber;

    /**
     * The Default action points
     */
    private static int mActionPoints;

    /**
     * The Default budget
     */
    private static final double M_BUDGET = 9;

    /**
     * The Default demand
     */
    private static final double M_DEMAND = 100;


    //////////////////// Constructors

    /**
     * Constructor
     */
    public BaseManager()
    {
	mRoundNumber  = 0;
	mActionPoints = 8;
    }

    /**
     * Increases the round Number
     */
    public void nextRound()
    {
	mRoundNumber++;
	mActionPoints = 20;
    }

    /**
     * Increases the round Number
     * @param pRound the round to set to
     */
    public void setRound(int pRound)
    {
	mRoundNumber = pRound;
	
    }

    /**
     * Get the round Number
     * @return mRoundNumber the current round number
     */
    public int getRound()
    {
	return mRoundNumber;
    }

    /**
     * Gets the Action Points
     * @return mActionPoints the action points for the round
     */
    public int getActionPoints()
    {
	return mActionPoints;
    }

    /**
     * Get this rounds budget
     * @return mBudget the current rounds budget
     */
    public double getBudget()
    {
	return M_BUDGET + (double)(mRoundNumber * 15);
    }
    
    /**
     * Get this rounds demand
     * @return mDemand the current rounds demand
     */
    public double getDemand()
    {
	return M_DEMAND + (double)(mRoundNumber * 5);
    }
}
