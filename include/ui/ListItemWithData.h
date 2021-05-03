#pragma once

#include <QtWidgets/QListWidgetItem>

/**
 * Helper template to keep arbitrary additional data in a `QListWidgetItem`.
 */
template<typename T>
class ListItemWithData: public QListWidgetItem {
    T m_data;

public:
    ListItemWithData() = default;

    /**
     * Constructs a `ListItemWithData` instance.
     * @param data associated data.
     * @param text see Qt docs.
     * @param parent see Qt docs.
     * @param type see Qt docs.
     */
    ListItemWithData(T data, const QString& text, QListWidget* parent = nullptr, int type = Type)
            : QListWidgetItem{text, parent, type}, m_data{std::move(data)} {}

    /**
     * @return associated data.
     */
    const T& data() const {
        return m_data;
    }

    T& data() {
        return m_data;
    }

    /**
     * Sets the associated data to a new value.
     * @param newData replacement data.
     */
    void data(T newData) {
        m_data = std::move(newData);
    }
};
