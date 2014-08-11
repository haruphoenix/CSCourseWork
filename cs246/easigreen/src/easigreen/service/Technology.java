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
public class Technology
{
    //////////////////// Variables

    /**
     * 1 to 10 scale of the technology quality
     */
    protected int mQuality;
    	
     /**
     * Name of the Technology
     */
    protected String mName;

    /**
     * Holds the current code associated with the technology
     */
    protected String mCode;

    /**
     * The Nuclear Aspect of the tech
     */
    protected PlantAspect mNuclear;

    /**
     * The Fossil Aspect of the tech
     */
    protected PlantAspect mFossil;
    
    /**
     * The Renewable Aspect of the tech
     */
    protected PlantAspect mRenewable;

    /**
     * The Oil Aspect of the tech
     */
    protected OilAspect   mOil;

    /**
     * The Other Aspect of the tech
     */
    protected OtherAspect mOther;

    //////////////////// Constructor

    /**
     * Member varables are instanciated as default values
     */
    public Technology()
    {
	mName      = "Unknown";
	mCode      = "0";
	mNuclear   = new PlantAspect();
	mFossil    = new PlantAspect();
	mRenewable = new PlantAspect();
	mOil       = new OilAspect  ();
	mOther     = new OtherAspect();
    }

    //////////////////// Methods

    /**
     * The name of the technology
     *
     * @return the String of the name
     */
    public String getName()
    {
       return mName;
    }
    
    /**
     * Sets the name of the technology
     *
     * @param String pName the name of the tech
     */
    public void setName(String pName)
    {
	mName = pName;
    }

    /**
     * Returns the quality of the technology
     *
     * @return int mQuality the quality of the tech
     */
    public int getQuality()
    {
	return mQuality;
    }

    /**
     * Sets the quality of the technology
     *
     * @param int pQuality the quality on a scale from 1 to ten
     */
    public void setQuality(int pQuality)
    {
	mQuality = pQuality;
    }
    
    /**
     * Sets current technology code
     *
     * @param String pCode 
     */
    public void setCode(String pCode)
    {
	mCode = pCode;
    }

    /**
     * returns the tech's current code
     *
     * @return String mCode the techs current code
     */
    public String getCode()
    {
	return mCode;
    }

    /**
     * Gets the Nuclear Aspect of the upgrade
     *
     * @return PlantAspect mNuclear
     */
    public PlantAspect getNuclear()
    {
	return mNuclear;
    }

    /**
     * Gets the Fossil Aspect of the upgrade
     *
     * @return PlantAspect mFossil
     */
    public PlantAspect getFossil()
    {
	return mFossil;
    }

    /**
     * Gets the Renewable Aspect of the upgrade
     *
     * @return PlantAspect mRenewable
     */
    public PlantAspect getRenewable()
    {
	return mRenewable;
    }

    /**
     * Gets the Oil Aspect of the upgrade
     *
     * @return OilAspect mOil
     */
    public OilAspect getOil()
    {
	return mOil;
    }

    /**
     * Gets the Other Aspect of the upgrade
     *
     * @return OtherAspect mOther
     */
    public OtherAspect getOther()
    {
	return mOther;
    }
}
