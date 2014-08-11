package easigreen.service;

import easigreen.system.*;

/**
 * This class contains the default values for an unmodified fossil plant.  It
 * will assign these values unless they are passed into the constructor.
 *
 * @version 0.1.1
 * @author Larson Caldwell
 * @author Sam Graham
 * @author Haru McClellan
 */
public class Fossil
    extends Energy
{
    /**
     * Sets default values to a fossil plant.
     */
    public Fossil()
    {
        mAmount        = 100;
	mCostBuild     = 1;
        mCostRemove    = .1;
        mApproval      = 50;
        mProduction    = .65;
        mEmissions     = 2;
        mSecurity      = .09;
        mProfitPercent = 45;
    }
}
