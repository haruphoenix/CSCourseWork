package easigreen.service;

import easigreen.system.*;

import java.util.ArrayList;

/**
 * The Simulator class contains information that each different type of plant
 * will use.  It will contain the number of a particular type of plant, the
 * cost for each one, and the impacts that it will have on the short-term and
 * long-term goals.
 *
 * @see java.util.ArrayList
 *
 * @version 0.1.2
 * @author Larson Caldwell
 * @author Sam Graham
 * @author Haru McClellan
 */
public class Upgrade
{
    //////////////////// Variables

    /**
     * The budget change
     */
    private double mBudgetChange;

    /**
     * The price change
     */
    private double mPriceChange;

    /**
     * The approval Change
     */
    private double mApprovalChange;

    /**
     * The change in the approval rating of each nuclear plant
     */
    private double mNatt;

    /**
     * The change in the security of a single nuclear plant
     */
    private double mNsec;

    /**
     * The change in the approval rating of each fossil plant
     */
    private double mFatt;

    /**
     * The change in the security of a single fossil plant
     */
    private double mFsec;

    /**
     * The change in the approval rating of each renewable plant
     */
    private double mRatt;

    /**
     * The change in the security of a single renewable plant
     */
    private double mRsec;

    /**
     * The change in the daily oil consumption
     */
    private double mOil;

    /**
     * The change in the oil security
     */
    private double mOilSec;

    /**
     * The change in the oil growth
     */
    private double mOilGrow;

    ////////////////////////////// Getters

    /**
     * Get the change in budget
     *
     * @return the change in budget
     */
    public double getBudgetChange()
    {
        return mBudgetChange;
    }

    /**
     * Get the change in energy price
     *
     * @return the change in the energy price
     */
    public double getPriceChange()
    {
        return mPriceChange;
    }

    /**
     * Get the change in approval
     *
     * @return the change in approval
     */
    public double getApprovalChange()
    {
        return mApprovalChange;
    }

    /**
     * Get the change in nuclear approval rating
     *
     * @return the change in nuclear approval rating
     */
    public double getNatt()
    {
        return mNatt;
    }

    /**
     * Get the change in Nuclear Security
     *
     * @return the change in nuclear security
     */
    public double getNsec()
    {
        return mNsec;
    }

    /**
     * Get the change in fossil approval rating
     *
     * @return the change in fossil approval rating
     */
    public double getFatt()
    {
        return mFatt;
    }

    /**
     * Get the change in fossil security
     *
     * @return the change in fossil security
     */
    public double getFsec()
    {
        return mFsec;
    }

    /**
     * Get the change in approval rating of renewable
     *
     * @return the change in approval rating of renewable
     */
    public double getRatt()
    {
        return mRatt;
    }

    /**
     * Get the change in renewable security
     *
     * @return the change in renewable security
     */
    public double getRsec()
    {
        return mRsec;
    }

    /**
     * Get the change in daily oil consumption
     *
     * @return the change in daily oil consumption
     */
    public double getOil()
    {
        return mOil;
    }

    /**
     * Get the change in oil security
     *
     * @return the change in oil security
     */
    public double getOilSec()
    {
        return mOilSec;
    }

    /**
     * Get the change in oil growth
     *
     * @return the change in oil growth
     */
    public double getOilGrow()
    {
        return mOilGrow;
    }

    //////////////////////// Setters

    /**
     * Set the change in budget
     *
     * @param pBudgetChange change in budget
     */
    public void setBudgetChange(int pBudgetChange)
    {
        mBudgetChange = pBudgetChange;
    }

    /**
     * Set the change in the energy price
     *
     * @param pNRGChange change in the energy price
     */
    public void setPriceChange(int pPriceChange)
    {
        mPriceChange = pPriceChange;
    }

    /**
     * Set the change in approval
     *
     * @param pEmissionsChange change in approval
     */
    public void setApprovalChange(double pApprovalChange)
    {
        mApprovalChange = pApprovalChange;
    }

    /**
     * Set the change in nuclear approval rating
     *
     * @param pNatt a double
     */
    public void setNatt(double pNatt)
    {
        mNatt = pNatt;
    }

    /**
     * Set the change in nuclear security
     *
     * @param pNsec a double
     */
    public void setNsec(double pNsec)
    {
        mNsec = pNsec;
    }

    /**
     * Set the change in fossil approval rating
     *
     * @param pFatt a double
     */
    public void setFatt(double pFatt)
    {
        mFatt = pFatt;
    }

    /**
     * Set the change in fossil security
     *
     * @param pFsec a double
     */
    public void setFsec(double pFsec)
    {
        mFsec = pFsec;
    }

    /**
     * Set the change in renewable approval rating
     *
     * @param pRatt a double
     */
    public void setRatt(double pRatt)
    {
        mRatt = pRatt;
    }

    /**
     * Set the change in renewable security
     *
     * @param pRsec a double
     */
    public void setRsec(double pRsec)
    {
        mRsec = pRsec;
    }

    /**
     * Set the change in daily oil consumption
     *
     * @param pOil
     */
    public void setOil(double pOil)
    {
        mOil = pOil;
    }

    /**
     * Set the change in oil security
     *
     * @param pOilSec a double
     */
    public void setOilSec(double pOilSec)
    {
        mOil = pOilSec;
    }

    /**
     * Set the change in oil growth
     *
     * @param pOilGrow a double
     */
    public void setOilGrow(double pOilGrow)
    {
        mOil = pOilGrow;
    }
}
