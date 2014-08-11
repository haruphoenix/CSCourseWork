package easigreen.desktop;

import easigreen.desktop.*;
import easigreen.service.*;

import java.util.*;

import javafx.collections.ObservableList;
import javafx.collections.FXCollections;
import javafx.scene.control.ListView;

class OilTechList
    extends AppDataList
{

    public OilTechList(SimCity pModel)
    {
        super(pModel);
    }

    protected void update()
    {
	mData.clear();
	for (Technology t : mModel.getUpgradeManager().getTechnologyManager().getOil())
	    {
		mData.add(t.getName());
	    }
    }
}
