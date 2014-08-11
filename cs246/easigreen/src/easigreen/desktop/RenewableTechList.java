package easigreen.desktop;

import easigreen.desktop.*;
import easigreen.service.*;

import java.util.*;

import javafx.collections.ObservableList;
import javafx.collections.FXCollections;
import javafx.scene.control.ListView;

/**
 * Technology List for Renewable Technologies
 * @version 0.2.0
 * @author Haru McClellan
 */
class RenewableTechList
    extends AppDataList
{
    /**
     * Basic Constructor
     * @param pModel a reference to SimCity
     */
    public RenewableTechList(SimCity pModel)
    {
	   super(pModel);
    }

    /**
     * Updater
     */
    protected void update()
    {
	mData.clear();
	for (Technology t : mModel.getUpgradeManager().getTechnologyManager().getRenewable())
	    {
		mData.add(t.getName());
	    }
    }
}
