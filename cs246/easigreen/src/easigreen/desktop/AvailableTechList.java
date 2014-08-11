package easigreen.desktop;

import easigreen.desktop.*;
import easigreen.service.*;

import java.util.*;

import javafx.collections.ObservableList;
import javafx.collections.FXCollections;
import javafx.scene.control.ListView;

/**
 * List holder of technologies
 *
 * @version 0.2.1
 * @author Sam Graham
 * @author Haru McClellan
 * @author Larson Caldwell
 */ 
class AvailableTechList
    extends AppDataList
{
    ///////////////////////////// Constructor

    /**
     * Basic Constructor
     * @param pModel the model, a SimCity
     */
    public AvailableTechList(SimCity pModel)
    {
        super(pModel);
    }

    //////////////////////////// Methods
    
    /**
     * Update the Technology List
     */
    protected void update()
    {
	   mData.clear();
	   for (Technology t : mModel.getUpgradeManager().getTechnologyManager().getAvailable())
	   {
	       mData.add(t.getName() + t.getQuality());
	   }
    }
}
