package easigreen.service;

/**
 * The Trade Manager class.
 *
 * @version 0.1.1
 * @author Larson Caldwell
 * @author Sam Graham
 * @author Haru McClellan
 */
public class TradeManager
{
    //////////////////// Variables

    /**
     * The technology manager
     */
    private UpgradeManager mUpgradeManager;

    /**
     * The resource manager
     */
    private ResourceManager mResourceManager;

    /**
     * The Constructor for this class
     *
     * @param pUpgradeManager the upgrade manager
     * @param pResourceManager   the resource manager
     */
    public TradeManager(ResourceManager pResourceManager, 
                        UpgradeManager pUpgradeManager)
    {
        mUpgradeManager = pUpgradeManager;
        mResourceManager   = pResourceManager;
    }
}
