package easigreen.service;

import java.util.ArrayList;
import java.lang.Math;

/**
 * This class generates random access code for each technology.
 *
 * @version 0.1.2
 * @author Larson Caldwell
 * @author Sam Graham 
 * @author Haru McClellan
 */
public class CodeGenerator
{
    //////////////////// Variables

    /**
     * the codes to be generated for each tech
     */
    private ArrayList<Integer> mTechnologies;

    /**
     * Codes are generated for each technology
     */
    public void generate(ArrayList<Technology> allTechnology)
    {
        for (int i = 0; i < allTechnology.size(); i++)
        {
            int newCode = (int)(Math.random() * 2000000000);
            mTechnologies.add(newCode);
        }
    }
}