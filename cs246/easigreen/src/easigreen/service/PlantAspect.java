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
public class PlantAspect
{
    //////////////////// Variables

    /**
     * The change in the power production of a single plant
     */
    private double mPower;

    /**
     * The change in the cost of a single plant
     */
    private double mCost;

    /**
     * The change in the approval rating of each plant
     */
    private double mApproval;

    /**
     * The change in the emissions of a single plant
     */
    private double mEmissions;

    /**
     * The change in the security of a single plant
     */
    private double mSecurity;

    /**
     * The change in the profit of a single plant
     */
    private double mProfit;

    //////////////////// Constructor

    /**
     * All variables are set to a default value that can be changed as needed
     */
    public PlantAspect()
    {
        mPower     = 0;
        mCost      = 0;
        mApproval  = 0;
        mEmissions = 0;
        mSecurity  = 0;
        mProfit    = 0;
    }

    //////////////////// Methods

    /**
     * Returns the plants power upgrade
     *
     * @return double mPower
     */
    public double getPower()
    {
	return mPower;
    }

    /**
     * Returns the plants cost upgrade
     *
     * @return double mCost
     */
    public double getCost()
    {
	return mCost;
    }

    /**
     * Returns the plants approval upgrade
     *
     * @return double mApproval
     */
    public double getApproval()
    {
	return mApproval;
    }

    /**
     * Returns the plants emissions upgrade
     *
     * @return double mEmissions
     */
    public double getEmissions()
    {
	return mEmissions;
    }

    /**
     * Returns the plants Security upgrade
     *
     * @return double mSecurity
     */
    public double getSecurity()
    {
	return mSecurity;
    }

    /**
     * Returns the plants profit upgrade
     *
     * @return double mProfit
     */
    public double getProfit()
    {
	return mProfit;
    }

    /**
     * Sets the plants Power upgrade
     *
     * @param double pPower
     */
    public void setPower(double pPower)
    {
	mPower = pPower;
    }

    /**
     * Sets the plants cost upgrade
     *
     * @param double pCost
     */
    public void setCost(double pCost)
    {
	mCost = pCost;
    }

    /**
     * Sets the plants approval upgrade
     *
     * @param double pApproval
     */
    public void setApproval(double pApproval)
    {
	mApproval = pApproval;
    }

    /**
     * Sets the plants emissions upgrade
     *
     * @param double pEmissions
     */
    public void setEmissions(double pEmissions)
    {
	mEmissions = pEmissions;
    }

    /**
     * Sets the plants security upgrade
     *
     * @param double pSecurity
     */
    public void setSecurity(double pSecurity)
    {
	mSecurity = pSecurity;
    }

    /**
     * Sets the plants profit upgrade
     *
     * @param double pProfit
     */
    public void setProfit(double pProfit)
    {
	mProfit = pProfit;
    }
}
