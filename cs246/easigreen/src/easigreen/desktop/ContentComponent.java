package easigreen.desktop;

import easigreen.service.*;

import java.util.*;

import javafx.scene.control.*;
import javafx.scene.layout.*;

import javafx.event.*;
import javafx.geometry.*;
import javafx.scene.*;
import javafx.scene.image.*;
import javafx.scene.text.*;

/**
 * Component extension for Easigreen
 *
 * @version 0.2.1
 * @author Sam Graham
 * @author Haru McClellan
 * @author Larson Caldwell
 */ 
public class ContentComponent
    extends GridPane
{
    /////////////////////////////// Variables

    /**
     * Holds a reference to the model
     */
    protected SimCity mModel;

    /////////////////////////////// Method
    
    /**
     * Initializer
     */
    protected void init()
    {
    }
    
    /**
     * Setup of the variables
     */
    protected void setup()
    {
    }

    /**
     * Updates the various components
     */
    protected void update()
    {
    }

    ////////////////////////////// Getters
    
    /**
     * Returns a list of columns
     * @return integer array of columns
     */
    protected int[] getColumns()
    {
        return new int[] {};
    }

    /**
     * Returns a list of rows
     * @return integer array of rows
     */
    protected int[] getRows()
    {
        return new int[] {};
    }
    
    ///////////////////////////////// Constructor
    
    /**
     * Constructor
     * @param pModel the current SimCity Model
     */
    public ContentComponent(SimCity pModel)
    {
        mModel = pModel;
        setGrid();
        init();
        setup();
    }

    /////////////////////////////// Setters
    
    /**
     * Sets up the grid
     */
    protected void setGrid()
    {
        int[] columns = getColumns();
        for (int i = 0; i < columns.length; i++) {
            ColumnConstraints column = new ColumnConstraints();
            column.setPercentWidth(columns[i]);
            getColumnConstraints().add(column);
        }
        int[] rows = getRows();
        for (int i = 0; i < rows.length; i++) {
            RowConstraints row = new RowConstraints();
            row.setPercentHeight(rows[i]);
            getRowConstraints().add(row);
        }
    }
}
