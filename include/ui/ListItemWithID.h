#ifndef RESEARCHAPP_LISTITEMWITHID_H
#define RESEARCHAPP_LISTITEMWITHID_H


#include <QtWidgets/QListWidgetItem>

/**
 * Helper class to keep additional data in a `QLisstWidgetItem`, in this case
 * an ID of an associated object.
 */
class ListItemWithID: public QListWidgetItem {
    size_t id;

public:
    ListItemWithID() = default;
    /**
     * Constructs a `ListItemWithID` instance.
     * @param id ID of an associated object.
     * @param text see Qt docs.
     * @param parent see Qt docs.
     * @param type see Qt docs.
     */
    ListItemWithID(size_t id, const QString& text, QListWidget* parent = nullptr, int type = Type);
    /**
     * @return the ID of an associated object.
     */
    size_t getID() const;
    /**
     * Sets the ID of an associated object.
     * @param id ID to set.
     */
    void setID(size_t id);
};


#endif //RESEARCHAPP_LISTITEMWITHID_H
