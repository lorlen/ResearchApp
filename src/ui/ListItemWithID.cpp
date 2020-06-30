#include "ui/ListItemWithID.h"

ListItemWithID::ListItemWithID(unsigned int id, const QString& text, QListWidget* parent, int type)
        : QListWidgetItem{text, parent, type}, id{id} {}

unsigned int ListItemWithID::getID() {
    return id;
}

void ListItemWithID::setID(unsigned int id) {
    this->id = id;
}
