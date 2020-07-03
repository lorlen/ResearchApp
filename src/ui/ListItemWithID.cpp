#include "ui/ListItemWithID.h"

ListItemWithID::ListItemWithID(size_t id, const QString& text, QListWidget* parent, int type)
        : QListWidgetItem{text, parent, type}, id{id} {}

size_t ListItemWithID::getID() const {
    return id;
}

void ListItemWithID::setID(size_t id) {
    this->id = id;
}
