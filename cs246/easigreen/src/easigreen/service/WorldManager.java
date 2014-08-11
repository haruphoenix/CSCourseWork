package easigreen.service;

/**
 * The ResourceManager Manages Resources
 *
 * @version 0.1.2
 * @author Larson Caldwell
 * @author Sam Graham
 * @author Haru McClellan
 */
public class WorldManager
{
    //////////////////// Variables

    /**
     * The total amount of funds (in billions)
     */
    private double mBudget;

    /**
     * Get the budget
     *
     * @return mBudget the world budget
     */
    public double getBudget()
    {
	return mBudget;
    }

    /**
     * Set the budget to a new value
     *
     * @param pBudget the new budget
     */
    public void setBudget(double pBudget)
    {
	mBudget = pBudget;
    }
}