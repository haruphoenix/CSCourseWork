package easigreen.service;

import easigreen.system.*;
import java.util.ArrayList;

/**
 * The Sim city is the main class of the application.  It uses the user
 * interface to communicate with the user, uses the simulator to process the
 * data, and uses the CSV getter to create and access files containing saved
 * changes.
 *
 *
 * @version 0.1.1
 * @author Larson Caldwell
 * @author Sam Graham
 * @author Haru McClellan
 */
public class SimCity
{
    //////////////////// Variables

    /**
     * The base values
     */
    private BaseManager mBaseManager;

    /**
     * Manager for the energy
     */
    private EnergyManager mEnergyManager;

    /**
     * Manager for the upgrades.
     */
    private UpgradeManager mUpgradeManager;

    /**
     * Manager for the goals
     */
    private GoalManager mGoalManager;

    /**
     * Manager for the world
     */
    private WorldManager mWorldManager;

    /**
     * Manager for the resources
     */
    private ResourceManager mResourceManager;

    /**
     * Manager for the trades
     */
    private TradeManager mTradeManager;

    //////////////////// Methods

    /**
     * This method will run the program.  It will listen to the user and call
     * algorithms in the simulators.
     */
    public void run()
    {
	mBaseManager     = new BaseManager    ();
	mUpgradeManager  = new UpgradeManager ();
	mResourceManager = new ResourceManager(mBaseManager, mUpgradeManager);
        mEnergyManager   = new EnergyManager  (mUpgradeManager);
        mGoalManager     = new GoalManager    (mResourceManager, 
                                               mUpgradeManager, 
                                               mEnergyManager);
        mWorldManager    = new WorldManager   ();
        mTradeManager    = new TradeManager   (mResourceManager, 
                                               mUpgradeManager);
    }

    
    /**
     * Main starts the run method
     *
     * @param args the command line arguments
     */
    public static void main(String[] args)
    {
        new SimCity().run();
    }

    ////////////////////////////////// Getters
    
    /**
     * Gets the current round
     *
     * @return the round number
     */
    public BaseManager getBaseManager()
    {
        return mBaseManager;
    }
    
    /**
     * Gets the EnergyManager
     *
     * @return the EnergyManager
     */
    public EnergyManager getEnergyManager()
    {
        return mEnergyManager;
    }
    
    /**
     * Gets the UpgradeManager
     *
     * @return the UpgradeManager
     */
    public UpgradeManager getUpgradeManager()
    {
        return mUpgradeManager;
    }
    
    /**
     * Gets the GoalManager
     *
     * @return the GoalManager
     */
    public GoalManager getGoalManager()
    {
        return mGoalManager;
    }
    
    /**
     * Gets the WorldManager
     *
     * @return the WorldManager
     */
    public WorldManager getWorldManager()
    {
        return mWorldManager;
    }
    
    /**
     * Gets the ResourceManager
     *
     * @return the ResourceManager
     */
    public ResourceManager getResourceManager()
    {
        return mResourceManager;
    }
    
    /**
     * Gets the TradeManager
     *
     * @return the TradeManager
     */
    public TradeManager getTradeManager()
    {
        return mTradeManager;
    }

    //////////////////////////// Setters
    
    /**
     * Sets the RoundNumber
     *
     * @param pRoundNumber the round number
     */
    public void setBaseManager(BaseManager pBaseManager)
    {
        mBaseManager = pBaseManager;
    }
    
    /**
     * Sets the EnergyManager 
     *
     * @param pEnergyManager
     */
    public void setEnergyManager(EnergyManager pEnergyManager)
    {
        mEnergyManager = pEnergyManager;
    }
    
    /**
     * Sets the upgrade manager
     *
     * @param pUpgradeManager
     */
    public void setUpgradeManager(UpgradeManager pUpgradeManager)
    {
        mUpgradeManager = pUpgradeManager;
    }
    
    /**
     * Sets the goal manager
     *
     * @param pGoalManager
     */
    public void setGoalManager(GoalManager pGoalManager)
    {
        mGoalManager = pGoalManager;
    }
    
    /**
     * Sets the world manager
     *
     * @param pWorldManager
     */
    public void setWorldManager(WorldManager pWorldManager)
    {
        mWorldManager = pWorldManager;
    }
    
    /**
     * Sets the resource manager
     *
     * @param pResourceManager
     */
    public void setResourceManager(ResourceManager pResourceManager)
    {
        mResourceManager = pResourceManager;
    }
    
    /**
     * Sets the trade manager
     *
     * @param pTradeManager
     */
    public void setTradeManager(TradeManager pTradeManager)
    {
        mTradeManager = pTradeManager;
    }
}
