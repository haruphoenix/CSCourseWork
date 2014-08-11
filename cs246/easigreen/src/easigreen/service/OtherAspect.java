package easigreen.service;

import easigreen.system.*;
import easigreen.service.*;

/**
 * The technology class contains the information about what will be changed
 * when it is implemented.
 *
 * @version 0.1.3
 * @author Larson Caldwell
 * @author Sam Graham
 * @author Haru McClellan
 */
public class OtherAspect
{
    //////////////////// Variables

    /**
     * The budget change
     */
    private double mBudget;

    /**
     * The energy demand change
     */
    private double mDemand;

    /**
     * The change in net emissions
     */
    private double mEmissions;

    //////////////////// Constructor

    /**
     * All variables are set to a default value that can be changed as needed
     */
    public OtherAspect()
    {
        mBudget    = 0;
        mDemand    = 0;
        mEmissions = 0;
    }
    
    //////////////////// Methods

    /**
     * Sets the budget upgrade
     *
     * @param double pBudget
     */
    public void setBudget(double pBudget)
    {
	mBudget = pBudget;
    }

    /**
     * Sets the demand upgrade
     *
     * @param double pDemand
     */
    public void setDemand(double pDemand)
    {
	mDemand = pDemand;
    }

    /**
     * Sets the net emissions upgrade
     *
     * @param double pEmissions
     */
    public void setEmissions(double pEmissions)
    {
	mEmissions = pEmissions;
    }

    /**
     * Returns the budget upgrade
     *
     * @return double mBudget
     */
    public double getBudget()
    {
	return mBudget;
    }

    /**
     * Returns the energy demand upgrade
     *
     * @return double mDemand
     */
    public double getDemand()
    {
	return mDemand;
    }

    /**
     * Returns the net emissions upgrade
     *
     * @return double mEmissions
     */
    public double getEmissions()
    {
	return mEmissions;
    }
}
