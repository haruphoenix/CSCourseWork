package easigreen.service;

import easigreen.system.*;

/**
 * The oil class contains information about the current oil status.  This
 * includes oil security, consumption and emissions.  These values can be
 * adjusted through getters.
 *
 * @version 0.1.1
 * @author Larson Caldwell
 * @author Sam Graham
 * @author Haru McClellan
 */
public class Oil
{
    //////////////////// Variables

    /**
     * Daily consumption of oil
     */
    final private static double mConsumption = 1.7;

    /**
     * Security rating of oil
     */
    final private static double mSecurity = -17;

    /**
     * Oil growth per round
     */
    final private static double mGrowth = 20;

    /**
     * Oil Emissions
     */
    final private static double mEmissions = 100;

    //////////////////// Methods

    /**
     * Gets the daily consumption of oil
     *
     * @return mConsumption the daily consumption of oil
     */
    public double getConsumption()
    {
        return mConsumption;
    }

    /**
     * Gets the security rating of oil
     *
     * @return mSecurity the security rating of oil
     */
    public double getSecurity()
    {
        return mSecurity;
    }

    /**
     * Gets the growth of oil per round
     *
     * @return mGrowth the growth of oil per round
     */
    public double getGrowth()
    {
        return mGrowth;
    }

    /**
     * Gets the emissions per round caused by oil
     *
     * @return mEmissions the oil emissions per round
     */
    public double getEmissions()
    {
        return mEmissions;
    }

}
