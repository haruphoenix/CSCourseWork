package easigreen.service;

import easigreen.system.*;

/**
 * This class contains the default values for an unmodified nuclear plant.  It
 * will assign these values unless they are passed into the constructor.
 *
 * @version 0.1.1
 * @author Larson Caldwell
 * @author Sam Graham
 * @author Haru McClellan
 */
public class Nuclear
    extends Energy
{
    /**
     * Sets default values to a nuclear plant
     */
    public Nuclear()
    {
        mAmount        = 18;
	mCostBuild     = 2.5;
	mCostRemove    = .5;
	mApproval      = 35;
	mProduction    = 1;
	mEmissions     = 0;
	mSecurity      = 0;
	mProfitPercent = 50;
    }
}
