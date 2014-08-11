package easigreen.desktop;

import easigreen.desktop.*;
import easigreen.service.*;
import easigreen.system.*;

import java.lang.reflect.*;
import java.util.*;
import java.util.prefs.*;

import javafx.application.*;
import javafx.event.*;
import javafx.geometry.*;
import javafx.scene.*;
import javafx.scene.control.*;
import javafx.scene.image.*;
import javafx.scene.layout.*;
import javafx.stage.*;

/**
 * The main Graphical User Interface for the "Sim City" Application
 */
public class GUI
    extends Application
{
    /**
      * Holds the singleton instance.
      */
    private static GUI cInstance = null;

    /**
     * Gets the singleton instance.
     *
     * @return the singleton instance.
     */
    public static GUI getInstance()
    {
        return cInstance;
    }

    /**
     * Holds Game Name
     */
    private static final String GAME_NAME = "Sargeant City";

    /**
     * Holds Navigation Names
     */
    private static final String[]   mainNavNames = new String[] {"country", "energy", "upgrades", "goals"};

    /**
     * Holds The Sub Classes of the main navigation panes
     */
    private static final String[][] subNavNames  = new String[][] {{"world", "politicalresources", "trade"},
        {"nuclear", "fossilfuel", "renewable", "oil"},
        {"science", "engineering", "policies", "technologies1"},
        {"shortterm", "longterm"}
    };

    /**
     * Holds Class Names
     */
    private static final String[]   mainClassNames = new String[] {"CountryPane", "EnergyPane", "UpgradesPane", "GoalsPane"};

    /**
     * Holds Holds Sub Class names
     */
    private static final String[][] subClassNames  = new String[][] {{"WorldPane", "PoliticalPane", "TradePane"},
        {"NuclearPane", "FossilPane", "RenewablePane", "OilPane"},
        {
            "SciencePane", "EngineeringPane",
            "PoliciesPane", "TechnologiesPane"
        },
        {"ShortTermPane", "LongTermPane"}
    };

    /**
     * Holds the model
     */
    private SimCity mModel;

    /**
     * Contains Graphical buttons for the main navigation of the system.
     */
    private NavPane mainNavigation;

    /**
     * A map of Strings to navigation panes
     */
    private static Map<String, NavPane> subNavigation;

    /**
     * A Map of string (button names) to the events they handle
     */
    private static Map<String, EventHandler<ActionEvent>> events;

    /**
     * Maps strings to the content page it provides
     */
    private static Map<String, ContentPane> mContent;

    /**
     * The Primary Stage for this application
     */
    private Stage mPrimaryStage;

    /**
     * Contains the primary layout for the application.
     */
    private BorderPane windowArea;

    /**
     * Creates a new GUI object.
     */
    public GUI()
    {
        super();

        synchronized (GUI.class) {
            if (cInstance != null) {
                throw new UnsupportedOperationException(getClass() +
                                                        " is singleton but constructor called more than once.");
            }

            cInstance = this;
        }
    }

    /**
     * Allows access to the main window area
     */
    public BorderPane getWindow()
    {
        return windowArea;
    }

    /**
     * Starts the GUI.
     *
     * @param primaryStage the primary stage.
     */
    @Override
    public void start(Stage primaryStage)
    {
        mPrimaryStage = primaryStage;
        setLocation();
        initialize();
        mPrimaryStage.show();
    }

    /**
     * Exits the application.
     */
    public void exit()
    {
        saveLocation();
        Action.showAll();
        Platform.exit();
        System.exit(0);
    }

    /**
     * Initializes the GUI.
     *
     * @param primaryStage the primary stage.
     */
    private void initialize()
    {
        initializeModel();
        initializeEvents();
        initializeNavigation();
        initializeContent();
        initializeWindow();
        initializeStage();
    }

    /**
     * Initializes the model
     */
    private void initializeModel()
    {
        mModel = new SimCity();
	mModel.run();
    }

    /**
     * Initializes action events for buttons
     */
    private void initializeEvents()
    {
        events = new HashMap<String, EventHandler<ActionEvent>>();
        // Initialize Main Menu Events
        for (final String nav : mainNavNames) {
            events.put(nav, new EventHandler<ActionEvent>() {
                public void handle(ActionEvent event) {
                    windowArea.setRight(subNavigation.get(nav));
                    mContent.get(nav).update();
                    windowArea.setCenter(mContent.get(nav));
                }
            });
        }
        // Initialize Sub Menu Events
        for (int navNumber = 0; navNumber < mainNavNames.length; navNumber++) {
            for (final String subNavName : subNavNames[navNumber]) {
                events.put(subNavName, new EventHandler<ActionEvent>() {
                    public void handle(ActionEvent event) {
                        mContent.get(subNavName).update();
                        windowArea.setCenter(mContent.get(subNavName));
                    }
                });
            }
        }
    }

    /**
     * Initialize Primary Navigation
     */
    private void initializeNavigation()
    {
        mainNavigation = new NavPane();
        subNavigation  = new HashMap<String, NavPane>();
        for (int mainNavNum = 0; mainNavNum < mainNavNames.length; mainNavNum++) {
            mainNavigation.addButton(mainNavNames[mainNavNum], events.get(mainNavNames[mainNavNum]));
            NavPane newNav = new NavPane();
            for (int subNavNum = 0; subNavNum < subNavNames[mainNavNum].length; subNavNum++) {
                newNav.addButton(subNavNames[mainNavNum][subNavNum], events.get(subNavNames[mainNavNum][subNavNum]));
            }
            newNav.initialize();
            subNavigation.put(mainNavNames[mainNavNum], newNav);
        }
        mainNavigation.initialize();
    }

    /**
     * Initializes Content
     */
    private void initializeContent()
    {
        mContent = new HashMap<String, ContentPane>();
        String currentClass = "";
        try {
            for (int navNumber = 0; navNumber < mainNavNames.length; navNumber++) {
                String packagePrefix = getClass().getName();
                int lastDotIndex = packagePrefix.lastIndexOf('.');
                packagePrefix = packagePrefix.substring(0, lastDotIndex + 1);
                currentClass = packagePrefix + mainClassNames[navNumber];
                Constructor mainConstruct = Class.forName(currentClass).getConstructor(SimCity.class);
                mContent.put(mainNavNames[navNumber], (ContentPane) mainConstruct.newInstance(mModel));
                for (int subNavNum = 0; subNavNum < subNavNames[navNumber].length; subNavNum++) {
                    currentClass = packagePrefix + subClassNames[navNumber][subNavNum];
                    Constructor subConstruct = Class.forName(currentClass).getConstructor(SimCity.class);
                    mContent.put(subNavNames[navNumber][subNavNum], (ContentPane) subConstruct.newInstance(mModel));
                }
            }
        } catch (ClassNotFoundException e) {
            System.out.println("Fatal Error: " + currentClass + " class not found");
            exit();
        } catch (InstantiationException e) {
            System.out.println("Fatal Error: Could not instantiate " + currentClass);
            exit();
        } catch (NoSuchMethodException e) {
            System.out.println("Fatal Error: Constructor for " + currentClass + "Not Found");
            exit();
        } catch (IllegalAccessException e) {
            System.out.println("Fatal Error: Cannot access " + currentClass);
            exit();
        } catch (InvocationTargetException e) {
            System.out.println("Fatal Error: Invocation Target Exception");
            System.out.println(e.getCause() + " caused by " + currentClass);
            exit();
        } catch (Exception e) {
            System.out.println("Error Initializing " + currentClass);
            e.printStackTrace();
        }
    }

    /**
     * Initializes Main Window Layout
     */
    private void initializeWindow()
    {
        windowArea = new BorderPane();
        windowArea.setLeft(mainNavigation);
        windowArea.setRight(subNavigation.get(mainNavNames[0]));
        windowArea.setCenter(mContent.get(mainNavNames[0]));
    }

    /**
     * Initializes the Primary Stage
     *
     */
    private void initializeStage()
    {
        mPrimaryStage.setScene(new Scene(windowArea));
        mPrimaryStage.setMinHeight(600);
        mPrimaryStage.setMinWidth(750);
        mPrimaryStage.setTitle(GAME_NAME);
        setCloseOperation();
    }

    /**
     * Sets the exit button to use exit method to exit
     */
    private void setCloseOperation()
    {
        mPrimaryStage.setOnCloseRequest(new EventHandler<WindowEvent>() {
            public void handle(WindowEvent event) {
                exit();
            }
        });
    }

    /**
     * Sets the location of the window
     */
    private void setLocation()
    {
        Preferences prefs = Preferences.userNodeForPackage(GUI.class);
        mPrimaryStage.setX(prefs.getDouble("locationX", 100.0));
        mPrimaryStage.setY(prefs.getDouble("locationY", 100.0));
    }

    /**
    * Saves the location of the GUI as a user preference.
    */
    private void saveLocation()
    {
        Preferences prefs = Preferences.userNodeForPackage(GUI.class);
        prefs.putDouble("locationX", mPrimaryStage.getX());
        prefs.putDouble("locationY", mPrimaryStage.getY());
    }
}
