package easigreen.service;

import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;

/**
 * The Technology Manager class.
 *
 * @see java.util.ArrayList
 *
 * @version 0.1.2
 * @author Larson Caldwell
 * @author Sam Graham
 * @author Haru McClellan
 */
public class TechnologyManager
{
    //////////////////// Variables

    /**
     * The implemented technologies
     */
    private ArrayList<Technology> mImplemented;

    /**
     * The available technologies
     */
    private ArrayList<Technology> mAvailable;

    /**
     * All of the technologies
     */
    private ArrayList<Technology> mAll;

    /**
     * Nuclear Technologies
     */
    private ArrayList<Technology> mNuclear;

    /**
     * Fossil Fuel Technologies
     */
    private ArrayList<Technology> mFossil;

    /**
     * Renewable Technologies
     */
    private ArrayList<Technology> mRenewable;

    /**
     * Oil Technologies
     */
    private ArrayList<Technology> mOil;

    /**
     * An alternate data structure for holding available techs
     * so they can be referenced by their name
     */
    private Map<String, Technology> mNames;

    /**
     * Holds all technologies referenced by their name
     */
    private Map<String, Technology> mLookup;

    /**
     * Holds the tech codes and creates technologies
     */
    private TechCodeManager mCodes;

    //////////////////// Constructor

    /**
     * Basic constructor of the array lists
     */
    public TechnologyManager()
    {
        mImplemented = new ArrayList<Technology>();
        mAvailable   = new ArrayList<Technology>();
        mNuclear     = new ArrayList<Technology>();
	mFossil      = new ArrayList<Technology>();
	mRenewable   = new ArrayList<Technology>();
	mOil         = new ArrayList<Technology>();
        mAll         = new TechnologyGetter().getTechnologies();
	mCodes       = new TechCodeManager(mAll);
	mNames       = new HashMap<String, Technology>();
	mLookup      = new HashMap<String, Technology>();
	setPlantLists();
	setLookup();
    }

    //////////////////// Methods

    /**
     * Populates the lookup map using every technology
     */
    private void setLookup()
    {
	for (Technology t : mAll)
	{
	    mLookup.put(t.getName(), t);
	}
    }

    /**
     * Returns a technology by name
     *
     * @param techName the name to lookup
     * @return tech the tech associated with name
     */
    public Technology lookup(String techName)
    {
	return mLookup.get(techName);
    }

    /**
     * Adds specific types of technologies to plant lists
     */
    private void setPlantLists()
    {
	for (Technology t : mAll)
	{
	    // Add to nuclear if it affects nuclear plants
	    if ((t.getNuclear().getPower    () > 0) ||
		(t.getNuclear().getCost     () < 0) ||
		(t.getNuclear().getApproval () > 0) ||
		(t.getNuclear().getSecurity () > 0) ||
		(t.getNuclear().getEmissions() < 0) ||
		(t.getNuclear().getProfit   () > 0)) 
	    {
		mNuclear.add(t);
	    }
	    // Add to fossil if it affects fossil plants
	    if ((t.getFossil().getPower    () > 0) ||
		(t.getFossil().getCost     () < 0) ||
		(t.getFossil().getApproval () > 0) ||
		(t.getFossil().getSecurity () > 0) ||
		(t.getFossil().getEmissions() < 0) ||
		(t.getFossil().getProfit   () > 0)) 
	    {
		mFossil.add(t);
	    } 
	    // Add to renewable if it affects renewable plants
	    if ((t.getRenewable().getPower    () > 0) ||
		(t.getRenewable().getCost     () < 0) ||
		(t.getRenewable().getApproval () > 0) ||
		(t.getRenewable().getSecurity () > 0) ||
		(t.getRenewable().getEmissions() < 0) ||
		(t.getRenewable().getProfit   () > 0)) 
	    {
		mRenewable.add(t);
	    } 
	    // Add to oil if it affects oil plants
	    if ((t.getOil().getConsumption() < 0) ||
		(t.getOil().getSecurity   () > 0) ||
		(t.getOil().getGrowth     () < 0)) 
	    {
		mOil.add(t);
	    } 
	}
    }

    /**
     * Updates the Merger
     *
     * @returns UpgradeMerger the UpgradeMerger
     */
    public UpgradeMerger update()
    {
        UpgradeMerger allChanges = new UpgradeMerger();
        for (int i = 0; i < mImplemented.size(); i++) {
            // General
            allChanges.addBudgetChange      (mImplemented.get(i).getOther().getBudget   ());
            allChanges.addDemandRateChange  (mImplemented.get(i).getOther().getDemand   ());
            allChanges.addEmissionsChange   (mImplemented.get(i).getOther().getEmissions());
            // Nuclear
            allChanges.addNuclearPower      (mImplemented.get(i).getNuclear().getPower    ());
            allChanges.addNuclearCost       (mImplemented.get(i).getNuclear().getCost     ());
            allChanges.addNuclearApproval   (mImplemented.get(i).getNuclear().getApproval ());
            allChanges.addNuclearEmissions  (mImplemented.get(i).getNuclear().getEmissions());
            allChanges.addNuclearSecurity   (mImplemented.get(i).getNuclear().getSecurity ());
            allChanges.addNuclearProfit     (mImplemented.get(i).getNuclear().getProfit   ());
            // Fossil
            allChanges.addFossilPower       (mImplemented.get(i).getFossil().getPower    ());
            allChanges.addFossilCost        (mImplemented.get(i).getFossil().getCost     ());
            allChanges.addFossilApproval    (mImplemented.get(i).getFossil().getApproval ());
            allChanges.addFossilEmissions   (mImplemented.get(i).getFossil().getEmissions());
            allChanges.addFossilSecurity    (mImplemented.get(i).getFossil().getSecurity ());
            allChanges.addFossilProfit      (mImplemented.get(i).getFossil().getProfit   ());
            // Renewable
            allChanges.addRenewablePower    (mImplemented.get(i).getRenewable().getPower    ());
            allChanges.addRenewableCost     (mImplemented.get(i).getRenewable().getCost     ());
            allChanges.addRenewableApproval (mImplemented.get(i).getRenewable().getApproval ());
            allChanges.addRenewableEmissions(mImplemented.get(i).getRenewable().getEmissions());
            allChanges.addRenewableSecurity (mImplemented.get(i).getRenewable().getSecurity ());
            allChanges.addRenewableProfit   (mImplemented.get(i).getRenewable().getProfit   ());
            // Oil
            allChanges.addOilConsumption    (mImplemented.get(i).getOil().getConsumption());
            allChanges.addOilSecurity       (mImplemented.get(i).getOil().getSecurity   ());
            allChanges.addOilGrowth         (mImplemented.get(i).getOil().getGrowth     ());
        }
        return allChanges;
    }


    //////////////////// Getters

    /**
     * Gets the implemented technologies
     *
     * @return implemented the implemented technologies
     */
    public ArrayList<Technology> getImplemented()
    {
        return mImplemented;
    }

    /**
     * Gets the available technologies
     *
     * @return available the available technologies
     */
    public ArrayList<Technology> getAvailable()
    {
        return mAvailable;
    }

    /**
     * Gets all technologies
     *
     * @return all all of the technologies
     */
    public ArrayList<Technology> getAll()
    {
        return mAll;
    }

    /**
     * Gets a list of nuclear upgrades
     *
     * @return mNuclear nuclear upgrades
     */
    public ArrayList<Technology> getNuclear()
    {
	return mNuclear;
    }

    /**
     * Gets a list of fossil upgrades
     *
     * @return mFossil fossil upgrades
     */
    public ArrayList<Technology> getFossil()
    {
	return mFossil;
    }

    /**
     * Gets a list of renewable upgrades
     *
     * @return mRenewable renewable upgrades
     */
    public ArrayList<Technology> getRenewable()
    {
	   return mRenewable;
    }

    /**
     * Gets a list of oil upgrades
     *
     * @return mOil oil upgrades
     */
    public ArrayList<Technology> getOil()
    {
	   return mOil;
    }

    //////////////////// Setters

    /**
     * Sets the implemented technologies
     *
     * @param pImplemented the new implemented technologies
     */
    public void setImplemented(ArrayList<Technology> pImplemented)
    {
        mImplemented = pImplemented;
    }

    /**
     * Gets a technology from a name
     *
     * @param techName the name of the tech to get
     * @return tech the technology associated with the name
     */
    public Technology getTechnology(String techName)
    {
	   return mNames.get(techName);
    }

    /**
     * Implements a given technology
     *
     * @param pTech the technology to implement
     */
    public void implementTechnology(Technology pTech)
    {
	   if (!isImplemented(pTech))
	   {
	       mImplemented.add(pTech);
	   }
    }

    /**
     * Returns true if the technology is implemented
     *
     * @param pTech the technology to check
     * @return isTrue whether or not the technology is implemented
     */
    public boolean isImplemented(Technology pTech)
    {
	boolean isTrue = false;
	for (Technology t : mImplemented)
	{
	    if (t == pTech)
	    {
		   isTrue = true;
		   break;
	    }
	}
	return isTrue;
    }

    /**
     * Sets the available technologies
     *
     * @param pAvailable the new available technologies
     */
    public void setAvailable(ArrayList<Technology> pAvailable)
    {
        mAvailable = pAvailable;
	    for (Technology tech : mAvailable)
	    {
	        mNames.put(tech.getName() + tech.getQuality(), tech);
	    }
    }

    /**
     * Adds a Technology
     *
     * @param pTech a Technology
     */
    public void addTechnology(Technology pTech)
    {
        mAvailable.add(pTech);
	mNames.put(pTech.getName() + pTech.getQuality(), pTech);
    }

    /**
     * Adds a technology from a code
     *
     * @param pCode String holding the code for the technology
     */
    public void addTechnology(String pCode)
    {
	Technology newTech = mCodes.getTech(pCode);
	if (newTech != null)
	{
	    mAvailable.add(newTech);
	    mNames.put(newTech.getName() + newTech.getQuality(), newTech);
	}
    }

    /**
     * Sets all technologies
     *
     * @param pAll all of the new technologies
     */
    public void setAll(ArrayList<Technology> pAll)
    {
        mAll = pAll;
    }
}
