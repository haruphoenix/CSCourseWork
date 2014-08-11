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
 * A Panel for the center data region of the GUI interface
 * @version 0.1.0
 * @author Haru McClellan
 */
public class ContentPane
    extends GridPane
{

    /**
     * Format for displaying numbers
     */
    protected static final String FORMAT = "%.2f";

    /**
     * Holds a reference to the model
     */
    protected SimCity mModel;

    /**
     * Retrieves a list of columns
     * @return integer array of columns
     */
    protected int[] getColumns()
    {
        return new int[] {12, 76, 12};
    }

    /**
     * Retrieves a list of rows
     * @return integer array of rows
     */
    protected int[] getRows()
    {
        return new int[] {16, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 32};
    }

    /**
     * Constructor
     * @param SimCity pModel the current sim city Model
     */
    public ContentPane(SimCity pModel)
    {
        mModel = pModel;
        setPrefSize(0, 0);
        init();
        setGrid();
        setup();
    }

    /**
     * Set up needs to be implemented by child
     */
    protected void setup()
    {
    }

    /**
     * Retrieves the title
     * @return the title, a String
     */
    protected String getTitle()
    {
        return "Unknown";
    }

    /**
     * Retrieves the Title Label
     * @return a Label
     */
    protected Label getTitleLabel()
    {
        Label title = new Label(getTitle());
        title.setFont(new Font("Arial", 40));
        setHalignment(title, HPos.CENTER);
        return title;
    }

    /**
     * Initializer
     */
    protected void init()
    {
    }

    /**
     * Updater
     */
    protected void update()
    {
    }

    /**
     * Sets the grid
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
