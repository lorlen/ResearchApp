#ifndef RESEARCHAPP_GLOBALS_H
#define RESEARCHAPP_GLOBALS_H


#include "ui/MainWindow.h"
#include "db/Database.h"

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


#endif //RESEARCHAPP_GLOBALS_H
