package easigreen.service;

import easigreen.system.*;

/**
 * This class contains the default values for an unmodified renewable plant.
 * It will assign these values unless they are passed into the constructor.
 *
 * @version 0.1.1
 * @author Larson Caldwell
 * @author Sam Graham
 * @author Haru McClellan
 */
public class Renewable
    extends Energy
{
    /**
     * Sets default values to a renewable plant
     */
    public Renewable()
    {
        mAmount        = 140;
	mCostBuild     = .2;
        mCostRemove    = -.1;
        mApproval      = 35;
        mProduction    = 0.1;
        mEmissions     = .05;
        mSecurity      = .03;
        mProfitPercent = 20;
    }
}
