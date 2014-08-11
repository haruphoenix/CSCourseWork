package easigreen.service;

import easigreen.service.*;
import easigreen.system.*;

/**
 * A class for creating a clone of a technology
 *
 * @version 0.1.1
 * @author Larson Caldwell
 * @author Sam Graham
 * @author Haru McClellan
 */
class TechCloner
{
    /**
     * Clones a technology using all of the information stored inside
     *
     * @param pTech the technology being cloned
     * @return clone the copy of the technology inputed
     */
    public static Technology getClone(Technology pTech)
    {
	Technology  clone = new Technology();

	PlantAspect nucA = pTech.getNuclear() ;
	PlantAspect nucB = clone.getNuclear() ;
	nucB.setPower    (nucA.getPower    ());
	nucB.setCost     (nucA.getCost     ());
	nucB.setApproval (nucA.getApproval ());
	nucB.setEmissions(nucA.getEmissions());
	nucB.setSecurity (nucA.getSecurity ());
	nucB.setProfit   (nucA.getProfit   ());

	PlantAspect fosA = pTech.getFossil () ;
	PlantAspect fosB = clone.getFossil () ;
	fosB.setPower    (fosA.getPower    ());
	fosB.setCost     (fosA.getCost     ());
	fosB.setApproval (fosA.getApproval ());
	fosB.setEmissions(fosA.getEmissions());
	fosB.setSecurity (fosA.getSecurity ());
	fosB.setProfit   (fosA.getProfit   ());

	PlantAspect renA = pTech.getRenewable() ;
	PlantAspect renB = clone.getRenewable() ;
	renB.setPower    (renA.getPower      ());
	renB.setCost     (renA.getCost       ());
	renB.setApproval (renA.getApproval   ());
	renB.setEmissions(renA.getEmissions  ());
	renB.setSecurity (renA.getSecurity   ());
	renB.setProfit   (renA.getProfit     ());

	OilAspect oilA = pTech.getOil();
	OilAspect oilB = clone.getOil();
	oilB.setConsumption(oilA.getConsumption());
	oilB.setSecurity   (oilA.getSecurity   ());
	oilB.setGrowth     (oilA.getGrowth     ());

	OtherAspect othA = pTech.getOther();
	OtherAspect othB = clone.getOther();
	othB.setBudget   (othA.getBudget   ());
	othB.setDemand   (othA.getDemand   ());
	othB.setEmissions(othA.getEmissions());

	return clone;
    }
}
