package easigreen.service;

import easigreen.system.*;
import java.io.*;
import java.util.ArrayList;

/**
 * Gets  a list of all the Technologies
 *
 * @author Sam Graham
 */
public class TechnologyGetter
{
    
    /**
     * The path prefix for the technology resource.
     */
    public static final String cTechFilename 
        = "/resources/data/Technologies.csv";

    /**
     * Encapsulates getting the technologies from a resource file.
     */
    public ArrayList<Technology> getTechnologies()
    {
        ArrayList<Technology> tech = new ArrayList<Technology>();
		
	String line;
		
	try
	{
	    BufferedReader br = new BufferedReader(new InputStreamReader(
                ResourceGetter.getResourceAsStream(cTechFilename)));

	    while ((line = br.readLine()) != null)
	    {
		String[] strArr = line.split(",");
		double[] dblArr = new double[25];
		Technology newTech = new Technology();
		for (int i = 1; i < 25; i++)
		{
		    try
		    {
			if (strArr[i] != "")
			{
                            dblArr[i] = Double.parseDouble(strArr[i]);
		        }
		    }
		    catch (Exception e)
		    {
		    }
		}

		if (strArr[0]  != "")
	        { 
                    newTech.setName(strArr[0]);
		}

		if (strArr[1]  != "")
	        { 
                    newTech.getOther().setDemand(dblArr[1]);
		}
 
		if (strArr[2]  != "")
	        { 
                    newTech.getOther().setBudget(dblArr[2]);
		}

		if (strArr[3]  != "")
	        { 
                    newTech.getOther().setEmissions(dblArr[3]);
		}

		if (strArr[4]  != "")
	        { 
                    newTech.getNuclear().setPower(dblArr[4]);
		}

		if (strArr[5]  != "") 
	        {
                    newTech.getNuclear().setCost(dblArr[5]);
		}

		if (strArr[6]  != "")
	        { 
                    newTech.getNuclear().setApproval(dblArr[6]);
		}

		if (strArr[7]  != "") 
	        {
                    newTech.getNuclear().setEmissions(dblArr[7]);
		}

		if (strArr[8]  != "") 
	        {
                    newTech.getNuclear().setSecurity(dblArr[8]);
		}

		if (strArr[9]  != "") 
	        {
                    newTech.getNuclear().setProfit(dblArr[9]);
		}

		if (strArr[10] != "") 
	        {
                    newTech.getFossil().setPower(dblArr[10]);
	        }

		if (strArr[11] != "") 
	        {
                    newTech.getFossil().setCost(dblArr[11]);
		}

		if (strArr[12] != "") 
	        {
                    newTech.getFossil().setApproval(dblArr[12]);
		}

		if (strArr[13] != "") 
	        {
                    newTech.getFossil().setEmissions(dblArr[13]);
		}

		if (strArr[14] != "") 
	        {
                    newTech.getFossil().setSecurity(dblArr[14]);
		}

		if (strArr[15] != "") 
	        {
                    newTech.getFossil().setProfit(dblArr[15]);
		}

		if (strArr[16] != "") 
	        {
                    newTech.getRenewable().setPower(dblArr[16]);
		}

		if (strArr[17] != "") 
	        {
                    newTech.getRenewable().setCost(dblArr[17]);
		}
		
		if (strArr[18] != "") 
	        {
                    newTech.getRenewable().setApproval(dblArr[18]);
		}

		if (strArr[19] != "") 
	        {
                    newTech.getRenewable().setEmissions(dblArr[19]);
		}

		if (strArr[20] != "") 
	        {
                    newTech.getRenewable().setSecurity(dblArr[20]);
		}

		if (strArr[21] != "") 
	        {
                    newTech.getRenewable().setProfit(dblArr[21]);
		}
		
		if (strArr[22] != "") 
	        {
                    newTech.getOil().setConsumption(dblArr[22]);
		}

		if (strArr[23] != "") 
	        {
                    newTech.getOil().setSecurity(dblArr[23]);
		}

		if (strArr[24] != "") 
	        {
                    newTech.getOil().setGrowth(dblArr[24]);
		}

		tech.add(newTech);
	    }
	}
	catch (Exception e)
	{
	    e.printStackTrace();
	}
		
        return tech;
    }
}
