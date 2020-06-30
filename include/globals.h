#ifndef PROJEKT_GLOBALS_H
#define PROJEKT_GLOBALS_H


#include "ui/MainWindow.h"
#include "db/database.h"

/**
 * Namespace containing a few global objects used throughout the application.
 */
namespace globals {
    /**
     * Pointer to the current main window of the application.
     */
    extern ::MainWindow* mainWindow;
    /**
     * The global database.
     */
    extern ::Database db;
}


#endif //PROJEKT_GLOBALS_H
