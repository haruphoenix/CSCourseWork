package easigreen.service;

import easigreen.system.*;

import java.util.ArrayList;

/**
 * The trade class contains the information about a specific trade scenario.
 * The trade commodities are budget, market shares, emission credits, and
 * technologies.  These values are placed into trades from the simulator.
 *
 * @see java.util.ArrayList
 *
 * @version 0.1.0
 * @author Larson Caldwell
 * @author Sam Graham
 * @author Haru McClellan
 */
public class Trade
{
    //////////////////// Variables

    /**
     * The budget that has been placed into the trade
     */
    private int mBudget;

    /**
     * The emission credits that has been placed into the trade
     */
    private int mEmissionCredits;

    /**
     * The market shares that has been placed into the trade
     */
    private int mMarketShares;

    /**
     * The budget that has been placed into the trade
     */
    private ArrayList<Technology> mTechnologies;

    //////////////////// Constructor

    /**
     * Constructs a trade with specific values for the amount of assets that 
     * are being traded.
     *
     * @param pBudget the money that is being traded
     * @param pEmissionCredits the emission credits that are being traded
     * @param pMarketShares the market shares that are being traded
     * @param pTechnologies the technologies being traded
     */
    public Trade(int pBudget, int pEmissionCredits, int pMarketShares,
                 ArrayList<Technology> pTechnologies)
    {
        mBudget = pBudget;
        mEmissionCredits = pEmissionCredits;
        mMarketShares = pMarketShares;
        mTechnologies = pTechnologies;
    }

    //////////////////// Methods

    /**
     * returns the budget to be traded
     *
     * @return mBudget the money that is being traded
     */
    public int getBudget()
    {
        return mBudget;
    }

    /**
     * returns the emission credits to be traded
     *
     * @return mEmissionCredits the emission credits that are being traded
     */
    public int getEmissionCredits()
    {
        return mEmissionCredits;
    }

    /**
     * returns the market shares to be traded
     *
     * @return mMarketShares the market shares that are being traded
     */
    public int getMarketShares()
    {
        return mMarketShares;
    }

    /**
     * returns the technologies
     *
     * @return mTechnologies the technologies that are being traded
     */
    public ArrayList<Technology> getTechnologies()
    {
        return mTechnologies;
    }
}
