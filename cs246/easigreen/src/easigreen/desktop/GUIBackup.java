package easigreen.desktop;

import easigreen.service.*;

import easigreen.system.*;

import java.util.*;

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
 *
 * @version 0.2.3
 * @author Larson Caldwell
 * @author Sam Graham
 * @author Haru McClellan
 */
public class GUIBackup
    extends Application
{
    ///////////////////////////// Constants
   
    /**
     * The Name of the Game
     */
    private static final String GAME_NAME = "Sargeant City";

    ///////////////////////////// Methods
    
    /**
     * Holds the singleton instance.
     */
    private static GUIBackup cInstance = null;

    /**
     * Gets the singleton instance.
     *
     * @return the singleton instance.
     */
    public static GUIBackup getInstance()
    {
        return cInstance;
    }

    /**
     * A Map of string (button names) to the events they handle
     */
    private static Map<String, EventHandler<ActionEvent>> events;

    /**
     * Contains the primary layout for the application.
     */
    private BorderPane windowArea;

    /**
     * Contains Graphical buttons for the main navigation of the system.
     */
    private NavPane mainNavigation;

    /**
    * Contains Graphical buttons for navigating within the country tab.
    */
    private NavPane countryNavigation;

    /**
    * Contains Graphical buttons for navigating within the energy tab.
    */
    private NavPane energyNavigation;

    /**
    * Contains Graphical buttons for navigating within the upgrade tab.
    */
    private NavPane upgradeNavigation;

    /**
    * Contains Graphical buttons for navigating within the goal tab.
    */
    private NavPane goalNavigation;

    ///////////////////////////// Constructor
    
    /**
     * Constructor
     * Creates a new GUI object.
     */
    public GUIBackup()
    {
        super();

        synchronized (GUIBackup.class) {
            if (cInstance != null) {
                throw new UnsupportedOperationException(getClass() +
                                                        " is singleton but constructor called more than once.");
            }

            cInstance = this;
        }
    }

    ///////////////////////////// Methods
    
    /**
     * Initializes the GUI.
     *
     * @param primaryStage the primary stage.
     */
    private void init(Stage primaryStage)
    {
        initEvents();
        initNav();
        initWindow();
        initStage(primaryStage);
    }

    /**
     * Starts the GUI.
     *
     * @param primaryStage the primary stage.
     */
    @Override
    public void start(Stage primaryStage)
    {
        init(primaryStage);
        primaryStage.show();
    }

    /**
     * Exits the application.
     */
    public void exit()
    {
        Action.showAll();
        Platform.exit();
        System.exit(0);
    }

    /**
     * Initializes action events for buttons
     */
    private void initEvents()
    {
        events = new HashMap<String, EventHandler<ActionEvent>>();
        initMainNavEvent();
        initEnergyNavEvent();
        initCountryNavEvent();
        initUpgradeNavEvent();
        initGoalNavEvent();
    }

    /**
     * Initializes action events for Main Navigation Buttons
     */
    private void initMainNavEvent()
    {
        events.put("country", new EventHandler<ActionEvent>() {
            public void handle(ActionEvent event) {
                windowArea.setRight(countryNavigation);
            }
        });
        events.put("energy", new EventHandler<ActionEvent>() {
            public void handle(ActionEvent event) {
                windowArea.setRight(energyNavigation);
            }
        });
        events.put("upgrades", new EventHandler<ActionEvent>() {
            public void handle(ActionEvent event) {
                windowArea.setRight(upgradeNavigation);
            }
        });
        events.put("goals", new EventHandler<ActionEvent>() {
            public void handle(ActionEvent event) {
                windowArea.setRight(goalNavigation);
            }
        });
    }

    /**
     * Initializes action events for Energy Navigation Buttons
     */
    private void initEnergyNavEvent()
    {
    }

    /**
     * Initializes action events for Country Navigation Buttons
     */
    private void initCountryNavEvent()
    {
    }

    /**
     * Initializes action events for Upgrade Navigation Buttons
     */
    private void initUpgradeNavEvent()
    {
    }

    /**
     * Initializes action events for Goal Navigation Buttons
     */
    private void initGoalNavEvent()
    {
    }

    /**
     * Initializes the Primary Stage
     *
     * @param primaryStage the primary Stage.
     */
    private void initStage(Stage primaryStage)
    {
        primaryStage.setScene(new Scene(windowArea));
        primaryStage.setMinHeight(600);
        primaryStage.setMinWidth(600);
        primaryStage.setTitle(GAME_NAME);
    }

    /**
     * Initializes Navigation Panels
     */
    private void initNav()
    {
        initMainNav();
        initEnergyNav();
        initCountryNav();
        initUpgradeNav();
        initGoalNav();
    }

    /**
     * Initializes Main Window Layout
     */
    private void initWindow()
    {
        windowArea = new BorderPane();
        windowArea.setLeft(mainNavigation);
        windowArea.setRight(countryNavigation);
    }

    /**
     * Initializes Main Navigation
     */
    private void initMainNav()
    {
        mainNavigation    = new NavPane();
        mainNavigation.addButton("country", events.get("country"));
        mainNavigation.addButton("energy", events.get("energy"));
        mainNavigation.addButton("upgrades", events.get("upgrades"));
        mainNavigation.addButton("goals", events.get("goals"));
        mainNavigation.initialize();
    }

    /**
     * Initializes Country Navigation
     */
    private void initCountryNav()
    {
        countryNavigation = new NavPane();
        countryNavigation.addButton("world", events.get("world"));
        countryNavigation.addButton("politicalresources", events.get("politicalresources"));
        countryNavigation.addButton("trade", events.get("trade"));
        countryNavigation.initialize();
    }

    /**
     * Initializes Energy Navigation
     */
    private void initEnergyNav()
    {
        energyNavigation  = new NavPane();
        energyNavigation.addButton("nuclear", events.get("nuclear"));
        energyNavigation.addButton("fossilfuel", events.get("fossilfuel"));
        energyNavigation.addButton("renewable", events.get("renewable"));
        energyNavigation.addButton("oil", events.get("oil"));
        energyNavigation.initialize();
    }

    /**
     * Initializes Upgrade Navigation
     */
    private void initUpgradeNav()
    {
        upgradeNavigation = new NavPane();
        upgradeNavigation.addButton("science", events.get("science"));
        upgradeNavigation.addButton("engineering", events.get("engineering"));
        upgradeNavigation.addButton("policies", events.get("policies"));
        upgradeNavigation.addButton("technologies1", events.get("technologies"));
        upgradeNavigation.initialize();
    }

    /**
     * Initializes Goals Navigation
     */
    private void initGoalNav()
    {
        goalNavigation    = new NavPane();
        goalNavigation.addButton("shortterm", events.get("shortterm"));
        goalNavigation.addButton("longterm", events.get("longterm"));
        goalNavigation.initialize();
    }
}
