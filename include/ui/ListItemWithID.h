#ifndef PROJEKT_LISTITEMWITHID_H
#define PROJEKT_LISTITEMWITHID_H


#include <QtWidgets/QListWidgetItem>

/**
 * Helper class to keep additional data in a `QLisstWidgetItem`, in this case
 * an ID of an associated object.
 */
class ListItemWithID: public QListWidgetItem {
    unsigned int id;

public:
    ListItemWithID() = default;
    /**
     * Constructs a `ListItemWithID` instance.
     * @param id ID of an associated object.
     * @param text see Qt docs.
     * @param parent see Qt docs.
     * @param type see Qt docs.
     */
    ListItemWithID(unsigned int id, const QString& text, QListWidget* parent = nullptr, int type = Type);
    /**
     * @return the ID of an associated object.
     */
    unsigned int getID();
    /**
     * Sets the ID of an associated object.
     * @param id ID to set.
     */
    void setID(unsigned int id);
};


#endif //PROJEKT_LISTITEMWITHID_H
