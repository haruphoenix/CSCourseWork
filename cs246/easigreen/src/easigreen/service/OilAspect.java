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
public class OilAspect
{
    //////////////////// Variables

    /**
     * The change in the daily oil consumption
     */
    private double mConsumption;

    /**
     * The change in the oil security
     */
    private double mSecurity;

    /**
     * The change in the oil growth
     */
    private double mGrowth;

    //////////////////// Constructor

    /**
     * All variables are set to a default value that can be changed as needed
     */
    public OilAspect()
    {
        mConsumption = 0;
        mSecurity    = 0;
        mGrowth      = 0;
    }

    //////////////////// Methods

    /**
     * Returns the oil consumption upgrade
     *
     * @return double mConsumption
     */
    public double getConsumption()
    {
	return mConsumption;
    }

    /**
     * Returns the oil security upgrade
     *
     * @return double mSecurity
     */
    public double getSecurity()
    {
	return mSecurity;
    }

    /**
     * Returns the oil growth upgrade
     *
     * @return double mGrowth
     */
    public double getGrowth()
    {
	return mGrowth;
    }

    /**
     * Sets the oil consumption upgrade
     *
     * @param double pConsumption
     */
    public void setConsumption(double pConsumption)
    {
	mConsumption = pConsumption;
    }

    /**
     * Sets the oil security upgrade
     *
     * @param double pSecurity
     */
    public void setSecurity(double pSecurity)
    {
	mSecurity = pSecurity;
    }

    /**
     * Sets the oil growth upgrade
     *
     * @param double pGrowth
     */
    public void setGrowth(double pGrowth)
    {
	mGrowth = pGrowth;
    }
}
