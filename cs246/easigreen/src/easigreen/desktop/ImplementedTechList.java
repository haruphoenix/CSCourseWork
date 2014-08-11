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
class ImplementedTechList
    extends AppDataList
{
    ///////////////////////////// Constructor

    /**
     * Basic Constructor
     * @param pModel the model, a SimCity
     */
    public ImplementedTechList(SimCity pModel)
    {
        super(pModel);
    }

    ///////////////////////////// Method
    
    /**
     * Update the Technology List
     */
    protected void update()
    {
	   mData.clear();
	   for (Technology t : mModel.getUpgradeManager().getTechnologyManager().getImplemented())
	   {
	       mData.add(t.getName() + t.getQuality());
	   }
    }
}
