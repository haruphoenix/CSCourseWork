/**
 * Exploration 5, Boldness
 * Instructor: Brother Neff
 * Author: Haru McClellan
 * Note: Many of the runnables associated with this application only work on Windows OS.
 * Collaborators: Larson Caldwell
 */
import java.util.ArrayList;
import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.HPos;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.SelectionMode;
import javafx.scene.control.TextField;
import javafx.scene.layout.ColumnConstraints;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.RowConstraints;
import javafx.scene.Node;

/**
 * This application class dynamically loads runnable classes and runs them
 * in their own thread.
 */
public class ThreadsOfGlory extends Application
{
    
    /**
     * Singleton instance of this class
     */
    private static ThreadsOfGlory instance;

    /**
     * Used to create rows and columns in a grid layout
     */
    private static final int[] COLUMNS = new int[]{3, 3, 25, 3, 11, 11, 41, 3, 0};
    private static final int[] ROWS    = new int[]{3, 7,  6, 5,  3, 62,  3, 8, 3};

    /**
     * Lists of runnables and running threads.
     */
    private static final ObservableList<String> RUNNABLES = FXCollections.observableArrayList();
    private static final ObservableList<String> RUNNING   = FXCollections.observableArrayList();

    /**
     * The main scene and its layout
     */
    private static GridPane mGrid;
    private static Scene mScene;

    /**
     * Application Nodes
     */
    private static Label textLabel;
    private static Label runnableLabel;
    private static Label runningLabel;
    private static TextField textField;
    private static ListView<String> runnableList;
    private static ArrayList<Runnable> runnables;
    private static ListView<String> runningList;
    private static Button startButton;
    private static Button stopButton;


    /**
     * Position of Nodes on grid. First two represent coordinate, second two
     * represent dimension.
     */
    private int[][] position = new int[][]{{2, 1, 1, 1},  // textLabel
					   {4, 1, 3, 1},  // textField
					   {1, 3, 4, 1},  // runnableLabel
					   {1, 5, 4, 1},  // runnableList
					   {6, 3, 1, 1},  // runningLabel
					   {6, 5, 1, 1},  // runningList
					   {1, 7, 4, 1},  // startButton
					   {6, 7, 1, 1}}; // stopButton

    /**
     * Used to tell if this application has been closed, and all threads
     * should end.
     */
    private static boolean isOff = false;

    /**
     * Constructor forces singleton behavior. Use getInstance()
     */
    public ThreadsOfGlory()
    {
	super();
	synchronized(ThreadsOfGlory.class)
	{
	    if (instance != null)
	    {
		throw new UnsupportedOperationException(
			  getClass() + " is singleton but constructor called more than once");
	    }

	    instance = this;
	}
    }

    /**
     * Main method invokes Threads of Glory Application
     */
    public static void main(String[] args)
    {
        launch(args);
    }

    /**
     * @return ThreadsOfGlory - singleton instance
     */
    public static ThreadsOfGlory getInstance()
    {
	if (instance == null)
	{
	    instance = new ThreadsOfGlory();
	}
	return instance;
    }

    /**
     * @return Scene - The main scene
     */
    public Scene getScene()
    {
	return mScene;
    }

    /**
     * @param Stage - primary Stage
     * initializes and starts application
     */
    public void start(final Stage primaryStage)
    {

	setLabels();
	setTextField();
	setRunnableList();
	setRunningList();
	setStartButton();
	setStopButton();
	setGrid();
	addComponents();

	mScene = new Scene(mGrid, 420, 350);

	primaryStage.setTitle("Threads of Glory");
        primaryStage.setScene(mScene);
        primaryStage.show();

	setClose();
    }

    /**
     * Changes close-window operation to change static variable isOff to true
     * thus allowing all invoked threads to end their run methods.
     */
    public void setClose()
    {
	mScene.getWindow().setOnCloseRequest(new EventHandler<WindowEvent>()
	{
	    public void handle(WindowEvent event)
	    {
		isOff = true;
		System.exit(0);
	    }
	});
    }

    /**
     * Initializes Labels
     */
    private void setLabels()
    {
	textLabel     = new Label("Enter Runnable:");
	runnableLabel = new Label("Runnables");
	runningLabel  = new Label("Running Threads");
    }

    /**
     * Initializes Text Field and implements action handler to add
     * legitamate runnables to the runnable list
     */
    private void setTextField()
    {
	textField = new TextField();
	textField.setPrefSize(300, 25);
	textField.setOnAction(new EventHandler<ActionEvent>()
	{
	    public void handle(ActionEvent event)
	    {
		String runnableName = textField.getText();
		try
		{
		    if (RUNNABLES.indexOf(runnableName) != -1)
		    {
			textField.setText("");
			throw new Exception("List already contains runnable");
		    }
		    Class runnable = Class.forName(runnableName);
		    Runnable item  = (Runnable)runnable.newInstance();
		    runnables.add(item);
		    RUNNABLES.add(runnableName);
		    runnableList.setItems(RUNNABLES);
		    textField.setText("");
		    runnableList.getSelectionModel().select(runnables.size() - 1);
		}
		catch (Exception e)
		{
		    textField.setText(e.toString());
		}
	    }
	});
    }

    /**
     * Initializes Runnable List
     */
    private void setRunnableList()
    {
	runnables = new ArrayList<Runnable>();
	runnableList = new ListView<String>(RUNNABLES);
	runnableList.setPrefSize(200, 250);
    }

    /**
     * Initializes Running List
     */
    private void setRunningList()
    {
	runningList = new ListView<String>(RUNNING);
	runningList.setPrefSize(200, 250);
	runningList.getSelectionModel().setSelectionMode(SelectionMode.MULTIPLE);
    }

    /**
     * Initializes Start Button and implements action Handler to start the
     * selected runnable and add it to the running list
     */
    private void setStartButton()
    {
	startButton = new Button();
	startButton.setPrefSize(100, 40);
	startButton.setText("Start");
	startButton.setOnAction(new EventHandler<ActionEvent>()
	{
	    public void handle(ActionEvent event)
	    {
		try
		{
		    int index = runnableList.getSelectionModel().getSelectedIndex();
		    Thread thread = new Thread(runnables.get(index));
		    thread.start();
		    RUNNING.add(RUNNABLES.get(index) + thread.getName());
		}
		catch (Exception e)
		{
		}
	    }
	});
    }

    /**
     * Initializes Stop Button and implements action handler to remove the
     * selected running thread from the running list, allowing the runnable
     * to finish its run method.
     */
    private void setStopButton()
    {
	stopButton = new Button();
	stopButton.setPrefSize(100, 40);
	stopButton.setText("Stop");
	stopButton.setOnAction(new EventHandler<ActionEvent>()
	{
	    public void handle(ActionEvent event)
	    {
		try
		{
		    int index = runningList.getSelectionModel().getSelectedIndex();
		    RUNNING.remove(index);
		}
		catch (Exception e)
		{
		}
	    }
	});

    }

    /**
     * Creates rows and columns for the grid layout
     */
    private void setGrid()
    {
	mGrid = new GridPane();
 
	for (int i = 0; i < COLUMNS.length; i++)
	{
	    RowConstraints    row    = new RowConstraints();
	    ColumnConstraints column = new ColumnConstraints();
	    row.setPercentHeight  (ROWS[i]);
	    column.setPercentWidth(COLUMNS[i]);
	    mGrid.getRowConstraints   ().add(row);
	    mGrid.getColumnConstraints().add(column);
        }
    }

    /**
     * Adds all of the different components to the grid
     */
    private void addComponents()
    {
	Node[] components = {textLabel, textField, runnableLabel, runnableList, 
			     runningLabel, runningList, startButton, stopButton};

	for (int i = 0; i < components.length; i++)
	{
	    mGrid.setHalignment(components[i], HPos.CENTER);
	    mGrid.add(components[i], position[i][0], position[i][1], position[i][2], position[i][3]);
	}
    }

    /**
     * Used to find out if a certain thread should still be running or not.
     * @param String - The name of the runnable
     * @return boolean - true if the runnable should still be running
     */
    public static boolean isRunning(String runnable)
    {
	if ((RUNNING.indexOf(runnable + Thread.currentThread().getName()) != -1) && !isOff)
	{
	    return true;
	}
	else
	{
	    return false;
	}
    }
}
